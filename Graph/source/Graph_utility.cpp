#include "../header/Graph.h"

void* dummyFunction(void* data)
{
	// Dummy function to avoid unused parameter warning
	return nullptr;
}

void dummyDestroy(void* data)
{
	return;
}

int Graph::get_vertexCnt() 
{
	return this->vertexCnt;
}
int Graph::get_edgeCnt() 
{
	return this->edgeCnt;
}
typGraphType Graph::get_type() 
{
	return this->type;
}
typErrcode Graph::get_errCode() 
{
	return this->errCode;
}
void* Graph::find_vertex(void** saveData)
{
	singleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;
	adjListNode = this->get_adjListNode(*saveData);

	if (adjListNode == nullptr)
	{
		return nullptr; // 일치하는 노드가 없을 경우
	}
	else
	{
		return this->get_nodeVertex(adjListNode); // 일치하는 노드의 vertex 반환
	}
}

void* Graph::make_node(void* data) 
{
	typAdjList* newNode = new typAdjList;
	if (newNode == nullptr) 
	{
		this->errCode = MEMORY_ERR;
		return nullptr;
	}
	return (void*)newNode;
}
void Graph::init_node(typAdjList* node, void* data) 
{
	if (node == nullptr || data == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else if (this->compareFunc == nullptr || this->printDataFunc == nullptr || this->destroyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else
	{
		this->set_nodeVertex(node, data); // 노드의 vertex 데이터 설정
		this->clearAdjacents(node);
	}
}
void* Graph::delete_node(typAdjList* node) 
{
	void* temp = nullptr;
	if (node == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		temp = this->get_nodeVertex(node);
		this->clearAdjacents(node);
		delete node;
		return temp;
	}
}
void Graph::clearAdjacents(typAdjList* node)
{
	if (node == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else
	{
		this->edgeCnt -= node->Adjacents.getSize();
		node->Adjacents.init(this->compareFunc, this->printDataFunc, dummyDestroy, dummyFunction);
	}
}

bool Graph::is_vertexReferenced(void* data)
{
	singleList_Node* node;
	List* nodeList = this->get_adjListsAddr();
	typAdjList* adjListNode = nullptr;

	for (node = nodeList->get_SingleList_head(); node != NULL; node = (singleList_Node*)nodeList->get_nextNode(node))
	{
		adjListNode = (typAdjList*)nodeList->get_Data(node);

		if(adjListNode->Adjacents.isMember(data) == true)
			return true; // data가 다른 노드의 인접노드로 사용중인 경우
	}
	return false;
}
bool Graph::is_Adjacent(void* srcData, void* destData)
{
	singleList_Node* node = nullptr, * prev = nullptr;
	typAdjList* adjListNode = this->get_adjListNode(srcData);

	if (adjListNode == nullptr)
		return false;
	else
		return adjListNode->Adjacents.isMember(destData);
}
void Graph::destroy() 
{
	typAdjList* temp_adjListNode = nullptr;
	Set* temp_Adjacents = nullptr;
	void* temp_Vertex = nullptr, *temp_data = nullptr;
	int nodeEdgeCnt = 0;

	if (this->destroyDataFunc == nullptr)
	{
		return;
	}

	while (this->adjLists.getSize() > 0)
	{
		if (this->adjLists.remove_nextNode(nullptr, (void**)&temp_adjListNode) == true)
		{
			//this->edgeCnt -= temp_adjListNode->Adjacents.getSize();
			temp_data = this->delete_node(temp_adjListNode);	// 노드 삭제
			this->destroyDataFunc(temp_data);					// 노드에 저장된 데이터 삭제
		}
		else
		{
			this->errCode = SYS_FAULT;
			this->adjLists.destroyList();
			return;
		}
		this->vertexCnt--;
	}
	this->adjLists.destroyList();
}

