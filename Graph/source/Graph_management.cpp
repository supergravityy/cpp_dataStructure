#include "../header/Graph.h"

Graph::Graph() 
{
	this->type = DIRECTED;
	this->vertexCnt = 0;
	this->edgeCnt = 0;
	this->errCode = NORMAL;
	this->compareFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->printDataFunc = nullptr;
}
Graph::~Graph() 
{
	this->destroy();

	this->type = DIRECTED;
	this->vertexCnt = 0;
	this->edgeCnt = 0;
	this->errCode = NORMAL;
	this->compareFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->printDataFunc = nullptr;
}
bool Graph::init(typCmpResult(*compareFunc)(const void* key1, const void* key2),
	void (*destroyDataFunc)(void* data), void (*printDataFunc)(const void* data), typGraphType type)
{
	if(compareFunc == nullptr || destroyDataFunc == nullptr || printDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->destroy();

		this->compareFunc = compareFunc;
		this->destroyDataFunc = destroyDataFunc;
		this->printDataFunc = printDataFunc;
		this->type = type;
		this->adjLists.init(compareFunc, printDataFunc, destroyDataFunc);

		return true;
	}	
}

bool Graph::insert_vertex(void* data)
{
	typAdjList* newAdjList;
	bool result;

	if (this->get_adjListNode(data) != nullptr) // 중복체크
	{
		return false;
	}

	newAdjList = (typAdjList*)this->make_node(data); // 새 노드 생성
	if (newAdjList == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else
	{
		this->init_node(newAdjList, data);
		
		result = this->adjLists.push_back(newAdjList);	// 새 인접노드를 연결리스트에 추가
		if (result == false)
		{
			this->delete_node(newAdjList);	// 삽입 실패시 노드 삭제

			return false;
		}
		else
		{
			this->vertexCnt++;
			return true;
		}
	}
}

bool Graph::insert_edge(void* srcData, void* destData)
{
	typAdjList* srcAdjList, *destAdjList;

	if (this->get_adjListNode(destData) == nullptr ||
		this->get_adjListNode(srcData) == nullptr) // src, dest 가 그래프에 존재하는지 확인
	{
		return false; 
	}
	else
	{
		srcAdjList = this->get_adjListNode(srcData);  // srcData의 인접노드 리스트를 get

		if (srcAdjList->Adjacents.insert(destData) == false) // srcData의 인접노드에 destData를 추가
		{
			return false; // srcData의 인접노드에 destData를 추가 실패시 false 반환
		}
		else
		{
			if (this->type == UNDIRECTED) // 무방향 그래프일시
			{
				destAdjList = this->get_adjListNode(destData); // destData의 인접노드 리스트를 get
				if (destAdjList->Adjacents.insert(srcData) == false) // destData의 인접노드에 srcData를 추가
				{
					void* rollback = destData;
					this->remove_edge(srcData, &rollback);			// 실패하면, 기존의 src->dest 엣지 삭제
					return false;
				}

				this->edgeCnt++; // 무방향그래프는 양방향엣지일 수밖에 없음. + 사용자가 하나만 지울수도 있기에 2배증가
			}
			this->edgeCnt++;
			return true; 
		}
	}
}

bool Graph::remove_vertex(void** saveData)
{
	singleList_Node* node = nullptr, * temp = nullptr, * prevNode = nullptr;
	typAdjList* adjListNode = nullptr;
	void* tempData = nullptr;
	List* nodeList = this->get_adjListsAddr();

	if (this->adjLists.getSize() == 0) // 그래프가 비어있을 경우
	{
		return false;
	}
	else
	{
		adjListNode = this->get_adjListNode(*saveData); // 삭제할 노드의 인접노드 리스트를 가져옴
		prevNode = this->get_prevNodeOf(*saveData);

		if(this->is_vertexReferenced(*saveData) == true)
			return false; // 해당 정점이 다른 정점의 인접노드로 사용중인 경우
		else if (adjListNode->Adjacents.getSize() != 0)
			return false; // 해당 정점의 인접노드가 존재하는 경우
		else
		{
			if (nodeList->remove_nextNode(prevNode, &tempData) == false)
			{
				this->errCode = nodeList->getErrCode();
				return false;
			}
			else
			{
				*saveData = this->delete_node((typAdjList*)tempData);

				this->vertexCnt--;
				return true;
			}
		}
	}
}

bool Graph::remove_edge(void* srcData, void** destData)
{
	singleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;

	adjListNode = this->get_adjListNode(srcData);

	if (adjListNode == nullptr || this->get_adjListNode(*destData) == nullptr) 
		// src, dest 가 그래프에 존재하는지 확인
	{
		return false; 
	}
	else
	{
		if (adjListNode->Adjacents.remove(*destData, destData) == false)
		{
			return false;
		}
		else
		{
			this->edgeCnt--;
			return true;
		}
	}
}

bool Graph::clear_allEdges_of(void* data)
{
	singleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;
	List* nodeList = this->get_adjListsAddr();
	void* tempData = nullptr;

	if (data == nullptr || this->get_adjListNode(data) == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false; // data가 nullptr인 경우
	}
	else
	{
		for (node = nodeList->get_SingleList_head(); node != nullptr; node = (singleList_Node*)nodeList->get_nextNode(node))
		{
			adjListNode = (typAdjList*)nodeList->get_Data(node);

			if(adjListNode->Adjacents.remove(data, &tempData))
			{
				this->edgeCnt--; // 인접노드 리스트에서 data를 모두 제거
			}
		}
		return true; // 모든 인접노드 제거 성공
	}
}

bool Graph::clear_NodesEdges_of(void* data)
{
	typAdjList* adjListNode = this->get_adjListNode(data);

	if (data == nullptr || adjListNode == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return false; // data가 nullptr이거나 그래프에 존재하지 않는 경우
	}
	else
	{
		clearAdjacents(adjListNode); // 해당 노드의 인접노드 리스트를 비움

		return true; // 인접노드 리스트 비우기 성공
	}
}

bool Graph::safeRemove_vertex(void** saveData)
{
	if (saveData == nullptr || *saveData == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}

	// 그래프에 정점이 존재하는지 먼저 확인
	if (this->get_adjListNode(*saveData) == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}

	// 1. 다른 노드들이 이 노드를 참조하는 모든 엣지 제거
	if (this->clear_allEdges_of(*saveData) == false)
	{
		return false; // 내부에서 errCode 설정됨
	}

	// 2. 이 노드가 참조하고 있는 모든 엣지 제거
	if (this->clear_NodesEdges_of(*saveData) == false)
	{
		return false; // 내부에서 errCode 설정됨
	}

	// 3. 최종적으로 정점 자체 제거
	if (this->remove_vertex(saveData) == false)
	{
		return false; // 내부에서 errCode 설정됨
	}

	return true;
}

void Graph::printGraph()
{
	singleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;
	List* nodeList = this->get_adjListsAddr();
	int num = 0;

	if (nodeList->getSize() == 0) 
	{
		return;
	}
	for (node = nodeList->get_SingleList_head(); node != nullptr; node = (singleList_Node*)nodeList->get_nextNode(node))
	{
		adjListNode = (typAdjList*)nodeList->get_Data(node);
		printf("\n[Vertex %d] ", num);

		this->printDataFunc(adjListNode->vertex);
		printf("-> Adjacents\n ");
		adjListNode->Adjacents.printAll();

		num++;
	}
}