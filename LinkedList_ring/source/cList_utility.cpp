#include "../header/cList.h"

/*------------------------------------------*/
// Public (for User)
/*------------------------------------------*/

void cList::printAll()
{
	typCircularList_Node* currNode = this->circularList_head;

	if (this->printFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else if (this->getSize() == 0)
	{
		return;
	}
	else
	{
		do
		{
			this->printFunc(currNode->data);
			currNode = currNode->nextNode;
		} while (currNode != this->circularList_head);

		return;
	}
}

/*------------------------------------------*/
// Protected (for Dev)
/*------------------------------------------*/

void* cList::makeNode()
{
	typCircularList_Node* newNode = new typCircularList_Node;

	return newNode;
}

void cList::initNode(void* node, void* data)
{
	typCircularList_Node* temp = (typCircularList_Node*)node;

	temp->data = data;
	temp->nextNode = nullptr;
}

void cList::deleteNode(void** node)
{
	typCircularList_Node** delNode = (typCircularList_Node**)node;

	if (node == nullptr || *node == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return;
	}
	else
	{
		delete (*delNode);
		*delNode = nullptr;
		return;
	}
}

bool cList::pushFront(void* data)
{
	// 마지막 노드를 찾아, 그 다음에 새 노드를 삽입 
	return this->insert_nextNode((void*)this->end(), data);
}

bool cList::popFront(void** saveData)
{
	// 마지막 노드의 다음 노드를 삭제 => 마지막 노드의 다음노드 = 헤드
	return this->removeNext((void*)this->end(), saveData);
}

bool cList::insertNext(void* node, void* data)
{
	typCircularList_Node* tgtNode = (typCircularList_Node*)node;
	typCircularList_Node* tgtNextNode = nullptr;
	typCircularList_Node* newNode = (typCircularList_Node*)this->makeNode();

	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else
	{
		this->initNode(newNode, data);								// 1. 노드 초기화

		if (this->getSize() == 0)									// 2. 리스트가 비어있다면
		{
			this->set_nextNode(newNode, newNode);					// 3. 새노드의 nextNode			-> 자기자신
			this->set_CircularList_head(newNode);					// 4. 헤드노드 설정
		}
		else														// 2-1. 리스트가 비어있지 않다면
		{
			tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);

			this->set_nextNode(newNode, tgtNextNode);				// 3. 새노드의 nextNode			-> tgtNode의 nextNode
			this->set_nextNode(tgtNode, newNode);					// 4. tgtNode의 nextNode			-> 새노드

			if (this->get_CircularList_head() == tgtNextNode)		// 5. tgtNode의 nextNode가 헤드노드라면 head 업데이트
				this->set_CircularList_head(newNode);
		}

		this->size++;
		return true;
	}
}

bool cList::removeNext(void* node, void** saveData)
{
	typCircularList_Node* oldNode = nullptr, * tgtNode = (typCircularList_Node*)node;
	typCircularList_Node* tgtNextNode = nullptr;

	if (this->getSize() == 0)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);
		*saveData = this->get_Data((void*)tgtNextNode);						// 1. 삭제할 노드의 데이터를 저장

		if (tgtNextNode == tgtNode)											// 2. 지정노드의 nextNode가 자기자신 => 리스트에 노드가 하나남음
		{
			oldNode = tgtNode;												// 3. oldNode에 삭제할 노드 저장
			this->set_CircularList_head(nullptr);							// 4. 헤드노드 비우기
		}
		else																// 2-1. 리스트에 노드가 여러개 있음												
		{
			oldNode = tgtNextNode;											// 3. oldNode에 삭제할 노드 저장
			this->set_nextNode(tgtNode, this->get_nextNode(oldNode));		// 4. 지정노드의 nextNode		-> 진짜 삭제할 대상의 nextNode

			if (oldNode == this->get_CircularList_head())					// 헤드노드가 삭제되는 경우, 헤드노드를 다음 노드로 변경
				this->set_CircularList_head((typCircularList_Node*)this->get_nextNode(oldNode));
		}

		this->deleteNode((void**)&oldNode);								// 5. oldNode 삭제
		this->size--;

		return true;
	}
}

void cList::destroyList()
{
	typCircularList_Node* head = this->get_CircularList_head();
	void* data = nullptr;

	if (this->freeDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else if (this->is_emptyNode(head) && this->getSize() > 0)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else
	{
		while (this->getSize() > 0)
		{
			this->remove_nextNode(this->get_CircularList_head(), &data);
			this->freeDataFunc(data);
		}

		return;
	}
}

void* cList::lookUp(void* data)
{
	typCircularList_Node* currNode = this->circularList_head;

	if (this->cmpFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else if (this->getSize() == 0)
	{
		return nullptr;
	}
	else
	{
		do
		{
			if (this->cmpFunc(currNode->data, data) == EQUAL)
				return (void*)currNode;
			else
				currNode = currNode->nextNode;
		} while (currNode != this->circularList_head);

		return nullptr;
	}
}