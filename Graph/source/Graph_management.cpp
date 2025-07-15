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

	if (this->get_adjListNode(data) != nullptr) // �ߺ�üũ
	{
		return false;
	}

	newAdjList = (typAdjList*)this->make_node(data); // �� ��� ����
	if (newAdjList == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else
	{
		this->init_node(newAdjList, data);
		
		result = this->adjLists.push_back(newAdjList);	// �� ������带 ���Ḯ��Ʈ�� �߰�
		if (result == false)
		{
			this->delete_node(newAdjList);	// ���� ���н� ��� ����

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
		this->get_adjListNode(srcData) == nullptr) // src, dest �� �׷����� �����ϴ��� Ȯ��
	{
		return false; 
	}
	else
	{
		srcAdjList = this->get_adjListNode(srcData);  // srcData�� ������� ����Ʈ�� get

		if (srcAdjList->Adjacents.insert(destData) == false) // srcData�� ������忡 destData�� �߰�
		{
			return false; // srcData�� ������忡 destData�� �߰� ���н� false ��ȯ
		}
		else
		{
			if (this->type == UNDIRECTED) // ������ �׷����Ͻ�
			{
				destAdjList = this->get_adjListNode(destData); // destData�� ������� ����Ʈ�� get
				if (destAdjList->Adjacents.insert(srcData) == false) // destData�� ������忡 srcData�� �߰�
				{
					void* rollback = destData;
					this->remove_edge(srcData, &rollback);			// �����ϸ�, ������ src->dest ���� ����
					return false;
				}

				this->edgeCnt++; // ������׷����� ����⿧���� ���ۿ� ����. + ����ڰ� �ϳ��� ������� �ֱ⿡ 2������
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

	if (this->adjLists.getSize() == 0) // �׷����� ������� ���
	{
		return false;
	}
	else
	{
		adjListNode = this->get_adjListNode(*saveData); // ������ ����� ������� ����Ʈ�� ������
		prevNode = this->get_prevNodeOf(*saveData);

		if(this->is_vertexReferenced(*saveData) == true)
			return false; // �ش� ������ �ٸ� ������ �������� ������� ���
		else if (adjListNode->Adjacents.getSize() != 0)
			return false; // �ش� ������ ������尡 �����ϴ� ���
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
		// src, dest �� �׷����� �����ϴ��� Ȯ��
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
		return false; // data�� nullptr�� ���
	}
	else
	{
		for (node = nodeList->get_SingleList_head(); node != nullptr; node = (singleList_Node*)nodeList->get_nextNode(node))
		{
			adjListNode = (typAdjList*)nodeList->get_Data(node);

			if(adjListNode->Adjacents.remove(data, &tempData))
			{
				this->edgeCnt--; // ������� ����Ʈ���� data�� ��� ����
			}
		}
		return true; // ��� ������� ���� ����
	}
}

bool Graph::clear_NodesEdges_of(void* data)
{
	typAdjList* adjListNode = this->get_adjListNode(data);

	if (data == nullptr || adjListNode == nullptr) 
	{
		this->errCode = SYS_FAULT;
		return false; // data�� nullptr�̰ų� �׷����� �������� �ʴ� ���
	}
	else
	{
		clearAdjacents(adjListNode); // �ش� ����� ������� ����Ʈ�� ���

		return true; // ������� ����Ʈ ���� ����
	}
}

bool Graph::safeRemove_vertex(void** saveData)
{
	if (saveData == nullptr || *saveData == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}

	// �׷����� ������ �����ϴ��� ���� Ȯ��
	if (this->get_adjListNode(*saveData) == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}

	// 1. �ٸ� ������ �� ��带 �����ϴ� ��� ���� ����
	if (this->clear_allEdges_of(*saveData) == false)
	{
		return false; // ���ο��� errCode ������
	}

	// 2. �� ��尡 �����ϰ� �ִ� ��� ���� ����
	if (this->clear_NodesEdges_of(*saveData) == false)
	{
		return false; // ���ο��� errCode ������
	}

	// 3. ���������� ���� ��ü ����
	if (this->remove_vertex(saveData) == false)
	{
		return false; // ���ο��� errCode ������
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