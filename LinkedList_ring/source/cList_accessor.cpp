#include "../header/cList.h"

/*------------------------------------------*/
// Iterator (for User)
/*------------------------------------------*/

const void* cList::begin()
{
	return (const void*)this->get_CircularList_head();
}

const void* cList::end()
{
	typCircularList_Node* tgtNode = this->get_CircularList_head();
	typCircularList_Node* tgtNextNode = nullptr;

	if (this->getSize() == 0)
		return nullptr;
	else if (this->getSize() == 1)
		return (const void*)tgtNode; // 리스트에 노드가 하나만 있다면, 헤드노드가 tail 노드임
	else
	{
		tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);

		while (tgtNextNode != this->get_CircularList_head())					// 1. tgtNode의 nextNode가 자기자신이 아닐 때까지 반복
		{
			tgtNode = tgtNextNode;												// 2. tgtNode를 다음 노드로 이동
			tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);	// 3. tgtNextNode를 다음 노드로 이동
		}

		return (const void*)tgtNode;											// 4. 이제 tgtNode는 리스트의 마지막 노드이므로, 그 노드를 반환
	}
}

/*------------------------------------------*/
// Accessor (for Dev)
/*------------------------------------------*/

typCircularList_Node* cList::get_CircularList_head()
{
	return this->circularList_head;
}

void cList::set_CircularList_head(typCircularList_Node* head)
{
	this->circularList_head = head;
}

void cList::set_nextNode(void* tgtNode, void* tgtAddr)
{
	typCircularList_Node* node = (typCircularList_Node*)tgtNode;
	node->nextNode = (typCircularList_Node*)tgtAddr;
}

void* cList::get_nextNode(void* tgtNode)
{
	typCircularList_Node* node = (typCircularList_Node*)tgtNode;
	return (void*)node->nextNode;
}

void* cList::get_Data(void* node)
{
	typCircularList_Node* temp = (typCircularList_Node*)node;

	return temp->data;
}

void  cList::set_Data(void* node, void* data)
{
	typCircularList_Node* temp = (typCircularList_Node*)node;

	temp->data = data;
	return;
}