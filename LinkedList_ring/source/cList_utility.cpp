#include "../header/cList.h"

void* cList::makeNode()
{
	typCircularList_Node* newNode = new typCircularList_Node;

	return newNode;
}

void cList::initNode(void* node, void* data)
{
	typCircularList_Node* temp = (typCircularList_Node*)node;

	temp->data = data;
	temp->nextNode = nullptr;
}

void cList::deleteNode(void** node)
{
	typCircularList_Node** delNode = (typCircularList_Node**)node;

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

void* cList::get_Data(void* node)
{
	typCircularList_Node* temp = (typCircularList_Node*)node;

	return temp->data;
}

void  cList::set_Data(void* node, void* data)
{
	typCircularList_Node* temp = (typCircularList_Node*)node;

	temp->data = data;
	return;
}

void cList::printAll()
{
	typCircularList_Node* currNode = this->circularList_head;

	if (this->printFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else if (this->getSize() == 0)
	{
		return;
	}
	else
	{
		do
		{
			this->printFunc(currNode->data);
			currNode = currNode->nextNode;
		} while (currNode != this->circularList_head);

		return;
	}
}

void* cList::lookUp(void* data)
{
	typCircularList_Node* currNode = this->circularList_head;

	if (this->cmpFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else if (this->getSize() == 0)
	{
		return nullptr;
	}
	else
	{
		do
		{
			if (this->cmpFunc(currNode->data, data) == EQUAL)
				return (void*)currNode;
			else
				currNode = currNode->nextNode;
		} while (currNode != this->circularList_head);

		return nullptr;
	}
}