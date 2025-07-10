#include "../header/bitree.h"

void BiTree::destroyTree()
{
	this->remove_left(nullptr); // remove all nodes at the beginning(root)
}

int BiTree::get_maxHeight()
{
	int temp = cal_maxHeight(this->get_BiTreeRoot());

	return temp;
}

void BiTree::printAll()
{
	if (this->printTreeFunc == nullptr)
		this->errCode = SYS_FAULT;
	else
		this->printTreeFunc(this->get_BiTreeRoot());
}

bool BiTree::init(typCmpResult (*compareFunc)(const void* key1, const void* key2)
	, void (*printFunc)(void* node)
	, void (*destroyDataFunc)(void* data)
	, void* (*traverseFunc)(void* node, void** saveData))
{
	if(compareFunc == nullptr || printFunc == nullptr || destroyDataFunc == nullptr || traverseFunc == nullptr)
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

int BiTree::get_Size(void)
{
	return this->treeSize;
}

typErrcode BiTree::get_ErrCode(void)
{
	return this->errCode;
}

void BiTree::initNode(void* node, void* data)
{
	this->set_data(node, data);
	this->set_leftPtr(node, nullptr);
	this->set_rightPtr(node, nullptr);
}

bool BiTree::makeNode(void** node)
{
	typBiTreeNode *temp = new typBiTreeNode;

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

bool BiTree::deleteNode(void** node)
{
	if (node == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false; 
	}
	else
	{
		if (this->destroyDataFunc != nullptr)
		{
			this->destroyDataFunc(((typBiTreeNode*)*node)->data);
			delete *node;
			*node = nullptr;
			this->treeSize--;

			return true;
		}
		else
		{
			this->errCode = SYS_FAULT;
			return false;
		}
	}
}

int BiTree::cal_maxHeight(void* node)
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

#ifdef DEBUG
typBiTreeNode* BiTree::get_bitreeRoot_Addr()
{
	return this->get_BiTreeRoot();
}
typBiTreeNode* BiTree::get_leftAddr(void* node)
{
	return (typBiTreeNode*)this->get_leftPtr(node);
}
typBiTreeNode* BiTree::get_rightAddr(void* node)
{
	return (typBiTreeNode*)this->get_rightPtr(node);
}
#endif // DEBUG