#include "../header/bitree.h"

bool BiTree::preOrder(typBiTreeNode* node, void* targetData)
{
	if (this->is_emptyNode(node) || targetData == nullptr)
	{
		return false;
	}
	else
	{
		if (this->compareFunc(targetData, node->data))
			return true;
		
		else
		{
			if (this->preOrder((typBiTreeNode*)this->get_leftPtr(node), targetData))
				return true;
			
			return this->preOrder((typBiTreeNode*)this->get_rightPtr(node), targetData);
		}
	}
}

bool BiTree::inOrder(typBiTreeNode* node, void* targetData)
{
	if (this->is_emptyNode(node) || targetData == nullptr)
	{
		return false;
	}
	else
	{
		if (this->inOrder((typBiTreeNode*)this->get_leftPtr(node), targetData))
			return true;
		if (this->compareFunc(targetData, node->data))
			return true;
		return this->preOrder((typBiTreeNode*)this->get_rightPtr(node), targetData);
	}
}

bool BiTree::postOrder(typBiTreeNode* node, void* targetData)
{
	if (this->is_emptyNode(node) || targetData == nullptr)
	{
		return false;
	}
	else
	{
		if (this->postOrder((typBiTreeNode*)this->get_leftPtr(node), targetData))
			return true;
		if (this->postOrder((typBiTreeNode*)this->get_rightPtr(node), targetData))
			return true;

		return this->compareFunc(targetData, node->data);
	}
}

void BiTree::preOrder_printNode(typBiTreeNode* node)
{
	if (node == nullptr)
		return;
	if (node->data != nullptr)
	{
		this->printFunc(node->data);
	}
	preOrder_printNode(node->left);
	preOrder_printNode(node->right);
}