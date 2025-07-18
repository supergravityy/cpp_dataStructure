#include "../header/bitree.h"

BiTree::BiTree()
{
	this->BiTreeRoot = nullptr;
	this->treeSize = 0;
	this->compareFunc = nullptr;
	this->printTreeFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->errCode = NORMAL;
}
BiTree::~BiTree()
{
	this->destroyTree();

	this->BiTreeRoot = nullptr;
	this->treeSize = 0;
	this->compareFunc = nullptr;
	this->printTreeFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->errCode = NORMAL;
}

bool BiTree::init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
	, void (*printFunc)(void* node)
	, void (*destroyDataFunc)(void* data)
	, void* (*traverseFunc)(void* node, void** saveData))
{
	if (compareFunc == nullptr || printFunc == nullptr || destroyDataFunc == nullptr || traverseFunc == nullptr)
		return false;

	else
	{
		this->destroyTree();

		this->BiTreeRoot = nullptr;
		this->treeSize = 0;
		this->compareFunc = compareFunc;
		this->printTreeFunc = printFunc;
		this->destroyDataFunc = destroyDataFunc;
		this->traverseFunc = traverseFunc;
		this->errCode = NORMAL;
		return true;
	}
}

int BiTree::insert_leftChild(void* node, const void* data)
{
	return this->insert_left(node, data);
}

int BiTree::insert_rightChild(void* node, const void* data)
{
	return this->insert_right(node, data);
}

bool BiTree::remove_leftChild(void* node)
{
	return this->remove_left(node);
}

bool BiTree::remove_rightChild(void* node)
{
	return this->remove_right(node);
}

bool BiTree::mergeTree(void* leftTree, void* rightTree, void* data)
{
	return this->merge(leftTree, rightTree, data);
}