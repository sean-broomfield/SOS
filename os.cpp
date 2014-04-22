#include "Job.h"
#include <list>
#include <iostream>
using namespace std;

    static list<Job> jobs;
    static Job running_job; //job object that runs on cpu-NICK

    void startup() {
        //sos.ontrace();
        
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
    
    void Svc (int a, int p[]) {
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
    
    /*
    This fucnction is going to keep track of the jobs time
    parameter: time p[5] will be passed in the fucntion.
    Will be called at the beginning of each interupt. - NICK
    */
    
    void bookKeep(int time) {
      int time_difference;	//time job has actually runned
      time_difference = time - running_job.getStartTime();

      if(time_difference <= running_job.getMaxTime())
      {
          running_job.setCurrentTime(time_difference);

      }

      
    }
    
    /*
	The Dispacther fucntion set the CPU registers before leaving the interupts
	parameters: int *a-CPU mode; int p[]- job's infomation from p[1]-p[5] if needed
	NICK
	*/

	void Dispatcher(int *a, int p[]) {
		
		if(!running_job.isInMemory() || running_job.isBlocked()) {
			*a=1;
		}
	
		else {
			*a=2;
			p[2]=running_job.getAddress();
			p[3]=running_job.getSize();
			p[4]=TimeSlice;
		}
	}


