#pragma once

#include "Libs.h"
#include "ListNode.h"
#include "List.h"
// stack

class Stack : public List
{
public:
	/*Management*/
	Stack();
	~Stack();

	bool Push(void* data);
	bool Pop(void** data);
	const void* Peek();

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
	using List::insert_nextNode;
	using List::remove_nextNode;
};

