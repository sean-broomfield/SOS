#ifndef JOB_H
#define JOB_H

#include <iostream>

using namespace std;

class Job {
private:
    int pendingIO;
    int size;
    int number;
    int priority;
    int maxTime;
    int location;
    int startTime;
    int currentTime;
    int direction;
    bool latched;
    bool blocked;
    bool inMemory;
    bool terminated;

public:
    Job() : number(-1), location(0), priority(0), size(0), pendingIO(0), maxTime(0), startTime(0), currentTime(0), direction(0), inMemory(false), blocked(false), terminated(false), latched(false) {}
    
    Job(int number, int priority, int size, int maxTime, int currentTime) : number(number), priority(priority), size(size), maxTime(maxTime), currentTime(currentTime), direction(-1), inMemory(false), blocked(false), latched(false), terminated(false), pendingIO(0) {}
    
    int getPendingIO() {
        return pendingIO;
    }
    
    void setPendingIO(int pendingIO) {
        this->pendingIO = pendingIO;
    }
    
    int getPriority() {
        return priority;
    }
    
    int getCurrentTime() {
        return currentTime;
    }
    
    int getStartTime() {
        return startTime;
    }
    
    int getDirection() {
        return direction;
    }
    
    int getMaxTime(){
        return maxTime;
    }
    
    int getNumber() const {
        return number;
    }
    
    int getLocation() {
        return location;
    }
    
    int getSize() {
        return size;
    }
    
    bool isInMemory() {
        return inMemory;
    }
    
    bool isBlocked() {
        return blocked;
    }
    
    bool isTerminated() {
        return terminated;
    }
    
    bool isLatched() {
        return latched;
    }
    
    void setDirection(int direction) {
        this->direction = direction;
    }
    
    void setLocation(int location) {
        this->location = location;
    }
    
    void setCurrentTime(int currentTime) {
        this->currentTime = currentTime;
    }
    
    void setIsInMemory(bool inMemory){
        this->inMemory = inMemory;
    }
    
    void setPriority(int priority){
        this->priority = priority;
    }
    
    void setNumber (int number) {
        this->number = number;
    }
    
    void setMaxTime (int maxTime) {
        this->maxTime = maxTime;
    }
    void setBlocked(bool blocked) {
        this->blocked = blocked;
    }
    
    void setTerminated(bool terminated) {
        this->terminated = terminated;
    }
    void setLatched(bool latched) {
        this->latched = latched;
    }
    
    void setStartTime(int startTime) {
        this->startTime = startTime;
    }
};

#endif
