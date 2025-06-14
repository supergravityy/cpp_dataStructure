#include "../header/List.h"

List::List()
{
	this->singleList_head = nullptr;
}

List::~List()
{
	this->destroyList();

	this->size = 0;
	this->cmpFunc = nullptr;
	this->printFunc = nullptr;
	this->freeDataFunc = nullptr;
	this->errCode = NORMAL;
	this->singleList_head = nullptr;
}

bool List::init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
	, void (*printFunc)(const void* data)
	, void (*destroyDataFunc)(void* data))
{
	if (compareFunc == nullptr || printFunc == nullptr || destroyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->destroyList();
		
		this->singleList_head = nullptr;
		this->size = 0;
		this->cmpFunc = compareFunc;
		this->printFunc = printFunc;
		this->freeDataFunc = destroyDataFunc;
		this->errCode = NORMAL;
		return true;
	}
}

bool List::insert_nextNode(void* node, void* data)
{
	return this->insertNext(node, data);
}

bool List::remove_nextNode(void* node, void** saveData)
{
	return this->removeNext(node, saveData);
}

void* List::lookup_Node(void* data)
{
	return this->lookUp(data);
}

bool  List::push_back(void* data)
{
	return this->pushBack(data);
}

bool List::insertNext(void* node, void* data)
{
	typSingleList_Node* prevNode, *newNode = nullptr, *tempNode = nullptr;
	prevNode = (typSingleList_Node*)node;


	if ( data == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		newNode = (typSingleList_Node*)this->makeNode();
		if(newNode == nullptr)
		{
			this->errCode = MEMORY_ERR;
			return false;
		}

		this->initNode(newNode,data);

		if (this->is_emptyNode(prevNode))										// 1. 이전노드가 null 일때		=> (맨앞에 삽입하고 싶다)
		{
			if (this->getSize() == 0)											// 2. 리스트가 비어있을 때		-> head == tail
				this->set_SingleList_tail(newNode);
			else {}																// 2-1. 리스트가 비어있지 않을 때	-> head != tail
			
			this->set_nextNode(newNode, (void*)this->get_SingleList_head());	// 3. newNode의 next				-> head	
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
		this->size++;															// 5. size 증가
		return true;
		
	}
}

bool List::removeNext(void* node, void** saveData)
{
	typSingleList_Node* prevNode, * tempNode, *targetNode;
	prevNode = (typSingleList_Node*)node;

	if (this->getSize() == 0) 
	{
		return false;
	}
	
	else if(prevNode == nullptr)	// 이전노드가 null	=>	head 노드 삭제
	{
		targetNode = this->get_SingleList_head();											// 1. 삭제대상				=> head 노드

		*saveData = this->get_Data(targetNode);												// 2. 삭제할 노드의 data를 data변수에 저장
		this->set_SingleList_head((typSingleList_Node*)this->get_nextNode(targetNode));		// 3. head 포인터 업데이트	=> head 노드의 next

		if(this->getSize() == 1)
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

	this->deleteNode((void**) &targetNode);	// 5. 삭제대상 노드 메모리 해제 (안의 data도 호출함수에서 해제)
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
			currentNode = (typSingleList_Node*)this->get_nextNode(currentNode); // 일치하지 않으면 다음 노드로 이동
	}
	return nullptr; // 일치하는 노드가 아예 없으면 nullptr 반환
}

bool List::pushBack(void* data)
{
	typSingleList_Node* newNode = nullptr, *temp = nullptr;
	if(data == nullptr)
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

		if (this->getSize() == 0) // 리스트가 비어있을 때
		{
			this->set_SingleList_head(newNode);			// head와 tail 모두 newNode로 설정
			this->set_SingleList_tail(newNode);
		}
		else // 리스트에 노드가 있을 때
		{
			temp = this->get_SingleList_tail();			// 현재 tail 노드를 temp에 저장
			this->set_nextNode(temp, newNode);			// 현재 tail의 next -> newNode로 설정
			this->set_SingleList_tail(newNode);			// tail 포인터를 newNode로 업데이트
		}

		this->size++;
	}
}