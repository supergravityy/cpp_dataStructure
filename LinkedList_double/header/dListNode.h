#pragma once

#include "ListNode.h"

typedef struct DoubleList_Node
{
	void* data;
    DoubleList_Node* nextNode;
    DoubleList_Node* prevNode;
}typDoubleList_Node;

