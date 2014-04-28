#include "Job.h"

Job::Job() : number(-1) {}

Job::Job(int number, int priority, int size, int cpuTime, int currentTime, Memory memory) {
    
    this->number = number;
    this->priority = priority;
    this->size = size;
    this->maxTime = cpuTime;
    this->currentTime = currentTime;
    this->inMemory = false;
    this->blocked = false;
    this->terminated = false;
    this->direction = -1;
    this->memory = memory;
    this->location = memory.findSpace(size);
}

bool Job::findMemory() {
    location = memory.findSpace(size);
    if (location == -1) {
        return false;
    }
    return true;
}

/*
<<<<<<< HEAD
reuturns the address of the job
=======
returns the starttime of a job
>>>>>>> FETCH_HEAD
NICK
*/

int Job::getStartTime() {
    return startTime;
}

int Job::getAddress() {
	return address;
}

int Job::getCurrentTime() {
    return currentTime;
}

int Job::getNumber(){
    return number;
}

int Job::getDirection() {
    return direction;
}

int Job::getMaxTime() {
    return maxTime;
}

int Job::getLocation() {
    return location;
}

int Job::getSize() {
    return size;
}

bool Job::isInMemory() {
    return inMemory;
}

bool Job::isBlocked() {
    return blocked;
}

bool Job::isTerminated() {
    return terminated;
}

bool Job::isLatched() {
    return latched;
}

void Job::setLatched(bool latched) {
    this->latched = latched;
}

void Job::setTerminated(bool terminated) {
    this->terminated = terminated;
}

void Job::setIsInMemory(bool inMemory) {
    this->inMemory = inMemory;
}

void Job::setBlocked(bool blocked) {
    this->blocked = blocked;
}

void Job::setDirection(int direction) {
    this->direction = direction;
}

void Job::setLocation(int location) {
    this->location = location;
}

void Job::setCurrentTime(int currentTime) {
    this->currentTime = currentTime;
}

void Job::setNumber(int number) {
    this->number = number;
}

void Job::setMaxTime(int maxTime) {
    this->maxTime = maxTime;
}

void Job::setPriority(int priority) {
    this->priority = priority;
}

void Job::setStartTime(int startTime) {
	this->startTime = startTime;
}

void Job::setAddress(int address) {
	this->address=address;
}
