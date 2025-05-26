#pragma once

#include "../header/Data.h"

enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT
};

class Heap
{
public:
    Heap();
    virtual ~Heap();

    /*Management*/
    void Heap_init();
    bool Heap_insert();
    MyAddr Heap_extract();

    /*Utility*/
    int Heap_getSize();

private:
    int heapSize;
    ErrCode errCode;
    Heap* root;
};