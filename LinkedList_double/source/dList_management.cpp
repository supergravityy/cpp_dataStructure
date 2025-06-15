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
	else if (this->is_emptyNode(node) && this->getSize() > 0)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode,data);

		if (this->getSize() == 0)
		{
			this->set_DoubleList_head(newNode);
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode,nullptr);
			this->set_prevNode(newNode, nullptr);
		}

		else
		{
			nodeNext = (typDoubleList_Node*)this->get_nextNode(node);

			this->set_nextNode(newNode, nodeNext);
			this->set_prevNode(newNode, node);
			this->set_nextNode(node, newNode);

			if (this->is_emptyNode(nodeNext))
				this->set_DoubleList_tail(newNode);
			else
				this->set_prevNode(nodeNext, newNode);
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
	else if (this->is_emptyNode(node) && this->getSize() > 0)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode, data);

		if (this->getSize() == 0)
		{
			this->set_DoubleList_head(newNode);
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode, nullptr);
			this->set_prevNode(newNode, nullptr);
		}
		else
		{
			nodePrev = (typDoubleList_Node*)this->get_prevNode(node);

			this->set_prevNode(newNode, nodePrev);
			this->set_nextNode(newNode, node);
			this->set_prevNode(node, newNode);

			if (this->is_emptyNode(nodePrev))
				this->set_DoubleList_head(newNode);
			else
				this->set_nextNode(nodePrev, newNode);
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
		*saveData = this->get_Data(node);

		if (node == (void*)this->get_DoubleList_head())
		{
			this->set_DoubleList_head(nodeNext);

			if (this->is_emptyNode(this->get_DoubleList_head()))
				this->set_DoubleList_tail(nullptr);
			else
				this->set_prevNode(nodeNext, nullptr);
		}
		else
		{
			this->set_nextNode(nodePrev, nodeNext);

			if (this->is_emptyNode(nodeNext))
				this->set_DoubleList_tail(nodePrev);
			else
				this->set_prevNode(nodeNext, nodePrev);
		}

		this->deleteNode(&node);
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

// todo : ���� ���Ͽ��Ḯ��Ʈ�� pushBack��