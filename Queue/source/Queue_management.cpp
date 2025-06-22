#include "../header/Queue.h"

Queue::Queue()
{
	// do nothing
}
Queue::~Queue()
{
	// do nothing
}

bool Queue::enqueue(void* data)
{
	return this->insertNext(this->get_SingleList_tail(), data);
}

bool Queue::dequeue(void** saveData)
{
	return this->removeNext(nullptr,saveData);
}

const void* Queue::peek()
{
	return (const void*)this->get_Data(this->get_SingleList_head());
}