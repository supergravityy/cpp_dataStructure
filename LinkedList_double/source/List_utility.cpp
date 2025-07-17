#include "../header/List.h"
/*------------------------------------------*/
// Public (for User)
/*------------------------------------------*/

void List::printAll()
{
	if (this->printFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}

	typSingleList_Node* current = this->singleList_head;
	while (current != nullptr)
	{
		this->printFunc(current->data);
		current = (typSingleList_Node*)this->get_nextNode(current);
	}
}

int List::getSize()
{
	return this->size;
}

typErrcode List::getErrCode()
{
	return this->errCode;
}

/*------------------------------------------*/
// Public (for Dev)
/*------------------------------------------*/

void* List::makeNode(void)
{
	typSingleList_Node* newNode = new typSingleList_Node;

	return newNode;
}

void List::initNode(void* node, void* data)
{
	typSingleList_Node* temp = (typSingleList_Node*)node;
	temp->data = data;
	temp->nextNode = nullptr;
}

void List::deleteNode(void** node)
{
	typSingleList_Node** delNode = (typSingleList_Node**)node;

	if (node == nullptr || *node == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return;
	}
	else
	{
		delete	(*delNode);
		*delNode = nullptr;
		return;
	}
}

bool List::insertNext(void* node, void* data)
{
	typSingleList_Node* prevNode, * newNode = nullptr, * tempNode = nullptr;
	prevNode = (typSingleList_Node*)node;


	if (data == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		newNode = (typSingleList_Node*)this->makeNode();
		if (newNode == nullptr)
		{
			this->errCode = MEMORY_ERR;
			return false;
		}

		this->initNode(newNode, data);

		if (this->is_emptyNode(prevNode))										// 1. 이전노드가 null 일때
		{
			if (this->getSize() == 0)											// 2. 리스트가 비어있을 때		-> head == tail
				this->set_SingleList_tail(newNode);
			else {}																// 2-1. 리스트가 비어있지 않을 때	-> head != tail

			this->set_nextNode(newNode, (void*)this->get_SingleList_head());	// 3. newNode의 next			-> head	
			this->set_SingleList_head(newNode);									// 4. head 포인터 업데이트
		}

		else																	// 1-1. 이전노드가 null이 아닐 때	=> (중간에 삽입하고 싶다)
		{
			tempNode = (typSingleList_Node*)this->get_nextNode(prevNode);		// 2. prevNode의 next를 tempNode에 임시저장
			this->set_nextNode(prevNode, newNode);								// 3. prevNode와 그 다음 노드 사이에 newNode 삽입
			this->set_nextNode(newNode, tempNode);

			if (tempNode == nullptr)											// 4. tempNode가 null이면 tail 업데이트
				this->set_SingleList_tail(newNode);
			else {}
		}
		this->size++;															// 5. size+1
		return true;

	}
}

bool List::removeNext(void* node, void** saveData)
{
	typSingleList_Node* prevNode, * targetNode;
	prevNode = (typSingleList_Node*)node;

	if (this->getSize() == 0)
	{
		return false;
	}

	else if (prevNode == nullptr)	// 이전노드가 null	=>	head 노드 삭제
	{
		targetNode = this->get_SingleList_head();											// 1. 삭제대상				=> head 노드

		*saveData = this->get_Data(targetNode);												// 2. 삭제할 노드의 data를 data변수에 저장
		this->set_SingleList_head((typSingleList_Node*)this->get_nextNode(targetNode));		// 3. head 포인터 업데이트	=> head 노드의 next

		if (this->getSize() == 1)
			this->set_SingleList_tail(nullptr);												// 4. 삭제 후 리스트가 비어있으면 tail도 null로 설정
		else {}
	}
	else							// 이전노드가 null이 아닐 때	=> 중간 노드 삭제
	{
		if (this->get_nextNode(prevNode) == nullptr) // 이전노드가 tail 노드일 때, 다음노드가 없으므로 삭제 불가능
		{
			this->errCode = SYS_FAULT;
			return false;
		}
		else
		{
			targetNode = (typSingleList_Node*)this->get_nextNode(prevNode);					// 1. 삭제대상				=> prevNode의 next 노드

			*saveData = this->get_Data(targetNode);											// 2. 삭제할 노드의 data를 data변수에 저장
			this->set_nextNode(prevNode, this->get_nextNode(targetNode));					// 3. prevNode의 next		-> targetNode의 next로 업데이트 (=> prev노드의 다음노드만 삭제됨)

			if (this->get_nextNode(targetNode) == nullptr)									// 4. targetNode의 next가 null이면 tail 업데이트
				this->set_SingleList_tail(prevNode);
			else {}
		}
	}

	this->deleteNode((void**)&targetNode);	// 5. 삭제대상 노드 메모리 해제 (내부 data는 메서드가 종료되고 사용자가 직접 판단)
	this->size--;

	return true;
}

void* List::lookUp(void* data)
{
	if (this->cmpFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}

	typSingleList_Node* currentNode = this->get_SingleList_head();

	while (currentNode != nullptr)										// head부터 시작하여 리스트의 끝까지 순회
	{
		if (this->cmpFunc(this->get_Data(currentNode), data) == EQUAL)	// 데이터가 일치하는지 비교
			return (void*)currentNode;									// 일치하는 노드주소 반환
		else
			currentNode = (typSingleList_Node*)this->get_nextNode(currentNode);  // 일치하지 않으면 다음 노드로 이동
	}
	return nullptr; // 일치하는 노드가 아예 없으면 null 반환
}

bool List::pushBack(void* data)
{
	return this->insertNext(this->get_SingleList_tail(), data);
}

bool List::pushFront(void* data)
{
	return this->insertNext(nullptr, data);
}

void List::destroyList()
{
	void* data = nullptr;

	while (this->getSize() > 0)
	{
		this->removeNext(nullptr,&data);
		this->freeDataFunc(data);
	}

	return;
}