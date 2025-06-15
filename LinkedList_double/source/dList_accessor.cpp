#include "../header/dList.h"

typDoubleList_Node* dList::get_DoubleList_head()
{
	return this->doubleList_headNode;
}

void dList::set_DoubleList_head(typDoubleList_Node* node)
{
	this->doubleList_headNode = node;
}

typDoubleList_Node* dList::get_DoubleList_tail()
{
	return this->doubleList_tailNode;
}

void dList::set_DoubleList_tail(typDoubleList_Node* node)
{
	this->doubleList_tailNode = node;
}

void* dList::get_nextNode(void* node)
{
	typDoubleList_Node* temp = (typDoubleList_Node*)node;
	return (void*)temp->nextNode;
}

void dList::set_nextNode(void* tgtNode, void* tgtAddr)
{
	typDoubleList_Node* temp = (typDoubleList_Node*)tgtNode;
	temp->nextNode = (typDoubleList_Node*)tgtAddr;
}

void* dList::get_prevNode(void* node)
{
	typDoubleList_Node* temp = (typDoubleList_Node*)node;
	return (void*)temp->prevNode;
}

void dList::set_prevNode(void* tgtNode, void* tgtAddr)
{
	typDoubleList_Node* temp = (typDoubleList_Node*)tgtNode;
	temp->prevNode = (typDoubleList_Node*)tgtAddr;
}