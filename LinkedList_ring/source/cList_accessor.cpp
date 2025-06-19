#include "../header/cList.h"

typCircularList_Node* cList::get_CircularList_head()
{
	return this->circularList_head;
}

void cList::set_CircularList_head(typCircularList_Node* head)
{
	this->circularList_head = head;
}

void cList::set_nextNode(void* tgtNode, void* tgtAddr)
{
	typCircularList_Node* node = (typCircularList_Node*)tgtNode;
	node->nextNode = (typCircularList_Node*)tgtAddr;
}

void* cList::get_nextNode(void* tgtNode)
{
	typCircularList_Node* node = (typCircularList_Node*)tgtNode;
	return (void*)node->nextNode;
}