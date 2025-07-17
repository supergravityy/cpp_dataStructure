#include "../header/List.h"

/*------------------------------------------*/
// Iterator (for User)
/*------------------------------------------*/

const typSingleList_Node* List::begin()
{
	return (const typSingleList_Node*)this->get_SingleList_head();
}
const typSingleList_Node* List::end()
{
	return (const typSingleList_Node*)this->get_SingleList_tail();
}
const typSingleList_Node* List::next(const typSingleList_Node* node)
{
	return (const typSingleList_Node*)this->get_nextNode((void*) node);
}
const void* List::data(const void* userData)
{
	return (const void*)this->get_Data((void*)userData);
}

/*------------------------------------------*/
// Iterator (for Dev)
/*------------------------------------------*/

typSingleList_Node* List::get_SingleList_head()
{
	return this->singleList_head;
}

void List::set_SingleList_head(typSingleList_Node* node)
{
	this->singleList_head = node;
}

typSingleList_Node* List::get_SingleList_tail()
{
	return this->singleList_tail;
}

void List::set_SingleList_tail(typSingleList_Node* node)
{
	this->singleList_tail = node;
}

bool List::is_emptyNode(void* node)
{
	return node == nullptr;
}

void List::set_Data(void* node, void* data)
{
	typSingleList_Node* tempNode = (typSingleList_Node*)node;
	tempNode->data = data;
}

void* List::get_Data(void* node)
{
	return ((typSingleList_Node*)node)->data;
}

void List::set_nextNode(void* tgtNode, void* tgtAddr)
{
		typSingleList_Node* tempNode = (typSingleList_Node*)tgtNode;
		tempNode->nextNode = (typSingleList_Node*)tgtAddr;
}
void* List::get_nextNode(void* node)
{
	return ((typSingleList_Node*)node)->nextNode;
}