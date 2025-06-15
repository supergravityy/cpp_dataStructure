#include "../header/List.h"

void* List::makeNode(void)
{
	typSingleList_Node* newNode = new typSingleList_Node;

	return newNode;
}

void List::initNode(void* node, void* data)
{
	typSingleList_Node* temp = (typSingleList_Node*)node;
	temp->data = data;
	temp->nextNode = nullptr;
}

void List::deleteNode(void** node)  
{
    typSingleList_Node** delNode = (typSingleList_Node**)node;  

	if (node == nullptr || *node == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return;
	}
	else
	{
		//this->freeDataFunc((*delNode)->data);
		delete	(*delNode);
		*delNode = nullptr;
		return;
	}
}

void List::printAll()
{
	if (this->printFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
		
	typSingleList_Node* current = this->singleList_head;
	while (current != nullptr)
	{
		this->printFunc(current->data);
		current = (typSingleList_Node*)this->get_nextNode(current);
	}
}

int List::getSize()
{
	return this->size;
}

typErrcode List::getErrCode()
{
	return this->errCode;
}

void List::destroyList()
{
	typSingleList_Node* nextNode = nullptr, *current = this->get_SingleList_head();
	void* data = nullptr;

	while (this->getSize() > 0)
	{
		this->removeNext(nullptr,&data);
		this->freeDataFunc(data);
	}

	return;
}

#ifdef fordebug
void* List::get_headAddr()
{
	return (void*)this->get_SingleList_head();
}
void* List::get_nextAddr(void* node)
{
	return this->get_nextNode((typSingleList_Node*)node);
}
#endif 