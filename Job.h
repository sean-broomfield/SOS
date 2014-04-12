#ifndef JOB_H
#define JOB_H

#include <iostream>

class Job {
public:
    Job();
    Job(int, int, int, int, int);
    int getCurrentTime();
    int getDirection();
    int getMaxTime();
    int getNumber();
    int getLocation();
    int getSize();
    bool isInMemory();
    bool isBlocked();
    bool isTerminated();
    bool isLatched();
    
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

private:
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

};

#endif