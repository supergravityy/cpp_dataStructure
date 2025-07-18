#include "../header/Graph.h"

void* dummyFunction(void* data)
{
	// 초기화용 더미함수
	return nullptr;
}
void dummyDestroy(void* data)
{
	return;
}

/*------------------------------------------*/
// Public (for User)
/*------------------------------------------*/

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
	typSingleList_Node* node = nullptr;
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

/*------------------------------------------*/
// Protected (for Dev)
/*------------------------------------------*/

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
	typSingleList_Node* node;
	List* nodeList = this->get_adjListsAddr();
	typAdjList* adjListNode = nullptr;

	for (node = (typSingleList_Node*)nodeList->begin(); node != NULL; node = (typSingleList_Node*)nodeList->next(node))
	{
		adjListNode = (typAdjList*)nodeList->data(node);

		if(adjListNode->Adjacents.isMember(data) == true)
			return true; // data가 다른 노드의 인접노드로 사용중인 경우
	}
	return false;
}
bool Graph::is_Adjacent(void* srcData, void* destData)
{
	typSingleList_Node* node = nullptr, * prev = nullptr;
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
			temp_data = this->delete_node(temp_adjListNode);	// 노드 삭제
			this->destroyDataFunc(temp_data);					// 노드에 저장된 데이터 삭제
		}
		else
		{
			this->errCode = SYS_FAULT;
			this->adjLists.init(this->compareFunc, this->printDataFunc, this->destroyDataFunc);
			return;
		}
		this->vertexCnt--;
	}
	this->adjLists.init(this->compareFunc, this->printDataFunc, this->destroyDataFunc);
}