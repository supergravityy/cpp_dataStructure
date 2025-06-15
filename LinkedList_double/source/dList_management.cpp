#include "../header/dList.h"

dList::dList()
{
	this->doubleList_headNode = nullptr;
	this->doubleList_tailNode = nullptr;

	// 부모클래스의 생성자에서 다른 멤버변수를 초기화한다.
}

dList::~dList()
{
	// 부모클래스의 소멸자에서 리스트 해제와 다른 멤버변수를 초기화한다.

	this->doubleList_headNode = nullptr;
	this->doubleList_tailNode = nullptr;
}

// insert_nextNode는 부모클래스에서 이미 구현됨

bool dList::insert_prevNode(void* node, void* data)
{
	return this->insertPrev(node, data);
}

bool dList::remove_tgtNode(void* node, void** saveData)
{
	return this->removeNode(node, saveData);
}

// push_back는 부모클래스에서 이미 구현됨

bool dList::push_front(void* data)
{
	return this->pushFront(data);
}

bool dList::pop_back(void** saveData)
{
	return this->popBack(saveData);
}

bool dList::pop_front(void** saveData)
{
	return this->popFront(saveData);
}

bool dList::insertNext(void* node, void* data)
{
	typDoubleList_Node* newNode = (typDoubleList_Node*)this->makeNode();
	typDoubleList_Node* nodeNext = nullptr; 

	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else if (this->is_emptyNode(node) && this->getSize() > 0) // 리스트가 비어있지 않는 한 node는 null이 될 수 없음
	{
		this->deleteNode((void**)&newNode);
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode,data);									// 1. 막 생성한 노드 초기화

		if (this->getSize() == 0) 										// 2. 비어있는 리스트일 경우
		{
			this->set_DoubleList_head(newNode);							// 3. 노드가 하나이기에 tail과 head가 똑같은 노드를 포인팅
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode,nullptr);						// 4. 노드의 next,prevNode		-> null
			this->set_prevNode(newNode, nullptr);
		}

		else															// 2-1. 비어있지 않은 리스트에 삽입처리
		{
			nodeNext = (typDoubleList_Node*)this->get_nextNode(node);	

			this->set_nextNode(newNode, nodeNext);						// 3. 새 노드의 nextNode		-> 기준 노드의 nextNode 주소
			this->set_prevNode(newNode, node);							// 4. 새 노드의 prevNode 		-> 기준 노드 주소
			this->set_nextNode(node, newNode);							// 5. 기준노드의 nextNode		-> 새 노드 주소

			if (this->is_emptyNode(nodeNext))							// 6. 기준노드의 nextNode가 null일시 => 기준노드가 tail이었음을 암시 
				this->set_DoubleList_tail(newNode);						// tail 포인터 업데이트
			else														// 6-1. 기준노드의 nextNode가 null이 아닐시
				this->set_prevNode(nodeNext, newNode);					// 기준노드의 nextNode의 prevNode -> 새 노드
		}

		this->size++;
		return true;
	}
}

bool dList::insertPrev(void* node, void* data)
{
	typDoubleList_Node* newNode = (typDoubleList_Node*)this->makeNode();
	typDoubleList_Node* nodePrev = nullptr; 

	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else if (this->is_emptyNode(node) && this->getSize() > 0) // 리스트가 비어있지 않는 한 node는 null이 될 수 없음
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode, data);									// 1. 막 생성한 노드 초기화

		if (this->getSize() == 0)										// 2. 비어있는 리스트일 경우
		{
			this->set_DoubleList_head(newNode);							// 3. 노드가 하나이기에 tail과 head가 똑같은 노드를 포인팅
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode, nullptr);						// 4. 노드의 next,prevNode		-> null
			this->set_prevNode(newNode, nullptr);
		}
		else															// 2-1. 비어있지 않은 리스트에 삽입처리
		{
			nodePrev = (typDoubleList_Node*)this->get_prevNode(node);

			this->set_prevNode(newNode, nodePrev);						// 3. 새 노드의 prevNode		-> 기준노드의 prevNode 주소
			this->set_nextNode(newNode, node);							// 4. 새 노드의 nextNode		-> 기준노드
			this->set_prevNode(node, newNode);							// 5. 기준노드의 prevNode		-> 새 노드

			if (this->is_emptyNode(nodePrev))							// 6. 기준노드의 prevNode가 null 일시 => 기준노드가 head였음을 암시
				this->set_DoubleList_head(newNode);						// head 포인터 업데이트
			else														// 6-1. 아닐시
				this->set_nextNode(nodePrev, newNode);					// 기준노드의 prevNode의 nextNode -> 새 노드
		}

		this->size++;
		return true;
	}
}

bool dList::removeNode(void* node, void** saveData)
{
	typDoubleList_Node* nodePrev = nullptr, *nodeNext = nullptr;

	if (node == nullptr || this->getSize() == 0)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		nodePrev = (typDoubleList_Node*)this->get_prevNode(node);
		nodeNext = (typDoubleList_Node*)this->get_nextNode(node);
		*saveData = this->get_Data(node);								// 1. 삭제할 노드의 data 추출 => data의 free는 사용자가 처리

		if (node == (void*)this->get_DoubleList_head())					// 2. 삭제할 노드가 리스트의 head 일 때
		{
			this->set_DoubleList_head(nodeNext);						// 3. head포인터			-> head포인터의 nextNode

			if (this->is_emptyNode(this->get_DoubleList_head()))		// 4. 만약, head포인터의 nextNode 가 null 일시 => 노드 크기가 1임을 암시
				this->set_DoubleList_tail(nullptr);						// tail 도 null로 업데이트
			else														// 4-1. 아닐 시
				this->set_prevNode(nodeNext, nullptr);					// head포인터의 nextNode	-> null
		}
		else															// 2-1. 삭제할 노드가 이외의 노드일시
		{
			this->set_nextNode(nodePrev, nodeNext);						// 3. 삭제할 노드의 prevNode -> nextNode

			if (this->is_emptyNode(nodeNext))							// 4. nextNode가 null일 때 => 삭제할 노드가 tail 이었음을 암시
				this->set_DoubleList_tail(nodePrev);					// tail포인터				-> 삭제할 노드의 prevNode
			else														// 4-1. nextNode가 null이 아닐시
				this->set_prevNode(nodeNext, nodePrev);					// nextNode의 prevNode		-> 삭제할 노드의 prevNode
		}

		this->deleteNode(&node);										// 5. 노드 삭제
		this->size--;

		return true;
	}
}

bool dList::pushBack(void* data) 
{
	return this->insertNext(this->get_DoubleList_tail(), data);
}
bool dList::pushFront(void* data) 
{
	return this->insertPrev(this->get_DoubleList_head(), data);
}

bool dList::popBack(void** saveData)
{
	return this->removeNode(this->get_DoubleList_tail(), saveData);
}

bool dList::popFront(void** saveData) 
{
	return this->removeNode(this->get_DoubleList_head(), saveData);
}