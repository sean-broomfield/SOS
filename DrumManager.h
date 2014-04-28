#include <iostream>
#include <queue>
#include <list>
#include <cstdlib>
#include "Job.h"

using namespace std;

void siodisk(int JobNum);
void siodrum(int jobNum, int Size, int location, int direction);

class DrumManager {
public:
    DrumManager();
    
    DrumManager(list<Job> jobs) {
        this->jobs = jobs;
    }
    
    /*Queues Jobs to be processed. */
    Job queueJob(Job job, int direction) {
        job.setDirection(direction);
        drumQueue.push(job);
        return job;
    }
    
    /*Checks to see if jobs are in memory.
     If job is in memory it sets "setInMemory"
     variable to true. If it is not, it sets it
     to false and removes the job from the drum
     and sets "setInMemory" to false.*/
    Job swap(list<Job> jobs) {
        Job job = drumQueue.front();
        if(job.getDirection() == 1) {
            job.setIsInMemory(true);
        } else {
            //remove Job from memory
            job.setLocation(-1);
            job.setIsInMemory(false);
        }
        drumQueue.pop();
        return job;
    }
    
    /*Completes the drmint for each job if they are in memory
    returns a job to os.cpp. This job that is returned is the new drumJob in
    os.cpp.*/
    Job manageDrum(Job drumJob) {
        //Must add "for all jobs in list jobs" clause
        Job j;
        if(j.getLocation() == -1) {
            if(j.findMemory()) {
                queueJob(j, 1);
            }
        }
        if (drumQueue.size() > 0 && drumQueue.front().getNumber() != drumJob.getNumber()) {
            Job newJob = drumQueue.front();
            if(newJob.getDirection() == 1) {
                siodrum(newJob.getNumber(), newJob.getSize(), newJob.getLocation(), 0);
            } else {
                siodrum(newJob.getNumber(), newJob.getSize(),    newJob.getLocation(), 1);
            }
            return newJob;
        }
        return drumJob;
    }
    
    
    
private:
    //Queues jobs that have initiated a drmint
    queue<Job> drumQueue;
    
    //List of all jobs that have entered the system
    list<Job> jobs;
};