#ifndef MEMORY_H
#define MEMORY_H

//#include "DrumManager.h"

class Memory {
public:
    //Memory(DrumManager drum);
    Memory();
    int findSpace(int size);
    int getSizeInUse();
    int getSizeLeft();
    
    void remove();
    void setSizeInUse(int);
    void setSizeLeft(int);
    
private:
    //DrumManager drum;
    int sizeInUse;
    int sizeLeft;
};

#endif