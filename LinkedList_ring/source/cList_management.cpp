#include "../header/cList.h"

cList::cList()
{
	this->circularList_head = nullptr;
}

cList::~cList()
{
	this->destroyList(); // �޸� ���� ���� -> �θ�Ŭ������ destroy�� �ƹ��͵� ��� ������
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
	// �� �޼���� List Ŭ���������� ���ǵ��� ���ѵ�
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
		this->initNode(newNode, data);								// 1. ��� �ʱ�ȭ

		if (this->getSize() == 0)									// 2. ����Ʈ�� ����ִٸ�
		{
			this->set_nextNode(newNode, newNode);					// 3. ������� nextNode			-> �ڱ��ڽ�
			this->set_CircularList_head(newNode);					// 4. ����� ����
		}
		else														// 2-1. ����Ʈ�� ������� �ʴٸ�
		{
			tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);

			this->set_nextNode(newNode, tgtNextNode);				// 3. ������� nextNode			-> tgtNode�� nextNode
			this->set_nextNode(tgtNode, newNode);					// 4. tgtNode�� nextNode			-> �����

			// ������忡�� tail �����Ͱ� ����.
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
		*saveData = this->get_Data((void*)tgtNextNode);						// 1. ������ ����� �����͸� ����

		if (tgtNextNode == tgtNode)											// 2. ��������� nextNode�� �ڱ��ڽ� => ����Ʈ�� ��尡 �ϳ�����
		{
			oldNode = tgtNode;												// 3. oldNode�� ������ ��� ����
			this->set_CircularList_head(nullptr);							// 4. ����� ����
		}
		else																// 2-1. ����Ʈ�� ��尡 ������ ����												
		{
			oldNode = tgtNextNode;											// 3. oldNode�� ������ ��� ����
			this->set_nextNode(tgtNode, this->get_nextNode(oldNode));		// 4. ��������� nextNode		-> ��¥ ������ ����� nextNode

			if (oldNode == this->get_CircularList_head())					// ����尡 �����Ǵ� ���, ����带 ���� ���� ����
				this->set_CircularList_head((typCircularList_Node*)this->get_nextNode(oldNode));
		}

		this->deleteNode((void**) &oldNode);								// 5. oldNode ����
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
		return (void*)tgtNode; // ����Ʈ�� ��尡 �ϳ��� �ִٸ�, ����尡 tail �����
	else
	{
		tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);

		while (tgtNextNode != this->get_CircularList_head())					// 1. tgtNode�� nextNode�� �ڱ��ڽ��� �ƴ� ������ �ݺ�
		{
			tgtNode = tgtNextNode;												// 2. tgtNode�� ���� ���� �̵�
			tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);	// 3. tgtNextNode�� ���� ���� �̵�
		}

		return (void*)tgtNode;													// 4. ���� tgtNode�� ����Ʈ�� ������ ����̹Ƿ�, �� ��带 ��ȯ
	}
}

bool cList::pushFront(void* data)
{
	// ������ ��带 ã��, �� ������ �� ��带 ���� 
	return this->insert_nextNode(this->findTail(), data);	
}

bool cList::popFront(void** saveData)
{
	// ������ ����� ���� ��带 ���� => ������ ����� ������� = ���
	return this->removeNext(this->findTail(), saveData);
}