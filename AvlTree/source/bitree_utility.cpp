#include "../header/bitree.h"

void BiTree::destroyTree()
{
	this->remove_left(nullptr); // remove all nodes at the beginning(root)
}

bool BiTree::init(typCmpResult (*compareFunc)(const void* key1, const void* key2)
	, void (*printFunc)(const void* data)
	, void (*destroyDataFunc)(void* data))
{
	if(compareFunc == nullptr || printFunc == nullptr || destroyDataFunc == nullptr)
		return false;

	else
	{
		this->destroyTree();

		this->BiTreeRoot = nullptr;
		this->treeSize = 0;
		this->compareFunc = compareFunc;
		this->printFunc = printFunc;
		this->destroyDataFunc = destroyDataFunc;
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

BiTree::BiTree()
{
	this->BiTreeRoot = nullptr;
	this->treeSize = 0;
	this->compareFunc = nullptr;
	this->printFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->errCode = NORMAL;
}

BiTree::~BiTree()
{
	this->destroyTree();

	this->BiTreeRoot = nullptr;
	this->treeSize = 0;
	this->compareFunc = nullptr;
	this->printFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->errCode = NORMAL;
}

int BiTree::insert_left(void* node, const void* data)
{

	typBiTreeNode* newNode = nullptr, * targetNode = (typBiTreeNode*)node,
		** position = nullptr;

	if (targetNode == nullptr)
	{
		if (this->treeSize == 0)
			position = &this->BiTreeRoot;
		else
		{
			this->errCode = SYS_FAULT;
			return INSERT_FAILED;
		}
	}
	else
	{
		if (!this->is_emptyNode(targetNode->left))
		{
			this->errCode = SYS_FAULT;
			return INSERT_CHILD_EXISTS;
		}
		else
			position = &targetNode->left;
	}

	this->makeNode((void**)&newNode);
	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return INSERT_MEMORY_ERR;
	}
	else
	{
		this->initNode(newNode, (void*)data);
		*position = newNode;
		this->treeSize++;
		return INSERT_SUCCESS;
	}
}

int BiTree::insert_right(void* node, const void* data)
{
	typBiTreeNode* newNode = nullptr, * targetNode = (typBiTreeNode*)node,
		** position = nullptr;

	if (targetNode == nullptr)
	{
		if (this->treeSize == 0)
			position = &this->BiTreeRoot;
		else
		{
			this->errCode = SYS_FAULT;
			return INSERT_FAILED;
		}
	}
	else
	{
		if (!this->is_emptyNode(targetNode->right))
		{
			this->errCode = SYS_FAULT;
			return INSERT_CHILD_EXISTS;
		}
		else
			position = &targetNode->right;
	}

	this->makeNode((void**)&newNode);
	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return INSERT_MEMORY_ERR;
	}
	else
	{
		this->initNode(newNode, (void*)data);
		*position = newNode;
		this->treeSize++;
		return INSERT_SUCCESS;
	}
}

bool BiTree::remove_left(void* node)
{
	typBiTreeNode** target = nullptr, * targetNode = (typBiTreeNode*)node;
	bool result = false;

	if (this->treeSize == 0)
		return result;
	else
	{
		if (this->is_emptyNode(targetNode))
			target = &this->BiTreeRoot;
		else
			target = &targetNode->left;
	}

	if (!this->is_emptyNode(targetNode))
	{
		this->remove_left(*target);
		this->remove_right(*target);
		this->deleteNode((void**)target);

		result = true;
	}
	return result;
}

bool BiTree::remove_right(void* node)
{
	typBiTreeNode** target = nullptr, * targetNode = (typBiTreeNode*)node;
	bool result = false;

	if (this->treeSize == 0)
		return result;
	else
	{
		if (targetNode == nullptr)
			target = &this->BiTreeRoot;
		else
			target = &targetNode->right;
	}

	if (!this->is_emptyNode(targetNode))
	{
		this->remove_left(*target);
		this->remove_right(*target);
		this->deleteNode((void**)target);

		result = true;
	}
	return result;
}