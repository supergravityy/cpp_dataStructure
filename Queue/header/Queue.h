#pragma once

#include "List.h"

class Queue : public List
{
    public:
    Queue();
    virtual ~Queue();

    void Queue_init();
    int Queue_enqueue(MyAddr* Data);
    int Queue_dequeue(MyAddr** Data);
    int Queue_peek(MyAddr* Data);

    int Queue_getQueueSize();
    virtual int Queue_cmpData(const char* key1, const char* key2);
    ErrCode Queue_getErrCode();

    private:
};