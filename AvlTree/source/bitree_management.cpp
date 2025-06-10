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

bool BiTree::merge(void* leftTree, void* rightTree, void* data)
{
	BiTree* left = (BiTree*)leftTree, * right = (BiTree*)rightTree;
	typBiTreeNode* tempNode = nullptr;

	// 1. insert data in
	if (this->insert_left(nullptr, data) != 0)
	{
		this->init(this->compareFunc, this->printFunc, this->destroyDataFunc);
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

void BiTree::printAll()
{
	if (this->treeSize == 0 || this->get_BiTreeRoot() == nullptr)
		return;

	this->preOrder_printNode(this->get_BiTreeRoot()); // call the recursive function
}