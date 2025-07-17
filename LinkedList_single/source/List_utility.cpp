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
// Protected (for Dev)
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

		if (this->is_emptyNode(prevNode))										// 1. ������尡 null �϶�
		{
			if (this->getSize() == 0)											// 2. ����Ʈ�� ������� ��		-> head == tail
				this->set_SingleList_tail(newNode);
			else {}																// 2-1. ����Ʈ�� ������� ���� ��	-> head != tail

			this->set_nextNode(newNode, (void*)this->get_SingleList_head());	// 3. newNode�� next			-> head	
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

	else if (prevNode == nullptr)	// ������尡 null	=>	head ��� ����
	{
		targetNode = this->get_SingleList_head();											// 1. �������				=> head ���

		*saveData = this->get_Data(targetNode);												// 2. ������ ����� data�� data������ ����
		this->set_SingleList_head((typSingleList_Node*)this->get_nextNode(targetNode));		// 3. head ������ ������Ʈ	=> head ����� next

		if (this->getSize() == 1)
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

	this->deleteNode((void**)&targetNode);	// 5. ������� ��� �޸� ���� (���� data�� �޼��尡 ����ǰ� ����ڰ� ���� �Ǵ�)
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
			currentNode = (typSingleList_Node*)this->get_nextNode(currentNode);  // ��ġ���� ������ ���� ���� �̵�
	}
	return nullptr; // ��ġ�ϴ� ��尡 �ƿ� ������ null ��ȯ
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