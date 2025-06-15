#include "../header/dList.h"

dList::dList()
{
	this->doubleList_headNode = nullptr;
	this->doubleList_tailNode = nullptr;

	// �θ�Ŭ������ �����ڿ��� �ٸ� ��������� �ʱ�ȭ�Ѵ�.
}

dList::~dList()
{
	// �θ�Ŭ������ �Ҹ��ڿ��� ����Ʈ ������ �ٸ� ��������� �ʱ�ȭ�Ѵ�.

	this->doubleList_headNode = nullptr;
	this->doubleList_tailNode = nullptr;
}

// insert_nextNode�� �θ�Ŭ�������� �̹� ������

bool dList::insert_prevNode(void* node, void* data)
{
	return this->insertPrev(node, data);
}

bool dList::remove_tgtNode(void* node, void** saveData)
{
	return this->removeNode(node, saveData);
}

// push_back�� �θ�Ŭ�������� �̹� ������

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
	else if (this->is_emptyNode(node) && this->getSize() > 0) // ����Ʈ�� ������� �ʴ� �� node�� null�� �� �� ����
	{
		this->deleteNode((void**)&newNode);
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode,data);									// 1. �� ������ ��� �ʱ�ȭ

		if (this->getSize() == 0) 										// 2. ����ִ� ����Ʈ�� ���
		{
			this->set_DoubleList_head(newNode);							// 3. ��尡 �ϳ��̱⿡ tail�� head�� �Ȱ��� ��带 ������
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode,nullptr);						// 4. ����� next,prevNode		-> null
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