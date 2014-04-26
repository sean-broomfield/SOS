#include "Memory.h"

//Memory::Memory(DrumManager drum) : drum(drum), sizeInUse(0), sizeLeft(100) {}

Memory::Memory() : sizeInUse(0), sizeLeft(100) {}

int Memory::findSpace(int size){
    if (sizeLeft > size){
        int location = sizeInUse;
        sizeInUse += size;
        sizeLeft -= size;
        return location;
    }
    return -1;
}

void Memory::remove() {
    
}

int Memory::getSizeInUse() {
    return sizeInUse;
}

void Memory::setSizeInUse(int size) {
    sizeInUse = size;
    return;
}

int Memory::getSizeLeft() {
    return sizeLeft;
}

void Memory::setSizeLeft(int size) {
    sizeLeft = size;
    return;
}
