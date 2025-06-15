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

// todo : 물론 단일연결리스트의 pushBack도