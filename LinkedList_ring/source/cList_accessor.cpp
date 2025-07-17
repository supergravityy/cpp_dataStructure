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
		return (const void*)tgtNode; // ����Ʈ�� ��尡 �ϳ��� �ִٸ�, ����尡 tail �����
	else
	{
		tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);

		while (tgtNextNode != this->get_CircularList_head())					// 1. tgtNode�� nextNode�� �ڱ��ڽ��� �ƴ� ������ �ݺ�
		{
			tgtNode = tgtNextNode;												// 2. tgtNode�� ���� ���� �̵�
			tgtNextNode = (typCircularList_Node*)this->get_nextNode(tgtNode);	// 3. tgtNextNode�� ���� ���� �̵�
		}

		return (const void*)tgtNode;											// 4. ���� tgtNode�� ����Ʈ�� ������ ����̹Ƿ�, �� ��带 ��ȯ
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