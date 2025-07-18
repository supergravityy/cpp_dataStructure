#include "../header/bitree.h"

/*------------------------------------------*/
// Public (for User)
/*------------------------------------------*/

int BiTree::get_maxHeight()
{
	return cal_maxHeight(this->get_BiTreeRoot());
}
int BiTree::get_Size(void)
{
	return this->treeSize;
}
typErrcode BiTree::get_ErrCode(void)
{
	return this->errCode;
}
void* BiTree::lookup(void** saveData)
{
	if (this->traverseFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
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

/*------------------------------------------*/
// Protected (for Dev)
/*------------------------------------------*/

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
void BiTree::destroyTree()
{
	this->remove_left(nullptr); // remove all nodes at the beginning(root)
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
bool BiTree::is_emptyNode(void* node)
{
	return (node == nullptr);
}
bool BiTree::is_leafNode(void* node)
{
	return ((node != nullptr) && (((typBiTreeNode*)node)->left == nullptr) && (((typBiTreeNode*)node)->right == nullptr));
}