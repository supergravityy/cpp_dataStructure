#include "../header/cList.h"

cList::cList()
{
	this->circularList_head = nullptr;
}

cList::~cList()
{
	this->destroyList(); // 메모리 해제 먼저 -> 부모클래스의 destroy는 아무것도 없어서 생략됨
	this->circularList_head = nullptr;
}

bool cList::push_front(void* data)
{
	return this->pushFront(data);
}

bool cList::pop_front(void** saveData)
{
	return this->popFront(saveData);
}

bool cList::pushBack(void* data)
{
	// 이 메서드는 List 클래스에서만 사용되도록 제한됨
	return false;
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

			// 원형노드에는 tail 포인터가 없다.
		}

		this->size++;
		return true;
	}
}

bool cList::removeNext(void* node, void** saveData)
{
	typCircularList_Node* oldNode = nullptr, *tgtNode = (typCircularList_Node*)node;
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

		this->deleteNode((void**) &oldNode);								// 5. oldNode 삭제
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
			this->remove_nextNode(this->get_CircularList_head(),&data);
			this->freeDataFunc(data);
		}

		return;
	}
}

void* cList::findTail()
{
	typCircularList_Node* tgtNode = this->get_CircularList_head();
	typCircularList_Node* tgtNextNode = nullptr;

	if (this->getSize() == 0)
		return nullptr;
	else if (this->getSize() == 1)
		return (void*)tgtNode; // 리스트에 노드가 하나만 있다면, 헤드노드가 tail 노드임
	else
	{
		tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);

		while (tgtNextNode != this->get_CircularList_head())					// 1. tgtNode의 nextNode가 자기자신이 아닐 때까지 반복
		{
			tgtNode = tgtNextNode;												// 2. tgtNode를 다음 노드로 이동
			tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);	// 3. tgtNextNode를 다음 노드로 이동
		}

		return (void*)tgtNode;													// 4. 이제 tgtNode는 리스트의 마지막 노드이므로, 그 노드를 반환
	}
}

bool cList::pushFront(void* data)
{
	// 마지막 노드를 찾아, 그 다음에 새 노드를 삽입 
	return this->insert_nextNode(this->findTail(), data);	
}

bool cList::popFront(void** saveData)
{
	// 마지막 노드의 다음 노드를 삭제 => 마지막 노드의 다음노드 = 헤드
	return this->removeNext(this->findTail(), saveData);
}