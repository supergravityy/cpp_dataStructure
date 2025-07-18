#include "../header/bitree.h"

/*------------------------------------------*/
// Iterator (for User)
/*------------------------------------------*/

const void* BiTree::begin()
{
	return (const void*)this->get_BiTreeRoot();
}
const void* BiTree::leftChild(void* node)
{
	return (const void*)this->get_leftPtr(node);
}
const void* BiTree::rightChild(void* node)
{
	return (const void*)this->get_rightPtr(node);
}
const void* BiTree::data(void* node)
{
	return (const void*)this->get_data(node);
}

/*------------------------------------------*/
// Accessor (for Dev)
/*------------------------------------------*/

typBiTreeNode* BiTree::get_BiTreeRoot()
{
	return this->BiTreeRoot;
}

void* BiTree::get_leftPtr(void* node)
{
	if (node != nullptr)
		return ((typBiTreeNode*)node)->left;
	else
		return nullptr;
}

void* BiTree::get_rightPtr(void* node)
{
	if (node != nullptr)
		return ((typBiTreeNode*)node)->right;
	else
		return nullptr;
}

void* BiTree::get_data(void* node)
{
	if (node != nullptr)
		return ((typBiTreeNode*)node)->data;
	else
		return nullptr;
}

void BiTree::set_leftPtr(void* tgtNode, void* tgtAddr)
{
	if (tgtNode != nullptr)
		((typBiTreeNode*)tgtNode)->left = (typBiTreeNode*)tgtAddr;
	else
		return;
}

void BiTree::set_rightPtr(void* tgtNode, void* tgtAddr)
{
	if (tgtNode != nullptr)
		((typBiTreeNode*)tgtNode)->right = (typBiTreeNode*)tgtAddr;
	else
		return;
}

void BiTree::set_data(void* node, void* data)
{
	if (node != nullptr)
		((typBiTreeNode*)node)->data = data;
	else
		return;
}