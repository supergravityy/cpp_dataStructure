#include "../header/dList.h"

void* dList::makeNode()
{
	typDoubleList_Node* newNode = new typDoubleList_Node;

	return newNode;
}

void dList::initNode(void* node, void* data)
{
	typDoubleList_Node* temp = (typDoubleList_Node *) node;
	temp->data = data;
	temp->nextNode = nullptr;
	temp->prevNode = nullptr;
}

void dList::deleteNode(void** node)
{
	typDoubleList_Node** delNode = (typDoubleList_Node**)node;

	if (node == nullptr || *node == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return;
	}
	else
	{
		delete (*delNode);
		*delNode = nullptr;
		return;
	}
}

void dList::printAll()
{
	if (this->printFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}

	typDoubleList_Node* currNode = this->doubleList_headNode;
	while (currNode != nullptr)
	{
		this->printFunc(currNode->data);
		currNode = (typDoubleList_Node*)this->get_nextNode(currNode);
	}
}

void* dList::lookUp(void* data)
{
	if (this->cmpFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}

	typDoubleList_Node* currNode = this->get_DoubleList_head();

	while (currNode != nullptr)
	{
		if (this->cmpFunc(this->get_Data(currNode), data) == EQUAL)
			return (void*)currNode;
		else
			currNode = (typDoubleList_Node*)this->get_nextNode(currNode);
	}

	return nullptr;
}

void dList::set_Data(void* node, void* data)
{
	typDoubleList_Node* temp = (typDoubleList_Node*)node;

	if (node == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else
	{
		temp->data = data;
	}
}

void* dList::get_Data(void* node)
{
	typDoubleList_Node* temp = (typDoubleList_Node*)node;

	if (node == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		return (void*)temp->data;
	}
}

void dList::destroyList()
{
	void* data = nullptr;

	while (this->getSize() > 0)
	{
		this->remove_tgtNode(this->get_DoubleList_head(), &data);
		this->freeDataFunc(data);
	}

	return;
}