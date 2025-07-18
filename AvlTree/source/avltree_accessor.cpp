#include "../header/avltree.h"

/*------------------------------------------*/
// Iterator (for User)
/*------------------------------------------*/

const void* AvlTree::begin()
{
	return (const void*)this->get_AvlTreeRoot();
}
const void* AvlTree::next(void* node) // preOrder style
{
    void* retNode = nullptr;
    void* rightNode = nullptr;

    while (true)
    {
        if ((retNode = this->get_leftPtr(node)) != nullptr)
        {
            this->parentsAddrs.push(node);

            if (this->get_hiddenFlag((typAvlTreeNode*)retNode) != NODE_HIDDEN) 
                return (const void*)retNode;
            else
                node = retNode; // 만약, 다음의 노드가 숨김상태면, 루프 한번더
        }
        else if ((retNode = this->get_rightPtr(node)) != nullptr)
        {
            this->parentsAddrs.push(node);
            if (this->get_hiddenFlag((typAvlTreeNode*)retNode) != NODE_HIDDEN)
                return (const void*)retNode;
            else
                node = retNode; // 만약, 다음의 노드가 숨김상태면, 루프 한번더
        }
        else if (this->parentsAddrs.getSize() > 0)
        {
            if (this->parentsAddrs.pop(&retNode) == false)
            {
                this->errCode = SYS_FAULT;
                return nullptr;
            }
            else
            {
                rightNode = this->get_rightPtr(retNode);
                if (rightNode != nullptr)
                {
                    if (this->get_hiddenFlag((typAvlTreeNode*)rightNode) != NODE_HIDDEN)
                        return (const void*)rightNode;
                    else
                        node = rightNode; // 만약, 다음의 노드가 숨김상태면, 루프 한번더
                }
                else
                    return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }
}
#ifdef forDebug
void AvlTree::hidenode(void* node)
{
    this->set_hiddenFlag((typAvlTreeNode*)node, NODE_HIDDEN);
}
#endif // forDebug

/*------------------------------------------*/
// Accessor (for Dev)
/*------------------------------------------*/

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

void AvlTree::set_AvlTreeRoot(typAvlTreeNode* node)
{
	this->AvlTreeRoot = node;
}

/*------------------------------------------*/
// Overriding parent's Accessor (for Dev)
/*------------------------------------------*/

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