#include "../header/List.h"

List::List()
{
	this->singleList_head = nullptr;
}

List::~List()
{
	// 주의 : 소멸자 호출 순서에서, 자식소멸자가 호출된 후, 부모소멸자가 호출되면, 오버라이딩 되기전의 메서드가 호출됨
	// 자식 메서드의의 removeNext와 부모 메서드의의 removeNext는 엄연히 틀리다. 그러나, 자식메서드에서 이미 size =0 을 보장하기에 바로 ret되기에 안전함.
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

		if (this->is_emptyNode(prevNode))										// 1. ������尡 null �϶�		=> (�Ǿտ� �����ϰ� �ʹ�)
		{
			if (this->getSize() == 0)											// 2. ����Ʈ�� ������� ��		-> head == tail
				this->set_SingleList_tail(newNode);
			else {}																// 2-1. ����Ʈ�� ������� ���� ��	-> head != tail
			
			this->set_nextNode(newNode, (void*)this->get_SingleList_head());	// 3. newNode�� next				-> head	
			this->set_SingleList_head(newNode);									// 4. head ������ ������Ʈ
		}
		
		else																	// 1-1. ������尡 null�� �ƴ� ��	=> (�߰��� �����ϰ� �ʹ�)
		{
			tempNode = (typSingleList_Node*)this->get_nextNode(prevNode);		// 2. prevNode�� next�� tempNode�� �ӽ�����
			this->set_nextNode(prevNode, newNode);								// 3. prevNode�� �� ���� ��� ���̿� newNode ����
			this->set_nextNode(newNode, tempNode);								
			
			if (tempNode == nullptr)											// 4. tempNode�� null�̸� tail ������Ʈ
				this->set_SingleList_tail(newNode);
			else {}
		}
		this->size++;															// 5. size ����
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
	
	else if(prevNode == nullptr)	// ������尡 null	=>	head ��� ����
	{
		targetNode = this->get_SingleList_head();											// 1. �������				=> head ���

		*saveData = this->get_Data(targetNode);												// 2. ������ ����� data�� data������ ����
		this->set_SingleList_head((typSingleList_Node*)this->get_nextNode(targetNode));		// 3. head ������ ������Ʈ	=> head ����� next

		if(this->getSize() == 1)
			this->set_SingleList_tail(nullptr);												// 4. ���� �� ����Ʈ�� ��������� tail�� null�� ����
		else {}
	}
	else							// ������尡 null�� �ƴ� ��	=> �߰� ��� ����
	{
		if (this->get_nextNode(prevNode) == nullptr) // ������尡 tail ����� ��, ������尡 �����Ƿ� ���� �Ұ���
		{
			this->errCode = SYS_FAULT;
			return false;
		}
		else
		{
			targetNode = (typSingleList_Node*)this->get_nextNode(prevNode);					// 1. �������				=> prevNode�� next ���

			*saveData = this->get_Data(targetNode);											// 2. ������ ����� data�� data������ ����
			this->set_nextNode(prevNode, this->get_nextNode(targetNode));					// 3. prevNode�� next		-> targetNode�� next�� ������Ʈ (=> prev����� ������常 ������)

			if (this->get_nextNode(targetNode) == nullptr)									// 4. targetNode�� next�� null�̸� tail ������Ʈ
				this->set_SingleList_tail(prevNode);
			else {}
		}
	}

	this->deleteNode((void**) &targetNode);	// 5. ������� ��� �޸� ���� (���� data�� ȣ���Լ����� ����)
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

	while (currentNode != nullptr)										// head���� �����Ͽ� ����Ʈ�� ������ ��ȸ
	{
		if (this->cmpFunc(this->get_Data(currentNode), data) == EQUAL)	// �����Ͱ� ��ġ�ϴ��� ��
			return (void*)currentNode;									// ��ġ�ϴ� ����ּ� ��ȯ
		else
			currentNode = (typSingleList_Node*)this->get_nextNode(currentNode); // ��ġ���� ������ ���� ���� �̵�
	}
	return nullptr; // ��ġ�ϴ� ��尡 �ƿ� ������ nullptr ��ȯ
}

bool List::pushBack(void* data)
{
	return this->insertNext(this->get_SingleList_tail(), data);
}

bool List::pushFront(void* data)
{
	return this->insertNext(nullptr, data);
}