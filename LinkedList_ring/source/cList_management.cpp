#include "../header/cList.h"

cList::cList()
{
	this->circularList_head = nullptr;
}

cList::~cList()
{
	this->destroyList(); // �޸� ���� ���� -> �θ�Ŭ������ destroy�� �ƹ��͵� ��� ������
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
	// �� �޼���� List Ŭ���������� ���ǵ��� ���ѵ�
	return false;
}