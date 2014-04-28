#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <iostream>
#include <deque>
#include <cstdlib>
#include "Job.h"

void siodisk(int JobNum);
void siodrum(int jobNum, int Size, int location, int direction);

using namespace std;

class ioManager {
public:
    ioManager() {}
    
    Job requestIO(Job job){
        ioQueue.push_back(job);
        
        if(ioQueue.size() == 1) {
            //CALL SOS SIODISK
            siodisk(job.getNumber());
            return job;
        } else {
            return ioQueue.front();
        }
    }
   
    
    Job IOmanage(Job job){
        Job job1;
        if (ioQueue.size() > 0) {
            Job newJob = ioQueue.front();
            //CALL SOS SIODISK
            siodisk(newJob.getNumber());
            newJob.setLatched(true);
            return newJob;
        }
        return job1;
    }
    
    Job finishIO(Job job) {
        job.setLatched(false);
        //REMOVE FIRST OCCURENCE OF THIS JOB
        ioQueue.pop_front();
        
        if(job.isBlocked() && (this->contains(job))){
            job.setBlocked(false);
        }
        job = IOmanage(job);
        return job;
    }
    
    
    
    bool contains(Job job) {
        for(deque<Job>::iterator iter = ioQueue.begin(); iter != ioQueue.end(); iter++) {
            if (iter->getNumber() == job.getNumber())
                return true;
        }
        return false;
    }
    
    /*
    void PrintIoTable() {
        cout << "-------------------------------------------------" << endl;
        cout << "| number \t| location \t| size \t| in memory? \t|" << endl;
        for(deque<Job>::iterator iter = ioQueue.begin(); iter != ioQueue.end(); iter++) {
            cout << "| " << *iter->getNumber() << "\t\t|" << *iter->getLocation() << "\t\t|" << *iter->getSize() << "\t|" << *iter->isInMemory() << "\t\t|" << endl;
        }
        cout << "-------------------------------------------------" << endl;
    }
     */
private:
    deque<Job> ioQueue;
};

#endif