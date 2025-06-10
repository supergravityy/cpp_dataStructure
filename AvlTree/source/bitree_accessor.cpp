#include "../header/bitree.h"

typBiTreeNode* BiTree::get_BiTreeRoot()
{
	return this->BiTreeRoot;
}

bool BiTree::is_emptyNode(void* node)
{
	return (node == nullptr);
}

bool BiTree::is_leafNode(void* node)
{
	return ((node != nullptr) && (((typBiTreeNode*)node)->left == nullptr) && (((typBiTreeNode*)node)->right == nullptr));
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