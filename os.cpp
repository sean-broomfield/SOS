#include "Job.h"
#include <list>
#include <iostream>
using namespace std;

    static list<Job> jobs;

    void startup() {
        sos.ontrace();
    }

    void Crint(int *a, int p[]) {
        cout << "Job Number: " << p[1] << endl;
        //ADD BOOKEEPING FUNCTION
        Job job(p[1], p[2], p[3], p[4], p[5]);
        jobs.push_back(job);
        //CHECK JOB LOCATION AND SEND JOB TO DRUM
        //If getLocation returns -1 (not in memory) then send to drum and change direction of job
        return;
    }
    
    void Tro(int *a, int p[]) {
        return;
    }
    
    void Svc (int *a, int p[]) {
        cout << "Supervisor call." << endl;
        switch(a)
        {
            case 5:
                //JOB HAS TERMINATED
                break;
            case 6:
                //JOB REQUESTS DISK I/O
                break;
            case 7:
                //JOB WANTS TO BE BLOCKED UNTIL I/O REQUESTS ARE DONE
                break;
        }
        return;
    }
    
    void Drmint(int *a, int p[]) {
        return;
    }
    
    void DiskInt(int *a, int p[]) {
        return;
    }
    
    void bookKeep(int time) {
        return;
    }
    

