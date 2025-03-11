#pragma once

#include "List.h"

class Stack : public List
{
    public:
    Stack();
    virtual ~Stack();

    void Stack_init();
    int Stack_push(MyAddr* Data);
    int Stack_pop(MyAddr** Data);
    int Stack_peek(MyAddr* bucket);

    int Stack_getStackSize();
    virtual int Stack_cmpData(const char* key1, const char* key2);
    ErrCode Stack_getErrCode();
    
    private:

};