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
    Heap(bool (*compareFunc)(int num1, int num2));
    virtual ~Heap();

    /*Management*/
    void Heap_init(bool (*compareFunc)(int num1, int num2));
    void Heap_destroy();
    bool Heap_insert(MyAddr* data);
    bool Heap_extract(MyAddr** data);
    void Heap_printAll();

    /*Utility*/
    int Heap_getSize();
    ErrCode Heap_getErrCode();

private:
    int treeSize;
    ErrCode errCode;
    MyAddr** treeArr;
    bool (*compare)(int num1, int num2) = nullptr;
};