#include "../header/cList.h"

cList::cList()
{
	this->circularList_head = nullptr;
}

cList::~cList()
{
	this->destroyList(); // 메모리 해제 먼저 -> 부모클래스의 destroy는 아무것도 없어서 생략됨
	this->circularList_head = nullptr;
}

bool cList::push_front(void* data)
{
	return this->pushFront(data);
}

bool cList::pop_front(void** saveData)
{
	return this->popFront(saveData);
}

bool cList::pushBack(void* data)
{
	// 이 메서드는 List 클래스에서만 사용되도록 제한됨
	return false;
}