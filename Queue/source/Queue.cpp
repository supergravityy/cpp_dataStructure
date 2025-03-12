#include "../header/Queue.h"

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

Queue::Queue()
{
    // do nothing
    // parent class(list) has proper Constructor
}

Queue::~Queue()
{
    MyAddr* temp = nullptr;

    while (this->listSize != 0)
    {
        this->Queue_dequeue(&temp);
    }
    
    this->listSize = 0;
    this->headNode = nullptr;
    this->tailNode = nullptr;
}

void Queue::Queue_init()
{
    MyAddr* temp = nullptr;

    while (this->listSize != 0)
    {
        this->Queue_dequeue(&temp);
    }
}

int Queue::Queue_enqueue(MyAddr* data)
{
    return this->List_ins_next(this->tailNode, data);
}

int Queue::Queue_dequeue(MyAddr** data)
{
    return this->List_rem_next(nullptr,data);
}

int Queue::Queue_peek(MyAddr* bucket)
{
    int result = 0;

    if(this->headNode != nullptr)
        memcpy(bucket, this->headNode->data, sizeof(MyAddr));
    else
        result = 1;

    return result;
}

int Queue::Queue_getQueueSize()
{
    return this->listSize;
}

int Queue::Queue_cmpData(const char* key1, const char* key2)
{
    return !(strcmp(key1,key2));
}

ErrCode Queue::Queue_getErrCode()
{
    return this->List_getErrcode();
}