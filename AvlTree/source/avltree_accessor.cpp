#include "../header/AVLtree.h"

void AvlTree::set_balFactor(typAvlTreeNode* node, typBalFactor balFactor)
{
	if (node != nullptr)
		node->balFactor = balFactor;
	else
		return;
}

void AvlTree::set_hiddenFlag(typAvlTreeNode* node, typHiddenFlag hiddenFlag)
{
	if (node != nullptr)
		node->hiddenFlag = hiddenFlag;
	else
		return;
}

typBalFactor AvlTree::get_balFactor(typAvlTreeNode* node)
{
	return node->balFactor;
}

typHiddenFlag AvlTree::get_hiddenFlag(typAvlTreeNode* node)
{
	return node->hiddenFlag;
}

typAvlTreeNode* AvlTree::get_AvlTreeRoot()
{
	return this->AvlTreeRoot;
}

/*Overriding parent's methods*/

void* AvlTree::get_leftPtr(void* node)
{
	if (node != nullptr)
		return ((typAvlTreeNode*)node)->left;
	else
		return nullptr;
}

void* AvlTree::get_rightPtr(void* node)
{
	if (node != nullptr)
		return ((typAvlTreeNode*)node)->right;
	else
		return nullptr;
}

void* AvlTree::get_data(void* node)
{
	if (node != nullptr)
		return ((typAvlTreeNode*)node)->data;
	else
		return nullptr;
}

bool AvlTree::is_leafNode(void* node)
{
	return ((node != nullptr) && (((typAvlTreeNode*)node)->left == nullptr) && (((typAvlTreeNode*)node)->right == nullptr));
}

void AvlTree::set_leftPtr(void* tgtNode, void* tgtAddr)
{
	if (tgtNode != nullptr)
		((typAvlTreeNode*)tgtNode)->left = (typAvlTreeNode*)tgtAddr;
	else
		return;
}

void AvlTree::set_rightPtr(void* tgtNode, void* tgtAddr)
{
	if (tgtNode != nullptr)
		((typAvlTreeNode*)tgtNode)->right = (typAvlTreeNode*)tgtAddr;
	else
		return;
}

void AvlTree::set_data(void* node, void* data)
{
	if (node != nullptr)
		((typAvlTreeNode*)node)->data = data;
	else
		return;
}