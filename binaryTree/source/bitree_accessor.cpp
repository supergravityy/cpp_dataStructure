#include "../header/bitree.h"
#include "../header/Stack.h"

/*------------------------------------------*/
// Iterator (for User)
/*------------------------------------------*/

typCmpResult dummyCmpFunc(const void* key1, const void* key2)
{
	return EQUAL;
}
void dummyPrintFunc(const void* data)
{
	return;
}
void dummyDestroyFunc(void* data) 
{
	// 리스트의 노드에는 트리노드의 주소가 들어있기에 삭제금지
	return;
}

const void* BiTree::begin()
{
	return (const void*)this->get_BiTreeRoot();
}
const void* BiTree::data(void* node)
{
	return (const void*)this->get_data(node);
}
const void* BiTree::end()
{
	return nullptr;
}
const void* BiTree::next(void* node) // preOrder style
{
	void* retNode = nullptr;

	if ((retNode = this->get_leftPtr(node)) != nullptr)
	{
		this->parentsAddrs.push(node);
		return (const void*)retNode;
	}
	else if ((retNode = this->get_rightPtr(node)) != nullptr)
	{
		this->parentsAddrs.push(node);
		return (const void*)retNode;
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
			return (const void*)this->get_rightPtr(retNode);
		}
	}
	else
	{
		return nullptr;
	}
}
void BiTree::reset_iter()
{
	this->parentsAddrs.init(dummyCmpFunc, dummyPrintFunc, dummyDestroyFunc);
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