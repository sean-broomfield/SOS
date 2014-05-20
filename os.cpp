#include "Job.h"
#include "Memory.h"
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

void bookKeep(int time);
void ontrace();
void offtrace();
void siodisk(int JobNum);
void siodrum(int jobNum, int Size, int location, int direction);
int shortestJob(vector<Job> job);
void dispatcher(int &a, int p[]);
void queueAllJobs();
void manageDrum(int);
int findNewJob();
void deleteJob(int);
void requestIO(int);
void findNextIO();
int jobNotInYet;

Memory memory;
static vector<Job> jobs;
static queue<int> ioQueue;
static int systemTime = 0;

int jobGoingIn = -1;
int goingDirection = -1;
int runningJob = -1;
int ioJob = 0;

bool drum = false;

void startup() {
    ontrace();
}

/********************************/
/**START OF INTERRUPT HANDLERS**/
/******************************/

void Crint(int &a, int p[]) {
    bookKeep(p[5]);
    Job job(p[1], p[2], p[3], p[4], p[5]);
    jobs.push_back(job);
    manageDrum(p[1]);
    runningJob = shortestJob(jobs);
    dispatcher(a, p);
}

void Tro(int &a, int p[]) {
    bookKeep(p[5]);
        
    //IF MAXTIME SUBTRACT CURRENT TIME == 0
    //REMOVE JOB
    if(jobs[runningJob].getPendingIO() == 0) {
        deleteJob(runningJob);
    } else {
        jobs[runningJob].setTerminated(true);
    }
        
    //WRITE FUNCTION TO FIND NEW JOB THAT SHOULD BE RUN.
    //UPDATE THE DRUM
        
    manageDrum(findNewJob());
    runningJob = shortestJob(jobs);
    dispatcher(a, p);
    return;
}
    
void Svc (int &a, int p[]) {
    bookKeep(p[5]);
    switch(a)
    {
        case 5:
            //CHECK TO SEE IF THERE IS IO LEFT AND IF TERMINATED IS TRUE
            //OTHERWISE ISTERMINATED(TRUE) SO IT CAN BE KILLED LATER
            if(jobs[runningJob].isTerminated() && jobs[runningJob].getPendingIO() == 0 && jobs[runningJob].getMaxTime() == 0) {
                deleteJob(runningJob);
            } else {
                jobs[runningJob].setTerminated(true);
            }
            break;
        case 6:
            if(ioQueue.empty())
                siodisk(jobs[runningJob].getNumber());
            requestIO(runningJob);
            break;
        case 7:
            //CHECK TO SEE IF A JOB HAS PENDING IO BEFORE BLOCKING IT
            //IF SO THEN BLOCK IT
            if(jobs[runningJob].getPendingIO() != 0) {
                jobs[runningJob].setBlocked(true);
            }
            break;
    }

    manageDrum(findNewJob());
    runningJob = shortestJob(jobs);
    dispatcher(a, p);

    return;
}
    
void Drmint(int &a, int p[]) {
    bookKeep(p[5]);

    //SINCE DRUMINT IS OCCURING SET DRUMBUSY TO FALSE
    drum = false;
        
    //FIND THE PLACE IN MEMORY OF THE JOB BEING SWAPPED
    //IF IT IS LOCATED THEN SET INMEMORY TO TRUE
    int place = memory.locateJob(jobs, jobGoingIn);
    jobs[place].setIsInMemory(true);
        
    manageDrum(findNewJob());
    runningJob = shortestJob(jobs);
    dispatcher(a, p);

    return;
}

void Dskint(int &a, int p[]) {
    bookKeep(p[5]);
    
    //FIND THE NEXT JOB WITH IO
    findNextIO();
        
    //REDUCE PENDING IO
    jobs[ioJob].setPendingIO(jobs[ioJob].getPendingIO() - 1);
        
    //UNBLOCK AND LATCH IF IT HAS NO MORE IO REQUESTS
    if(jobs[ioJob].getPendingIO() == 0) {
        jobs[ioJob].setBlocked(false);
        jobs[ioJob].setLatched(false);
    }
        
    //DELETE JOB IF IT IS TERMINATED, IS IN MEMORY, AND HAS NO OUTSTANDING
    //IO
    if(jobs[ioJob].isTerminated() == 1 && jobs[ioJob].getPendingIO() == 0 && jobs[ioJob].isInMemory())
            deleteJob(ioJob);
        
    //POPS THE THE JOB THAT JUST FINISHED IO
    ioQueue.pop();

    //IF THE QUEUE IS NOT EMPTY, FIND THE NEXT IO JOB
    //DO ITS IO IMMEDIATELY
    if(ioQueue.empty() == false) {
        findNextIO();
        siodisk(jobs[ioJob].getNumber());
    }
        
    manageDrum(findNewJob());
    runningJob = shortestJob(jobs);
    dispatcher(a, p);

    return;
}

