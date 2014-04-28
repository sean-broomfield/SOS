#ifndef JOB_H
#define JOB_H

#include <iostream>
#include "Memory.h"

class Job {
public:
    Job();
    Job(int, int, int, int, int, Memory);
    int getAddress();
    int getCurrentTime();
    int getStartTime();		//accessor for startTime-Nick
    int getDirection();
    int getMaxTime();
    int getNumber();
    int getLocation();
    int getSize();
    bool isInMemory();
    bool isBlocked();
    bool isTerminated();
    bool isLatched();
    bool findMemory();
    
    void setDirection(int directon);
    void setLocation(int location);
    void setCurrentTime(int currentTime);
    void setIsInMemory(bool inMemory);
    void setPriority(int priority);
    void setNumber (int number);
    void setMaxTime (int maxTime);
    void setBlocked(bool blocked);
    void setTerminated(bool terminated);
    void setLatched(bool latched);
    void setStartTime(int startTime);	//mutator for startTime-Nick
    void setAddress(int address);		//mutator for address-NICk

private:
    int address;
    bool latched;
    bool blocked;
    bool inMemory;
    bool terminated;
    int size;
    int number;
    int priority;
    int maxTime;
    int location;
    int currentTime;
    int direction;
    int startTime;		//Jobs startTime-Nick
    Memory memory;

};

#endif
