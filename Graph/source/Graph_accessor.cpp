#include "../header/Graph.h"

/*------------------------------------------*/
// Iterator (for User)
/*------------------------------------------*/

const void* Graph::begin()
{
	return (const void*)this->adjLists.begin();
}
const void* Graph::end()
{
	return (const void*)this->adjLists.end();
}
const void* Graph::next(void* node)
{
	return (const void*)this->adjLists.next(node);
}
const void* Graph::data(void* node)
{
	return this->adjLists.data(node);
}

/*------------------------------------------*/
// Accessor (for Dev)
/*------------------------------------------*/

List* Graph::get_adjListsAddr() 
{
	return &this->adjLists; // ���Ḯ��Ʈ �ּ� ��ȯ
}

void* Graph::get_nodeVertex(void* data) 
{
	typAdjList* adjListNode = this->get_adjListNode(data);
	if (adjListNode == nullptr)
	{
		return nullptr; // ��ġ�ϴ� ��尡 ���� ���
	}
	else
	{
		return adjListNode->vertex;
	}
}

void Graph::set_nodeVertex(typAdjList* node, void* data) 
{
	if (node == nullptr || data == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else
	{
		node->vertex = data; // ����� vertex ������ ����
	}
}

typAdjList* Graph::get_adjListNode(void* data) 
{
	typSingleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;
	List* nodeList = this->get_adjListsAddr();
	if (data == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}

	node = (singleList_Node*)this->adjLists.begin();
	while (node != nullptr) 
	{
		adjListNode = (typAdjList*)node->data;

		if (this->compareFunc(data, adjListNode->vertex) == EQUAL) 
		{
			return adjListNode; // ��ġ�ϴ� ��� ��ȯ
		}
		else
		{
			node = (singleList_Node*)nodeList->next(node);
		}
	}
	return nullptr; // ��ġ�ϴ� ��尡 ���� ���
}

singleList_Node* Graph::get_prevNodeOf(void* data)
{
	typSingleList_Node* node = nullptr, * prevNode= nullptr;
	typAdjList* adjListNode = nullptr;
	List* nodeList = this->get_adjListsAddr();
	if (data == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}

	node = (typSingleList_Node*)this->adjLists.begin();
	while (node != nullptr)
	{
		adjListNode = (typAdjList*)node->data;

		if (this->compareFunc(data, adjListNode->vertex) == EQUAL)
		{
			return prevNode;
		}
		else
		{
			prevNode = node; // ���� ��� ����
			node = (typSingleList_Node*)nodeList->next(node);
		}
	}
	return nullptr; // ��ġ�ϴ� ��尡 ���� ���
}