#include "../header/List.h"

List::List()
{
	this->singleList_head = nullptr;
	this->singleList_tail = nullptr;
}

List::~List()
{
	this->destroyList();

	this->size = 0;
	this->cmpFunc = nullptr;
	this->printFunc = nullptr;
	this->freeDataFunc = nullptr;
	this->errCode = NORMAL;
	this->singleList_head = nullptr;
	this->singleList_tail = nullptr;
}

bool List::init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
	, void (*printFunc)(const void* data)
	, void (*destroyDataFunc)(void* data))
{
	if (compareFunc == nullptr || printFunc == nullptr || destroyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->destroyList();
		
		this->singleList_head = nullptr;
		this->singleList_tail = nullptr;
		this->size = 0;
		this->cmpFunc = compareFunc;
		this->printFunc = printFunc;
		this->freeDataFunc = destroyDataFunc;
		this->errCode = NORMAL;
		return true;
	}
}

bool List::insert_nextNode(void* node, void* data)
{
	return this->insertNext(node, data);
}

bool List::remove_nextNode(void* node, void** saveData)
{
	return this->removeNext(node, saveData);
}

void* List::lookup_Node(void* data)
{
	return this->lookUp(data);
}

bool  List::push_back(void* data)
{
	return this->pushBack(data);
}

bool List::push_front(void* data)
{
	return this->pushFront(data);
}