/******************************/
/**END OF INTERRUPT HANDLERS**/
/****************************/








/*************************/
/**IO MANAGER FUNCTIONS**/
/***********************/

//PUTS JOB ON IOQUEUE AND SET LATCHED
void requestIO(int i) {
    ioQueue.push(jobs[i].getNumber());
    jobs[i].setPendingIO(jobs[i].getPendingIO() + 1);
    jobs[i].setLatched(true);
    findNextIO();
    return;
}

//FINDS NEXT JOB WITH IO TO BE DONE
void findNextIO() {
    for(int i = 0; i < jobs.size(); i++) {
        if(jobs[i].getNumber() == ioQueue.front()) {
            ioJob = i;
            return;
        }
    }
}

/****************************/
/*****END OF IO MANAGER*****/
/**************************/










/***************************/
/**DRUM MANAGER FUNCTIONS**/
/*************************/


//IF ISINMEMORY THEN ADD IT TO THE MEMORY TABLE
//IF THE JOB HAS BEEN SET TO TERMINATED AND HAS NO IO
//THEN DELETE THE JOB FROM MEMORY
void queueAllJobs() {
    for(int i = 0; i < jobs.size(); i++) {
        if(jobs.at(i).isInMemory())
            memory.addJobTo(i, jobs);
        if (jobs.at(i).isTerminated() && jobs.at(i).getPendingIO() == 0)
            deleteJob(i);
    }
}



void manageDrum(int number) {
    //IF THE DRUM ISNT BUSY AND THERES A RUNNINGJOB PASSED
    if(!drum && number != -1) {
        queueAllJobs();
        
            
        //FIND WHERE THE JOB IS LOCATED IN THE MEMORY ARRAY
        int jobPlaceInMem = memory.locateJob(jobs, number);
            
        //CHECK MEMORY TO SEE IF THERE IS ENOUGH SPACE FOR THE JOB SIZE
        //RETURNS THE # OF THE SPACE THAT IS FREE
        int avail = memory.MemoryCheck(jobs[jobPlaceInMem].getSize());
        
        //IF AVAIL < 100 AND IF THE JOB ISNT IN MEMORY
        //PLACE THE LOCATION OF THE JOB IN THE AVAILABLE SPACE
        //SWAP THE JOB INTO MEMORY (DRMINT WILL OCCUR)
        //SET JOB GOING IN TO THE NUMBER OF THE JOB
        //SET THE GOING DIRECTION
        //SET THE JOB IN THE TABLE AND SET THE DRUM = TRUE
        //WHEN TRUE IT MEANS THE DRUM IS BUSY
        //tell the drmint that the drum is busy (use boolean or queue)
        //TEST: [TRY USING queue.empty() OR bool drum = true]
        if((avail < 100)){
            if(!jobs[jobPlaceInMem].isInMemory()) {
                drum = true;
                jobGoingIn = number;
                jobs[jobPlaceInMem].setLocation(avail);
                memory.setMemory(jobs, jobPlaceInMem, avail);
                siodrum(jobs[jobPlaceInMem].getNumber(), jobs[jobPlaceInMem].getSize(), jobs[jobPlaceInMem].getLocation(), 0);
            }
        }
    }
}


/**************************/
/**END OF DRUM FUNCTIONS**/
/************************/










/**************************/
/***SCHEDULER FUNCTIONS***/
/************************/

//FINDS THE SHORTEST JOB THAT IS IN MEMORY
//RETURNS THE PLACE OF THAT JOB FROM THE VECTOR
//(i)
int shortestJob(vector<Job> jobs) {
    int shortJobNumber = -1;
    int minTime = 1000000;
    
    for(int i = 0; i < jobs.size(); i++) {
        if(jobs[i].isInMemory() && jobs[i].getMaxTime() != 0 && !jobs[i].isTerminated() && !jobs[i].isBlocked()) {
            if(jobs[i].getMaxTime() < minTime) {
                minTime = jobs[i].getMaxTime();
                shortJobNumber = i;
            }
        }
    }
    return shortJobNumber;
}

//FINDS THE JOB WITH THE SHORTEST TIME
//THAT IS NOT IN MEMORY SO IT CAN BE SWAPPED IN
//ON THE DRUM
int findNewJob() {
    
    int shortJobNotIn = 0;  //Location of the job in the vector
    int minTime = 1000000;  //Minimum time
    
    for(int i = 0; i < jobs.size(); i++) {
        if(jobs[i].isInMemory() == 0)
            if(jobs[i].getMaxTime() < minTime) {
                minTime = jobs[i].getMaxTime();
                shortJobNotIn = i;
            }
    }
    if(shortJobNotIn != 0)
        return jobs[shortJobNotIn].getNumber();
    return -1;
}

