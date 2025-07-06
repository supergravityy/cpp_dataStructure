#include "../header/traverse.h"

namespace lookupTraverse {
	typCmpResult(*compareFunc)(const void*, const void*) = nullptr;
}
namespace printTraverse {
	void (*printNodeFunc)(void*) = nullptr;
}

void* lookupTraverse::preOrder(void* rootNode, void** saveData)
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
		if (lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return (void*)stdNode;
		}
		else
		{
			tempNode = lookupTraverse::preOrder(stdNode->left, saveData);

			if (tempNode != nullptr)
				return tempNode;
			
			return lookupTraverse::preOrder(stdNode->right, saveData);
		}
	}
}

void* lookupTraverse::inOrder(void* rootNode, void** saveData)
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
		tempNode = lookupTraverse::inOrder(stdNode->left, saveData);
		if (tempNode != nullptr)
			return tempNode;

		if (lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return stdNode;
		}

		return lookupTraverse::inOrder(stdNode->right, saveData);
	}
}

void* lookupTraverse::postOrder(void* rootNode, void** saveData)
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
		tempNode1 = lookupTraverse::postOrder(stdNode->left, saveData);
		if (tempNode1 != nullptr)
			return tempNode1;

		tempNode2 = lookupTraverse::postOrder(stdNode->right, saveData);
		if (tempNode2 != nullptr)
			return tempNode2;

		if (lookupTraverse::compareFunc(*saveData, stdNode->data) == EQUAL)
		{
			*saveData = stdNode->data;
			return stdNode;
		}

		return nullptr;
	}
}

void printTraverse::preOrder(void* node)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)node;

	if (stdNode == nullptr || printTraverse::printNodeFunc == nullptr)
		return;
	else
	{
		printTraverse::printNodeFunc(stdNode->data);
		printTraverse::preOrder(stdNode->left);
		printTraverse::preOrder(stdNode->right);
	}
}

void printTraverse::inOrder(void* node)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)node;

	if (stdNode == nullptr || printTraverse::printNodeFunc == nullptr)
		return;

	else
	{
		printTraverse::inOrder(stdNode->left);
		printTraverse::printNodeFunc(stdNode->data);
		printTraverse::inOrder(stdNode->right);
	}
}

void printTraverse::postOrder(void* node)
{
	typBiTreeNode* stdNode = (typBiTreeNode*)node;

	if (stdNode == nullptr || printTraverse::printNodeFunc == nullptr)
		return;

	else
	{
		printTraverse::postOrder(stdNode->left);
		printTraverse::postOrder(stdNode->right);
		printTraverse::printNodeFunc(stdNode->data);
	}
}