#include "../header/traverse2.h"

namespace bitree_lookupTraverse {
	typCmpResult(*compareFunc)(const void*, const void*) = nullptr;
}
namespace bitree_printTraverse {
	void (*printNodeFunc)(void*) = nullptr;
}

namespace avltree_lookupTraverse {
	typCmpResult(*compareFunc)(const void*, const void*) = nullptr;
}

namespace avltree_printTraverse {
	void (*printNodeFunc)(void*) = nullptr;
}

// BiTree Traversal Functions

void* bitree_lookupTraverse::preOrder(void* rootNode, void** saveData)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)rootNode;
	void* tempNode = nullptr;

	if (rootNode == nullptr)
	{
		return nullptr;
	}
	else if (saveData == nullptr || *saveData == nullptr || compareFunc == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (bitree_lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return (void*)stdNode;
		}
		else
		{
			tempNode = bitree_lookupTraverse::preOrder(stdNode->left, saveData);

			if (tempNode != nullptr)
				return tempNode;
			
			return bitree_lookupTraverse::preOrder(stdNode->right, saveData);
		}
	}
}

void* bitree_lookupTraverse::inOrder(void* rootNode, void** saveData)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)rootNode;
	void* tempNode = nullptr;

	if (rootNode == nullptr)
	{
		return nullptr;
	}
	else if (saveData == nullptr || *saveData == nullptr || compareFunc == nullptr)
	{
		return nullptr;
	}
	else
	{
		tempNode = bitree_lookupTraverse::inOrder(stdNode->left, saveData);
		if (tempNode != nullptr)
			return tempNode;

		if (bitree_lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return stdNode;
		}

		return bitree_lookupTraverse::inOrder(stdNode->right, saveData);
	}
}

void* bitree_lookupTraverse::postOrder(void* rootNode, void** saveData)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)rootNode;
	void* tempNode1 = nullptr, *tempNode2 = nullptr;

	if (rootNode == nullptr)
	{
		return nullptr;
	}
	else if (saveData == nullptr || *saveData == nullptr || compareFunc == nullptr)
	{
		return nullptr;
	}
	else
	{
		tempNode1 = bitree_lookupTraverse::postOrder(stdNode->left, saveData);
		if (tempNode1 != nullptr)
			return tempNode1;

		tempNode2 = bitree_lookupTraverse::postOrder(stdNode->right, saveData);
		if (tempNode2 != nullptr)
			return tempNode2;

		if (bitree_lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return stdNode;
		}

		return nullptr;
	}
}

void bitree_printTraverse::preOrder(void* node)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)node;

	if (stdNode == nullptr || bitree_printTraverse::printNodeFunc == nullptr)
		return;
	else
	{
		bitree_printTraverse::printNodeFunc(stdNode->data);
		bitree_printTraverse::preOrder(stdNode->left);
		bitree_printTraverse::preOrder(stdNode->right);
	}
}

void bitree_printTraverse::inOrder(void* node)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)node;

	if (stdNode == nullptr || bitree_printTraverse::printNodeFunc == nullptr)
		return;

	else
	{
		bitree_printTraverse::inOrder(stdNode->left);
		bitree_printTraverse::printNodeFunc(stdNode->data);
		bitree_printTraverse::inOrder(stdNode->right);
	}
}

void bitree_printTraverse::postOrder(void* node)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)node;

	if (stdNode == nullptr || bitree_printTraverse::printNodeFunc == nullptr)
		return;

	else
	{
		bitree_printTraverse::postOrder(stdNode->left);
		bitree_printTraverse::postOrder(stdNode->right);
		bitree_printTraverse::printNodeFunc(stdNode->data);
	}
}

// AVL Tree Traversal Functions

void* avltree_lookupTraverse::preOrder(void* rootNode, void** saveData)
{
	typAvlTreeNode* stdNode = (typAvlTreeNode*)rootNode;
	void* tempNode = nullptr;

	if (rootNode == nullptr)
	{
		return nullptr;
	}
	else if (saveData == nullptr || *saveData == nullptr || compareFunc == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (avltree_lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return (void*)stdNode;
		}
		else
		{
			tempNode = avltree_lookupTraverse::preOrder(stdNode->left, saveData);

			if (tempNode != nullptr)
				return tempNode;

			return avltree_lookupTraverse::preOrder(stdNode->right, saveData);
		}
	}
}

void* avltree_lookupTraverse::inOrder(void* rootNode, void** saveData)
{
	typAvlTreeNode* stdNode = (typAvlTreeNode*)rootNode;
	void* tempNode = nullptr;

	if (rootNode == nullptr)
	{
		return nullptr;
	}
	else if (saveData == nullptr || *saveData == nullptr || compareFunc == nullptr)
	{
		return nullptr;
	}
	else
	{
		tempNode = avltree_lookupTraverse::inOrder(stdNode->left, saveData);
		if (tempNode != nullptr)
			return tempNode;

		if (avltree_lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return stdNode;
		}

		return avltree_lookupTraverse::inOrder(stdNode->right, saveData);
	}
}

void* avltree_lookupTraverse::postOrder(void* rootNode, void** saveData)
{
	typAvlTreeNode* stdNode = (typAvlTreeNode*)rootNode;
	void* tempNode1 = nullptr, * tempNode2 = nullptr;

	if (rootNode == nullptr)
	{
		return nullptr;
	}
	else if (saveData == nullptr || *saveData == nullptr || compareFunc == nullptr)
	{
		return nullptr;
	}
	else
	{
		tempNode1 = avltree_lookupTraverse::postOrder(stdNode->left, saveData);
		if (tempNode1 != nullptr)
			return tempNode1;

		tempNode2 = avltree_lookupTraverse::postOrder(stdNode->right, saveData);
		if (tempNode2 != nullptr)
			return tempNode2;

		if (avltree_lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return stdNode;
		}

		return nullptr;
	}
}

void avltree_printTraverse::preOrder(void* node)
{
	typAvlTreeNode* stdNode = (typAvlTreeNode*)node;

	if (stdNode == nullptr || avltree_printTraverse::printNodeFunc == nullptr)
		return;
	else
	{
		if (stdNode->hiddenFlag == NODE_AVAILABLE)
			avltree_printTraverse::printNodeFunc(stdNode->data);
		
		avltree_printTraverse::preOrder(stdNode->left);
		avltree_printTraverse::preOrder(stdNode->right);
	}
}

void avltree_printTraverse::inOrder(void* node)
{
	typAvlTreeNode* stdNode = (typAvlTreeNode*)node;

	if (stdNode == nullptr || avltree_printTraverse::printNodeFunc == nullptr)
		return;

	else
	{
		avltree_printTraverse::inOrder(stdNode->left);
		if(stdNode->hiddenFlag == NODE_AVAILABLE)
			avltree_printTraverse::printNodeFunc(stdNode->data);
		avltree_printTraverse::inOrder(stdNode->right);
	}
}

void avltree_printTraverse::postOrder(void* node)
{
	typAvlTreeNode* stdNode = (typAvlTreeNode*)node;

	if (stdNode == nullptr || avltree_printTraverse::printNodeFunc == nullptr)
		return;

	else
	{
		avltree_printTraverse::postOrder(stdNode->left);
		avltree_printTraverse::postOrder(stdNode->right);
		if (stdNode->hiddenFlag == NODE_AVAILABLE)
			avltree_printTraverse::printNodeFunc(stdNode->data);
	}
}