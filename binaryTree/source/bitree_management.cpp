#include "../header/bitree.h"

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

int BiTree::insert_left(void* node, const void* data)
{
	typBiTreeNode* newNode = nullptr, 
		* targetNode = (typBiTreeNode*)node,
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

	if (!this->is_emptyNode(*target))
	{
		this->remove_left(*target);
		this->remove_right(*target);
		this->deleteNode((void**)target);
		this->treeSize--;

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

	if (!this->is_emptyNode(*target))
	{
		this->remove_left(*target);
		this->remove_right(*target);
		this->deleteNode((void**)target);
		this->treeSize--;

		result = true;
	}
	return result;
}

bool BiTree::merge(void* leftTree, void* rightTree, void* data)
{
	BiTree* left = (BiTree*)leftTree, * right = (BiTree*)rightTree;
	typBiTreeNode* tempNode = nullptr;

	// 1. insert data in
	if (this->insert_left(nullptr, data) != 0)
	{
		this->init(this->compareFunc, this->printTreeFunc, this->destroyDataFunc, this->traverseFunc);
		return false;
	}

	// 2. merge Trees as subTree of newRoot
	else
	{
		tempNode = this->get_BiTreeRoot();
		this->set_leftPtr(tempNode, left->get_BiTreeRoot());
		this->set_rightPtr(tempNode, right->get_BiTreeRoot());

		// 3. update size of new tree
		this->treeSize += left->get_Size() + right->get_Size();

		// 4. inhibit access of original Trees to newMerge Tree
		left->BiTreeRoot = nullptr;
		left->treeSize = 0;
		right->BiTreeRoot = nullptr;
		right->treeSize = 0;

		return true;
	}
}

bool BiTree::lookup(void** saveData)
{
	if (this->traverseFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
		return this->traverseFunc(this->get_BiTreeRoot(), saveData);
}

void BiTree::printAll()
{
	if (this->printTreeFunc == nullptr)
		this->errCode = SYS_FAULT;
	else
		this->printTreeFunc(this->get_BiTreeRoot());
}