#include "../header/AVLtree.h"

void AvlTree::destroyTree()
{
	this->destroy_left(nullptr); // remove all nodes at the beginning(root)

	return;
}

bool AvlTree::init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
	, void (*printFunc)(const void* data)
	, void (*destroyDataFunc)(void* data))
{
	if (compareFunc == nullptr || printFunc == nullptr || destroyDataFunc == nullptr)
		return false;

	else
	{
		this->destroyTree(); // remove all nodes at the beginning(root)

		this->AvlTreeRoot = nullptr;
		this->treeSize = 0;
		this->compareFunc = compareFunc;
		this->printFunc = printFunc;
		this->destroyDataFunc = destroyDataFunc;
		this->errCode = NORMAL;
		return true;
	}
}

void AvlTree::initNode(void* node, void* data)
{
	this->set_data(node, data);
	this->set_leftPtr(node, nullptr);
	this->set_rightPtr(node, nullptr);
	this->set_balFactor((typAvlTreeNode*)node, AVL_BALANCED);
	this->set_hiddenFlag((typAvlTreeNode*)node, NODE_AVAILABLE);
}

bool AvlTree::makeNode(void** node)
{
	typAvlTreeNode* temp = new typAvlTreeNode;
	if (temp == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else
	{
		*node = temp;
		return true;
	}
}

bool AvlTree::deleteNode(void** node)
{
	if (node == nullptr || *node == nullptr)
		return false;

	delete* node;
	*node = nullptr;
	this->treeSize--;

	return true;
}

AvlTree::AvlTree()
{
	// already initialized in BiTree constructor
	this->AvlTreeRoot = nullptr;
}

AvlTree::~AvlTree()
{
	// after destruction of AvlTree, the BiTree destructor will be called
	// this->destroyTree(); -> this will be called in parents destructor

	this->AvlTreeRoot = nullptr;
	this->treeSize = 0;
	this->compareFunc = nullptr;
	this->printFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->errCode = NORMAL;
}