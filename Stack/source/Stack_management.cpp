#include "../header/Stack.h"

Stack::Stack()
{
	// do nothing
}

Stack::~Stack()
{
	// do nothing
}

bool Stack::Push(void* data)
{
	return this->insertNext(nullptr, data);
}

bool Stack::Pop(void** saveData)
{
	return this->removeNext(nullptr, saveData);
}

const void* Stack::Peek()
{
	return (const void*)this->get_Data(this->get_SingleList_head());
}