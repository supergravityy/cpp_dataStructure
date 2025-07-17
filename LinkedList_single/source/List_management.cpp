#include "../header/List.h"

List::List()
{
	this->singleList_head = nullptr;
	this->singleList_tail = nullptr;
}

List::~List()
{
	// 주의 : 소멸자 호출 순서에서, 자식소멸자가 호출된 후, 부모소멸자가 호출되면, 오버라이딩 되기전의 메서드가 호출됨
	// 자식 메서드의의 removeNext와 부모 메서드의의 removeNext는 엄연히 틀리다. 그러나, 자식메서드에서 이미 size =0 을 보장하기에 바로 ret되기에 안전함.
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