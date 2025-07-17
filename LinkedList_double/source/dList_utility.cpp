#include "../header/dList.h"

/*------------------------------------------*/
// Public (for User)
/*------------------------------------------*/

void dList::printAll()
{
	if (this->printFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}

	typDoubleList_Node* currNode = this->doubleList_headNode;
	while (currNode != nullptr)
	{
		this->printFunc(currNode->data);
		currNode = (typDoubleList_Node*)this->get_nextNode(currNode);
	}
}

/*------------------------------------------*/
// Public (for Dev)
/*------------------------------------------*/

void* dList::makeNode()
{
	typDoubleList_Node* newNode = new typDoubleList_Node;

	return newNode;
}
void dList::initNode(void* node, void* data)
{
	typDoubleList_Node* temp = (typDoubleList_Node *) node;
	temp->data = data;
	temp->nextNode = nullptr;
	temp->prevNode = nullptr;
}
void dList::deleteNode(void** node)
{
	typDoubleList_Node** delNode = (typDoubleList_Node**)node;

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

void* dList::lookUp(void* data)
{
	if (this->cmpFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}

	typDoubleList_Node* currNode = this->get_DoubleList_head();

	while (currNode != nullptr)
	{
		if (this->cmpFunc(this->get_Data(currNode), data) == EQUAL)
			return (void*)currNode;
		else
			currNode = (typDoubleList_Node*)this->get_nextNode(currNode);
	}

	return nullptr;
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
	else if (this->is_emptyNode(node) && this->getSize() > 0) // ����Ʈ�� ������� �ʴ� �� node�� null�� �� �� ����
	{
		this->deleteNode((void**)&newNode);
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode, data);									// 1. �� ������ ��� �ʱ�ȭ

		if (this->getSize() == 0) 										// 2. ����ִ� ����Ʈ�� ���
		{
			this->set_DoubleList_head(newNode);							// 3. ��尡 �ϳ��̱⿡ tail�� head�� �Ȱ��� ��带 ������
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode, nullptr);						// 4. ����� next,prevNode		-> null
			this->set_prevNode(newNode, nullptr);
		}

		else															// 2-1. ������� ���� ����Ʈ�� ����ó��
		{
			nodeNext = (typDoubleList_Node*)this->get_nextNode(node);

			this->set_nextNode(newNode, nodeNext);						// 3. �� ����� nextNode		-> ���� ����� nextNode �ּ�
			this->set_prevNode(newNode, node);							// 4. �� ����� prevNode 		-> ���� ��� �ּ�
			this->set_nextNode(node, newNode);							// 5. ���س���� nextNode		-> �� ��� �ּ�

			if (this->is_emptyNode(nodeNext))							// 6. ���س���� nextNode�� null�Ͻ� => ���س�尡 tail�̾����� �Ͻ� 
				this->set_DoubleList_tail(newNode);						// tail ������ ������Ʈ
			else														// 6-1. ���س���� nextNode�� null�� �ƴҽ�
				this->set_prevNode(nodeNext, newNode);					// ���س���� nextNode�� prevNode -> �� ���
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
	else if (this->is_emptyNode(node) && this->getSize() > 0) // ����Ʈ�� ������� �ʴ� �� node�� null�� �� �� ����
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode, data);									// 1. �� ������ ��� �ʱ�ȭ

		if (this->getSize() == 0)										// 2. ����ִ� ����Ʈ�� ���
		{
			this->set_DoubleList_head(newNode);							// 3. ��尡 �ϳ��̱⿡ tail�� head�� �Ȱ��� ��带 ������
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode, nullptr);						// 4. ����� next,prevNode		-> null
			this->set_prevNode(newNode, nullptr);
		}
		else															// 2-1. ������� ���� ����Ʈ�� ����ó��
		{
			nodePrev = (typDoubleList_Node*)this->get_prevNode(node);

			this->set_prevNode(newNode, nodePrev);						// 3. �� ����� prevNode		-> ���س���� prevNode �ּ�
			this->set_nextNode(newNode, node);							// 4. �� ����� nextNode		-> ���س��
			this->set_prevNode(node, newNode);							// 5. ���س���� prevNode		-> �� ���

			if (this->is_emptyNode(nodePrev))							// 6. ���س���� prevNode�� null �Ͻ� => ���س�尡 head������ �Ͻ�
				this->set_DoubleList_head(newNode);						// head ������ ������Ʈ
			else														// 6-1. �ƴҽ�
				this->set_nextNode(nodePrev, newNode);					// ���س���� prevNode�� nextNode -> �� ���
		}

		this->size++;
		return true;
	}
}
bool dList::removeNode(void* node, void** saveData)
{
	typDoubleList_Node* nodePrev = nullptr, * nodeNext = nullptr;

	if (node == nullptr || this->getSize() == 0)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		nodePrev = (typDoubleList_Node*)this->get_prevNode(node);
		nodeNext = (typDoubleList_Node*)this->get_nextNode(node);
		*saveData = this->get_Data(node);								// 1. ������ ����� data ���� => data�� free�� ����ڰ� ó��

		if (node == (void*)this->get_DoubleList_head())					// 2. ������ ��尡 ����Ʈ�� head �� ��
		{
			this->set_DoubleList_head(nodeNext);						// 3. head������			-> head�������� nextNode

			if (this->is_emptyNode(this->get_DoubleList_head()))		// 4. ����, head�������� nextNode �� null �Ͻ� => ��� ũ�Ⱑ 1���� �Ͻ�
				this->set_DoubleList_tail(nullptr);						// tail �� null�� ������Ʈ
			else														// 4-1. �ƴ� ��
				this->set_prevNode(nodeNext, nullptr);					// head�������� nextNode	-> null
		}
		else															// 2-1. ������ ��尡 �̿��� ����Ͻ�
		{
			this->set_nextNode(nodePrev, nodeNext);						// 3. ������ ����� prevNode -> nextNode

			if (this->is_emptyNode(nodeNext))							// 4. nextNode�� null�� �� => ������ ��尡 tail �̾����� �Ͻ�
				this->set_DoubleList_tail(nodePrev);					// tail������				-> ������ ����� prevNode
			else														// 4-1. nextNode�� null�� �ƴҽ�
				this->set_prevNode(nodeNext, nodePrev);					// nextNode�� prevNode		-> ������ ����� prevNode
		}

		this->deleteNode(&node);										// 5. ��� ����
		this->size--;

		return true;
	}
}

void dList::destroyList()
{
	void* data = nullptr;

	while (this->getSize() > 0)
	{
		this->remove_tgtNode(this->get_DoubleList_head(), &data);
		this->freeDataFunc(data);
	}

	return;
}