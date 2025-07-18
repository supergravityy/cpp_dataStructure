#include "../header/avltree.h"

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

int AvlTree::insert(const void* data)
{
	typBalancedFlag balanced = AVLNODE_BALANCED;

	if (data == nullptr)
	{
		this->errCode = SYS_FAULT;
		return INSERT_FAILED;
	}

	return this->recursive_insert(&this->AvlTreeRoot, data, &balanced);
}

bool AvlTree::remove(const void* data)
{
	if (data == nullptr)
	{
		return false;
	}
	else
	{
		return this->recursive_hide(this->AvlTreeRoot, data);
	}
}

bool AvlTree::search(void** data)
{
	if (data == nullptr || *data == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}

	return this->recursive_lookup(this->AvlTreeRoot, (void**)data);
}