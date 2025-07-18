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
	return &this->adjLists; // 연결리스트 주소 반환
}

void* Graph::get_nodeVertex(void* data) 
{
	typAdjList* adjListNode = this->get_adjListNode(data);
	if (adjListNode == nullptr)
	{
		return nullptr; // 일치하는 노드가 없을 경우
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
		node->vertex = data; // 노드의 vertex 데이터 설정
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
			return adjListNode; // 일치하는 노드 반환
		}
		else
		{
			node = (singleList_Node*)nodeList->next(node);
		}
	}
	return nullptr; // 일치하는 노드가 없을 경우
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
			prevNode = node; // 이전 노드 저장
			node = (typSingleList_Node*)nodeList->next(node);
		}
	}
	return nullptr; // 일치하는 노드가 없을 경우
}