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
	// ������ ��带 ã��, �� ������ �� ��带 ���� 
	return this->insert_nextNode((void*)this->end(), data);
}

bool cList::popFront(void** saveData)
{
	// ������ ����� ���� ��带 ���� => ������ ����� ������� = ���
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

			if (this->get_CircularList_head() == tgtNextNode)		// 5. tgtNode�� nextNode�� ������� head ������Ʈ
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

		this->deleteNode((void**)&oldNode);								// 5. oldNode ����
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