/***********************/
/***END OF SCHEDULER***/
/*********************/









/************************/
/**DISPATCHER FUNCTION**/
/**********************/

void dispatcher(int &a, int p[]) {
    if(!jobs[runningJob].isInMemory() || jobs[runningJob].isBlocked() || runningJob == -1) {
        a = 1;
    } else {
        a = 2;
        p[2] = jobs[runningJob].getLocation();
        p[3] = jobs[runningJob].getSize();
        p[4] = jobs[runningJob].getMaxTime();
        jobs[runningJob].setStartTime(p[5]);
    }
}

/************************/
/***END OF DISPATCHER***/
/**********************/









/************************/
/***BOOKKEEP FUNCTION***/
/**********************/

void bookKeep(int time) {
    //IF THERE IS A RUNNING JOB THEN SET THE CURRENT TIME TO THE MAX
    //SET THE MAX TIME TO THE DIFFERENCE
    if(runningJob != -1) {
        int val = time - jobs[runningJob].getStartTime();
        jobs[runningJob].setCurrentTime(jobs[runningJob].getMaxTime());
        jobs[runningJob].setMaxTime(jobs[runningJob].getMaxTime() - val);
    }
        
}

/************************/
/****END OF BOOKKEEP****/
/**********************/









/***************************/
/***DELETE JOBS FUNCTION***/
/*************************/


//REMOVES THE JOB FROM MEMORY BASED ON THE NUMBER PASSED
//ERASES THE JOB FROM THE JOB VECTOR
void deleteJob(int place) {
    
    memory.removeJobFrom(jobs[place].getLocation());
    jobs.erase(jobs.begin() + place);
}

/***************************/
/****END OF DELETE JOBS****/
/*************************/







/*****************************************************************/

//TRY SHORTEST JOB NEXT? SIMPLER TO WRITE.


//GO THRU LIST. FIND SHORTEST JOB
//IF LIST IS EMPTY RETURNS -1
/*int shortestJob(vector<Job> job) {
    int time = 40;
    int num = -1;
    
    for(int i = 0; i < job.size(); i++) {
        if(jobs[i].getMaxTime() < time) {
            num = jobs[i].getMaxTime();
            num = i;
        }
    }
    return num;
}
*/


/*
    void terminateJob(Job &runningJob) {
        int p;
        if( !(runningJob.getNumber() == -1) && !io.contains(runningJob)) {
            memory.remove(runningJob.getLocation(), runningJob.getSize());
            for(int i = 1; i < jobs.size(); i++) {
                if(jobs.at(i).getNumber() == runningJob.getNumber()) {
                    p = i;
                    break;
                }
             }
             jobs.erase(jobs.begin() + (p-1));
        } else if (!(runningJob.getNumber() == -1)) {
            runningJob.setTerminated(true);
        }
        return;
    }



 ROUND ROBIN ALGORITHM

    int schedule(vector<Job> jobs, int &a, int p[]) {
        for(int i = 0; i < jobs.size(); i++) {
            if(runningJob == i) {
                //IF THE JOB RAN THE AMOUNT OF THE TIMESLICE AND HAS MORE TIME LEFT
                if((jobs[i].getMaxTime() - TIMESLICE) != 0) {
                    jobs[i].setMaxTime(jobs[i].getMaxTime() - TIMESLICE);
                    
                    //put job at end of vector
                    jobs.push_back(jobs[i]);
                    
                    //erase jobs[i]
                    jobs.erase(jobs.begin()+i);
                    continue;
                }
                
            }
            if(jobs[i].isInMemory() && jobs[i].getMaxTime() != 0 && !jobs[i].getTerminated() && !jobs[i].getBlocked()) {
                if(jobs[i].getMaxTime() > jobs[i].getCurrentTime() + TIMESLICE) {
                    a = 2;
                    p[2] = jobs[i].getLocation();
                    p[3] = jobs[i].getSize();
                    p[4] = TIMESLICE;
                    return i;
                } else if (!(jobs[i].getCurrentTime() == jobs[i].getMaxTime())) {
                    a = 2;
                    p[2] = jobs[i].getLocation();
                    p[3] = jobs[i].getSize();
                    p[4] = jobs[i].getMaxTime() - jobs[i].getCurrentTime();
                    return i;
                } else {
                    a = 2;
                    p[2] = jobs[i].getLocation();
                    p[3] = jobs[i].getSize();
                    p[4] = TIMESLICE;
                    return i;
                }
            }
        }
        a = 1;
        return -1;
    }
*/
