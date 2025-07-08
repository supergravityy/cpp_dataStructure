#include "../header/avltree.h"

void AvlTree::destroyTree()
{
	this->destroy_left(nullptr); // 모든 노드 삭제

	return;
}

int AvlTree::get_maxHeight()
{
	int temp = cal_maxHeight(this->get_AvlTreeRoot());

	if (temp > 0)
		return temp - 1;
	else
		return temp;
}

int AvlTree::cal_maxHeight(void* node)
{
	int tempLeftHeight = 0, tempRightHeight = 0;

	if (node == nullptr)
	{
		this->errCode = SYS_FAULT;
		return 0;
	}
	else
	{
		tempLeftHeight = this->cal_maxHeight(this->get_leftPtr(node));
		tempRightHeight = this->cal_maxHeight(this->get_rightPtr(node));

		return 1 + std::max(tempLeftHeight, tempRightHeight);
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

void AvlTree::printAll()
{
	if (this->printTreeFunc == nullptr)
		this->errCode = SYS_FAULT;
	else
		this->printTreeFunc(this->get_AvlTreeRoot());
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
	this->printTreeFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->errCode = NORMAL;
}