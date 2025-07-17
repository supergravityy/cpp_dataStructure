#include "../header/dList.h"

dList::dList()
{
	this->doubleList_headNode = nullptr;
	this->doubleList_tailNode = nullptr;

	// �θ�Ŭ������ �����ڿ��� �ٸ� ��������� �ʱ�ȭ�Ѵ�.
}

dList::~dList()
{
	this->destroyList();  // �޸� ���� ���� -> �θ�Ŭ������ destroy�� �ƹ��͵� ��� ������

	this->doubleList_headNode = nullptr;
	this->doubleList_tailNode = nullptr;
}

// insert_nextNode�� �θ�Ŭ�������� �̹� ������

bool dList::insert_prevNode(void* node, void* data)
{
	return this->insertPrev(node, data);
}

bool dList::remove_tgtNode(void* node, void** saveData)
{
	return this->removeNode(node, saveData);
}

bool dList::push_back(void* data)
{
	return this->pushBack(data);
}

bool dList::push_front(void* data)
{
	return this->pushFront(data);
}

bool dList::pop_back(void** saveData)
{
	return this->popBack(saveData);
}

bool dList::pop_front(void** saveData)
{
	return this->popFront(saveData);
}

bool dList::pushBack(void* data) 
{
	return this->insertNext(this->get_DoubleList_tail(), data);
}
bool dList::pushFront(void* data) 
{
	return this->insertPrev(this->get_DoubleList_head(), data);
}

bool dList::popBack(void** saveData)
{
	return this->removeNode(this->get_DoubleList_tail(), saveData);
}

bool dList::popFront(void** saveData) 
{
	return this->removeNode(this->get_DoubleList_head(), saveData);
}