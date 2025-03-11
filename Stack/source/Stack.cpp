#include "../header/Stack.h"

/*----utils----*/

void printData2(MyAddr* data) 
{
    cout << "ID : ";
    cout << data->id << endl;
    cout << "Name : ";
    cout << data->name << endl;
    cout << "PhoneNumber : ";
    cout << data->phone << endl;
}

/*----public----*/

Stack::Stack()
{
    // do nothing
    // parent class(list) has proper Constructor
}

Stack::~Stack()
{
    MyAddr* temp = nullptr;

    while (this->listSize != 0)
    {
        this->Stack_pop(&temp);
    }
    
    this->listSize = 0;
    this->headNode = nullptr;
    this->tailNode = nullptr;
}

void Stack::Stack_init()
{
    MyAddr* temp = nullptr;

    while (this->listSize > 0)
    {
        this->Stack_pop(&temp);
    }
    
}

int Stack::Stack_push(MyAddr* data)
{
    return this->List_ins_next(nullptr, data);
}

int Stack::Stack_pop(MyAddr** data)
{
    return this->List_rem_next(nullptr, data);
}

int Stack::Stack_peek(MyAddr* bucket)
{
    int result = 0;

    if(this->headNode != nullptr && bucket != nullptr)
    {
        memcpy(bucket,this->headNode->data,sizeof(MyAddr));
    }
    else
    {
        result = 1;
    }

    return result;
}

int Stack::Stack_getStackSize()
{
    return this->listSize;
}

int Stack::Stack_cmpData(const char* key1, const char* key2)
{
    return !(strcmp(key1,key2));
}

ErrCode Stack::Stack_getErrCode()
{
    return this->List_getErrcode();
}

/*----private----*/