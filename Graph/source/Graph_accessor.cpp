#include "../header/Graph.h"

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
	singleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;
	List* nodeList = this->get_adjListsAddr();
	if (data == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}

	node = this->adjLists.get_SingleList_head();
	while (node != nullptr) 
	{
		adjListNode = (typAdjList*)node->data;

		if (this->compareFunc(data, adjListNode->vertex) == EQUAL) 
		{
			return adjListNode; // ��ġ�ϴ� ��� ��ȯ
		}
		else
		{
			node = (singleList_Node*)nodeList->get_nextNode(node);
		}
	}
	return nullptr; // ��ġ�ϴ� ��尡 ���� ���
}

singleList_Node* Graph::get_prevNodeOf(void* data)
{
	singleList_Node* node = nullptr, * prevNode= nullptr;
	typAdjList* adjListNode = nullptr;
	List* nodeList = this->get_adjListsAddr();
	if (data == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}

	node = this->adjLists.get_SingleList_head();
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
			node = (singleList_Node*)nodeList->get_nextNode(node);
		}
	}
	return nullptr; // ��ġ�ϴ� ��尡 ���� ���
}