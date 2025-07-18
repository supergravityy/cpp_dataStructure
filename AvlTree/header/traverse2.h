#pragma once

#include "bitreeNode.h"
#include "bitree.h"
#pragma comment (lib,"lib/biTree_debug.lib")
#include "avltree.h"
#include "avltreeNode.h"

namespace bitree_lookupTraverse
{
	void* preOrder(void* node, void** saveData);
	void* inOrder(void* node, void** saveData);
	void* postOrder(void* node, void** saveData);

	extern typCmpResult(*compareFunc)(const void* data1, const void* data2);
}

namespace bitree_printTraverse
{
	void preOrder(void* node);
	void inOrder(void* node);
	void postOrder(void* node);

	extern void (*printNodeFunc)(void* data);
}

namespace avltree_lookupTraverse
{
	void* preOrder(void* node, void** saveData);
	void* inOrder(void* node, void** saveData);
	void* postOrder(void* node, void** saveData);
	extern typCmpResult(*compareFunc)(const void* data1, const void* data2);
}

namespace avltree_printTraverse
{
	void preOrder(void* node);
	void inOrder(void* node);
	void postOrder(void* node);
	extern void (*printNodeFunc)(void* data);
}