#include "../header/Stack.h"

Stack::Stack()
{
	// do nothing
}

Stack::~Stack()
{
	// do nothing
}

bool Stack::push(void* data)
{
	return this->insertNext(nullptr, data);
}

bool Stack::pop(void** saveData)
{
	return this->removeNext(nullptr, saveData);
}

const void* Stack::peek()
{
	return (const void*)this->get_Data(this->get_SingleList_head());
}