#ifndef MEMORY_H
#define MEMORY_H

#include "Job.h"
#include <vector>

using namespace std;

//TRY USING ARRAY
//SET ARRAY[JOBSIZE]

class Memory {
private:
    int memory[100];
    
public:
    
    Memory() {
        clear();
    }
    
    void clear() {
        for(int i = 0; i < 100; i++) {
            memory[i] = 0;
        }
    }
    
    //ADDS JOB TO MEMORY ARRAY
    //SETS SIZE OF LOCATION TO THE JOB SIZE
    void addJobTo(int number, vector<Job> jobs) {
        int location = jobs[number].getLocation();
        int size  = jobs[number].getSize();
        memory[location] = size;
    }
    
    //WHEN A JOB IS DELETED IT SETS THE LOCATION
    //OF SAID JOB IN MEMORY TO 0 SO THAT IT IS
    //USABLE AGAIN.
    void removeJobFrom(int number) {
        memory[number] = 0;
    }
    
    //avail: The first free place in memory
    //jobPlaceInMem: The position of the job in the vector
    void setMemory(vector<Job> jobs, int jobPlaceInMem, int avail) {
        memory[avail]= jobs[jobPlaceInMem].getSize();
    }
    
    int MemoryCheck(int size) {
        int i, j;
        for(i = 0; i < 100; i++) {
            //SKIPS OCCUPIED SPACE IN MEMORY AND GOES TO NEXT AVAILABLE LOCATION
            if(memory[i] != 0)
                i += memory[i];
            else {
                for (j = 1; j < size; j ++) {
                    //CHECKS THE NEXT PLACE IN MEMORY TO SEE IF EMPTY
                    //IF NOT THEN ADD THE I + J + THE SIZE IN THAT SPACE TO FIND NEXT PLACE IN MEMORY
                    if(memory[i + j] != 0) {
                        i += (j + memory[i+j]);
                        break;
                    } else {
                        return i;
                    }
                }
            }
            //CHECKS AGAIN FOR A FREE SPACE IN MEMORY
            while(memory[i] != 0) {
                i = i + memory[i];
            }
            //IF THE SPACE IS FREE AND THE (OFFSET + SIZE) < 100
            if(memory[i] == 0) {
                if((i + size) < 100) {
                    //CHECK THE NEXT PLACE IN MEMORY
                    for(j = 1; j < size; j++){
                        //IF OCCUPIED GO TO THE NEXT OFFSET
                        if(memory[i + j] != 0) {
                            i += (j + memory[j + i]);
                            //CHECK AGAIN
                            while(memory[i] != 0) {
                                i += memory[i];
                            }
                            break;
                        } else {
                            //RETURNS THE AVAILABLE MEMORY
                            return i;
                        }
                    }
                } else if((i + size) >= 100)
                    //RETURNS 100 SINCE THERE IS NO AVAILABLE SPACE
                    return 100;
            }

        }
    }
    
    int locateJob(vector<Job> jobs, int number) {
        for(int i = 0; i <= jobs.size(); i++)
            if(jobs[i].getNumber() == number) {
                return i;
            }
    }
        
        
};


/*
class Memory {
private:
    vector<int> mem;
public:
    Memory() {
        mem.push_back(0);
        mem.push_back(100);
    }
    
    int findSpace(int size) {
        if(mem.front() < size) {
            cout << "Size is " << size;
            cout << endl << "Front is " << mem.front() << endl;
            int location = mem.front();
            mem.front() += size;
            mem.back() -= size;
            return location;
        }
        cout << "At -1 statement" <<  endl;
        return -1;
    }
    
};
*/


/*
class DrumManager;
class Memory {
public:
    /*Memory(DrumManager drum) {
        pair<int, int> p(0, 100);
        this->p = p;
        this->drum = drum;
    }
    
    Memory() {
        pair<int, int> p(0, 100);
        this->p = p;
    }
                                 
    int findSpace(vector<Job> &jobs, int index) {
        if(p.second > jobs[index].getSize()) {
            jobs[index].setLocation(p.first);
            p.first += jobs[index].getSize();
            p.second -= jobs[index].getSize();
            return true;
        //    int location = p.first;
        //    p.first += size;
        //    p.second -= size;
        //    return location;
        }
        //return -1;
        return false;
    }
     
    void remove(int location, int size) {
        bool spaceFreed = false;
        if(p.first == (location + size)) {
            p.first -= size;
            p.second += size;
            spaceFreed = true;
        } else if (p.first + p.second == location) {
            p.second += size;
            spaceFreed = true;
        }
        if (!spaceFreed) {
            while(spaceFreed == false) {
                if(p.first > location) {
                    pair<int, int> p(location, size);
                    this->p = p;
                    spaceFreed = true;
                }
        }
     
        }
    }
     
  //  DrumManager getDrum() {
    //    return drum;
   // }
    
private:
    pair<int, int> p;
    //DrumManager drum;
};

*/
 
#endif

