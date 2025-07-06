#pragma once

#include "bitreeNode.h"
#include "bitree.h"

namespace lookupTraverse
{
	void* preOrder(void* node, void** saveData);
	void* inOrder(void* node, void** saveData);
	void* postOrder(void* node, void** saveData);

	extern typCmpResult(*compareFunc)(const void* data1, const void* data2);
}

namespace printTraverse
{
	void preOrder(void* node);
	void inOrder(void* node);
	void postOrder(void* node);

	extern void (*printNodeFunc)(void* data);
}