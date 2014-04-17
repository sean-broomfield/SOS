#include "Job.h"

Job::Job() {}

Job::Job(int number, int priority, int size, int cpuTime, int currentTime) : number(number), priority(priority), size(size), maxTime(cpuTime), currentTime(currentTime), inMemory(false), blocked(false), terminated(false), direction(0), location(-1) {}

/*
returns the starttime of a job - NICK
*/
int Job::getStartTime() {
	return startTime;
}

int Job::getCurrentTime() {
    return currentTime;
}

int Job::getNumber() {
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
