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
// Protected (for Dev)
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
	else if (this->is_emptyNode(node) && this->getSize() > 0) // ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½Ê´ï¿½ ï¿½ï¿½ nodeï¿½ï¿½ nullï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	{
		this->deleteNode((void**)&newNode);
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode, data);									// 1. ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? ï¿½Ê±ï¿½È­

		if (this->getSize() == 0) 										// 2. ï¿½ï¿½ï¿½ï¿½Ö´ï¿? ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿?
		{
			this->set_DoubleList_head(newNode);							// 3. ï¿½ï¿½å°? ï¿½Ï³ï¿½ï¿½Ì±â¿¡ tailï¿½ï¿½ headï¿½ï¿½ ï¿½È°ï¿½ï¿½ï¿½ ï¿½ï¿½å¸? ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode, nullptr);						// 4. ï¿½ï¿½ï¿½ï¿½ï¿? next,prevNode		-> null
			this->set_prevNode(newNode, nullptr);
		}

		else															// 2-1. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ã³ï¿½ï¿½
		{
			nodeNext = (typDoubleList_Node*)this->get_nextNode(node);

			this->set_nextNode(newNode, nodeNext);						// 3. ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? nextNode		-> ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? nextNode ï¿½Ö¼ï¿½
			this->set_prevNode(newNode, node);							// 4. ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? prevNode 		-> ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? ï¿½Ö¼ï¿½
			this->set_nextNode(node, newNode);							// 5. ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? nextNode		-> ï¿½ï¿½ ï¿½ï¿½ï¿? ï¿½Ö¼ï¿½

			if (this->is_emptyNode(nodeNext))							// 6. ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? nextNodeï¿½ï¿½ nullï¿½Ï½ï¿½ => ï¿½ï¿½ï¿½Ø³ï¿½å°? tailï¿½Ì¾ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ï½ï¿½ 
				this->set_DoubleList_tail(newNode);						// tail ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ®
			else														// 6-1. ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? nextNodeï¿½ï¿½ nullï¿½ï¿½ ï¿½Æ´Ò½ï¿½
				this->set_prevNode(nodeNext, newNode);					// ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? nextNodeï¿½ï¿½ prevNode -> ï¿½ï¿½ ï¿½ï¿½ï¿?
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
	else if (this->is_emptyNode(node) && this->getSize() > 0) // ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½Ê´ï¿½ ï¿½ï¿½ nodeï¿½ï¿½ nullï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->initNode(newNode, data);									// 1. ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? ï¿½Ê±ï¿½È­

		if (this->getSize() == 0)										// 2. ï¿½ï¿½ï¿½ï¿½Ö´ï¿? ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿?
		{
			this->set_DoubleList_head(newNode);							// 3. ï¿½ï¿½å°? ï¿½Ï³ï¿½ï¿½Ì±â¿¡ tailï¿½ï¿½ headï¿½ï¿½ ï¿½È°ï¿½ï¿½ï¿½ ï¿½ï¿½å¸? ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			this->set_DoubleList_tail(newNode);
			this->set_nextNode(newNode, nullptr);						// 4. ï¿½ï¿½ï¿½ï¿½ï¿? next,prevNode		-> null
			this->set_prevNode(newNode, nullptr);
		}
		else															// 2-1. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ã³ï¿½ï¿½
		{
			nodePrev = (typDoubleList_Node*)this->get_prevNode(node);

			this->set_prevNode(newNode, nodePrev);						// 3. ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? prevNode		-> ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? prevNode ï¿½Ö¼ï¿½
			this->set_nextNode(newNode, node);							// 4. ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? nextNode		-> ï¿½ï¿½ï¿½Ø³ï¿½ï¿?
			this->set_prevNode(node, newNode);							// 5. ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? prevNode		-> ï¿½ï¿½ ï¿½ï¿½ï¿?

			if (this->is_emptyNode(nodePrev))							// 6. ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? prevNodeï¿½ï¿½ null ï¿½Ï½ï¿½ => ï¿½ï¿½ï¿½Ø³ï¿½å°? headï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ï½ï¿½
				this->set_DoubleList_head(newNode);						// head ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ®
			else														// 6-1. ï¿½Æ´Ò½ï¿½
				this->set_nextNode(nodePrev, newNode);					// ï¿½ï¿½ï¿½Ø³ï¿½ï¿½ï¿½ï¿? prevNodeï¿½ï¿½ nextNode -> ï¿½ï¿½ ï¿½ï¿½ï¿?
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
		*saveData = this->get_Data(node);								// 1. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? data ï¿½ï¿½ï¿½ï¿½ => dataï¿½ï¿½ freeï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ú°ï¿? Ã³ï¿½ï¿½

		if (node == (void*)this->get_DoubleList_head())					// 2. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½å°? ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ head ï¿½ï¿½ ï¿½ï¿½
		{
			this->set_DoubleList_head(nodeNext);						// 3. headï¿½ï¿½ï¿½ï¿½ï¿½ï¿½			-> headï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ nextNode

			if (this->is_emptyNode(this->get_DoubleList_head()))		// 4. ï¿½ï¿½ï¿½ï¿½, headï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ nextNode ï¿½ï¿½ null ï¿½Ï½ï¿½ => ï¿½ï¿½ï¿? Å©ï¿½â°¡ 1ï¿½ï¿½ï¿½ï¿½ ï¿½Ï½ï¿½
				this->set_DoubleList_tail(nullptr);						// tail ï¿½ï¿½ nullï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ®
			else														// 4-1. ï¿½Æ´ï¿½ ï¿½ï¿½
				this->set_prevNode(nodeNext, nullptr);					// headï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ nextNode	-> null
		}
		else															// 2-1. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½å°? ï¿½Ì¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ï½ï¿?
		{
			this->set_nextNode(nodePrev, nodeNext);						// 3. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? prevNode -> nextNode

			if (this->is_emptyNode(nodeNext))							// 4. nextNodeï¿½ï¿½ nullï¿½ï¿½ ï¿½ï¿½ => ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½å°? tail ï¿½Ì¾ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ï½ï¿½
				this->set_DoubleList_tail(nodePrev);					// tailï¿½ï¿½ï¿½ï¿½ï¿½ï¿½				-> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? prevNode
			else														// 4-1. nextNodeï¿½ï¿½ nullï¿½ï¿½ ï¿½Æ´Ò½ï¿½
				this->set_prevNode(nodeNext, nodePrev);					// nextNodeï¿½ï¿½ prevNode		-> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿? prevNode
		}

		this->deleteNode(&node);										// 5. ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½
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