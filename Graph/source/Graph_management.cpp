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

	if (this->get_adjListNode(data) != nullptr)				// 1. 인접리스트가 중복으로 존재하는지를 체크
	{
		return false;
	}

	newAdjList = (typAdjList*)this->make_node(data);		// 2. 새 인접리스트 노드 생성 및 초기화
	if (newAdjList == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else
	{
		this->init_node(newAdjList, data);
		
		result = this->adjLists.push_back(newAdjList);		// 3. 새 인접노드를 연결리스트에 추가
		if (result == false)
		{
			this->delete_node(newAdjList);

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
		this->get_adjListNode(srcData) == nullptr)						// 1. src, dest 가 그래프에 존재하는지 확인
	{
		return false; 
	}
	else if ((this->get_type() == UNDIRECTED) && (srcData == destData)) // 1a. 무방향 그래프 일때는 자기자신으로의 엣지는 금지됨
	{
		return false;
	}
	else
	{
		srcAdjList = this->get_adjListNode(srcData);					// 2. srcData의 인접노드 리스트를 get

		if (srcAdjList->Adjacents.insert(destData) == false)			// 3. srcData의 인접노드에 destData를 추가
		{
			return false; 
		}
		else
		{
			if (this->type == UNDIRECTED)								// 3a. 무방향 그래프일시
			{
				destAdjList = this->get_adjListNode(destData);			// 3b. destData의 인접노드 리스트를 get
				if (destAdjList->Adjacents.insert(srcData) == false)	// 3c. destData의 인접노드에 srcData를 추가
				{
					void* rollback = destData;
					this->remove_edge(&srcData, &rollback);				// 3d. 실패하면, 기존의 src->dest 엣지 삭제
					return false;
				}

				this->edgeCnt++;										// 3e. 엣지갯수 증가
			}
			this->edgeCnt++;											// 4. 엣지갯수 증가
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

	if (this->adjLists.getSize() == 0)										// 1. 그래프가 비어있을 경우 곧바로 종료
	{
		return false;
	}
	else
	{
		adjListNode = this->get_adjListNode(*saveData);						// 2. 삭제할 노드의 인접리스트 노드를 가져옴
		prevNode = this->get_prevNodeOf(*saveData);							// 3. 삭제할 노드의 이전 노드를 가져옴

		if (this->is_vertexReferenced(*saveData) == true)					// 4. 해당 정점이 다른 정점의 인접리스트에서 참조중인지를 체크
			return false;
		else if (adjListNode->Adjacents.getSize() != 0)						// 5. 해당 정점의 인접노드리스트가 비어있는지를 체크
			return false;
		else
		{
			if (nodeList->remove_nextNode(prevNode, &tempData) == false)	// 6. 대상 인접리스트노드 삭제
			{
				this->errCode = nodeList->getErrCode();
				return false;
			}
			else
			{
				*saveData = this->delete_node((typAdjList*)tempData);		// 7. 대상 인접리스트 삭제처리

				this->vertexCnt--;
				return true;
			}
		}
	}
}

bool Graph::remove_edge(void** srcData, void** destData)
{
	singleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;

	adjListNode = this->get_adjListNode(*srcData);

	if (adjListNode == nullptr || this->get_adjListNode(*destData) == nullptr)		// 1. src, dest 가 그래프에 존재하는지 확인
	{
		return false; 
	}
	else
	{
		if (adjListNode->Adjacents.remove(*destData, destData) == false)			// 2. src의 인접리스트에서 dest를 삭제 
		{
			this->errCode = adjListNode->Adjacents.getErrCode();
			return false;
		}
		else
		{
			this->edgeCnt--;														// 3. 엣지카운트 감소 (src의 엣지)

			if (this->get_type() == UNDIRECTED)										// 4a. 무방향 그래프일시
			{
				adjListNode = this->get_adjListNode(*destData);						// 4b. dest 노드 get

				if (adjListNode->Adjacents.remove(*srcData, srcData) == false)		// 4c. dest의 인접리스트에서 src 삭제
				{
					this->errCode = adjListNode->Adjacents.getErrCode();
					return false;
				}
				else
				{
					this->edgeCnt--;												// 4d. 엣지카운트 감소 (dest의 엣지)
				}
			}
		}
	}

	return true;
}

bool Graph::clear_allEdges_of(void* data)
{
	typSingleList_Node* node = nullptr;
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
		for (node = (typSingleList_Node*)nodeList->begin(); node != nullptr; node = (typSingleList_Node*)nodeList->next(node))
		{
			adjListNode = (typAdjList*)nodeList->data(node);

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
	typSingleList_Node* node = nullptr;
	typAdjList* adjListNode = nullptr;
	List* nodeList = this->get_adjListsAddr();
	int num = 0;

	if (nodeList->getSize() == 0) 
	{
		return;
	}
	for (node = (typSingleList_Node*)nodeList->begin(); node != nullptr; node = (typSingleList_Node*)nodeList->next(node))
	{
		adjListNode = (typAdjList*)nodeList->data(node);
		printf("\n[Vertex %d] ", num);

		this->printDataFunc(adjListNode->vertex);
		printf("-> Adjacents\n ");
		adjListNode->Adjacents.printAll();

		num++;
	}
}