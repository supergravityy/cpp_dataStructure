#pragma once

#include "List.h"
#pragma comment (lib,"lib/singleLinkedList_debug.lib")
// stack

class Stack : public List
{
public:
	/*Management*/
	Stack();
	~Stack();
	bool push(void* data);
	bool pop(void** data);
	const void* peek();

	/*Utility*/
protected:
	/*Utility-1*/

	/*Accessor*/
private:

	/* Hide */
	using List::set_Data;
	using List::get_Data;
	using List::lookup_Node;
	using List::push_back;
	using List::push_front;
	using List::insert_nextNode;
	using List::remove_nextNode;
};

