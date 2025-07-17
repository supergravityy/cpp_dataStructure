#include "../header/Set.h"

bool Set::isMember(void* data)
{
	typSingleList_Node* currentNode = this->get_SingleList_head();
	void* nodeItem = nullptr;
	bool result = false;

	if (data == nullptr)
	{
		this->errCode = SYS_FAULT;
		result = false;
	}
	else
	{
		while (! this->is_emptyNode(currentNode))
		{
			nodeItem = this->get_Data(currentNode);

			if (this->cmpFunc(nodeItem, data) == EQUAL)
			{
				result = true;
				break;
			}
			else
				currentNode = (typSingleList_Node*)this->get_nextNode(currentNode);
		}
	}
	return result;
}

bool Set::isSubset_1(Set* otherSet) // set1 ( set2
{
	typSingleList_Node* currNode = this->get_SingleList_head();
	bool result;

	if (this->getSize() > otherSet->getSize()) // �� ���� üũ => �κ������� �׻� ũ�Ⱑ �۰ų� ����.
		result = false;
	else
	{
		while (currNode != nullptr)
		{
			if (otherSet->isMember(this->get_Data(currNode)) == false) // set1�� ���Ұ� set2�� �ִ��� Ȯ��
			{
				result = false;
				goto retPoint;
			}
			else
				currNode = (typSingleList_Node*)this->get_nextNode(currNode);
		}
		result = true;
	}
retPoint:
	return result;
}

bool Set::isSubset_2(Set* otherSet) // set1 ) set2
{
	typSingleList_Node* currNode = otherSet->get_SingleList_head();
	bool result;

	if (this->getSize() < otherSet->getSize())
		result = false;
	else
	{
		while (currNode != nullptr)
		{
			if (this->isMember(otherSet->get_Data(currNode)) == false)
			{
				result = false; 
				goto retPoint;
			}
			else
				currNode = (typSingleList_Node*)otherSet->get_nextNode(currNode);
		}
		result = true;
	}
retPoint:
	return result;
}

bool Set::isEqual(Set* otherSet)
{
	typSingleList_Node* currNode = otherSet->get_SingleList_head();

	if (this->getSize() != otherSet->getSize()) // ũ�Ⱑ �ٸ��� ���� ����
		return false;
	else
		return isSubset_1(otherSet);		// ũ�Ⱑ �����鼭 �κ����հ���� �� ������ ����
}

void Set::deepCopySet(Set* otherSet)
{
	typSingleList_Node* memberNode;
	void* new_memberData;

	// 1. �������� �ʱ�ȭ
	this->init(otherSet->cmpFunc, otherSet->printFunc, otherSet->freeDataFunc, otherSet->copyDataFunc);
	this->errCode = otherSet->getErrCode();

	// 2. ���ڷ� ���� set�� ��� �ϳ��ϳ� ����
	for (memberNode = otherSet->get_SingleList_head(); memberNode != nullptr;
		memberNode = (typSingleList_Node*)otherSet->get_nextNode(memberNode))
	{
		// 3. ���� ��带 �״�� �����Ҵ��ؼ� this�� ������ �������� data�� ����
		new_memberData = this->deepCopyData(memberNode);
		if (new_memberData == nullptr)
		{
			this->destroyList();
			return;
		}

		// 4. ���� �����Ҵ��� data�� ����
		this->insert(new_memberData);

		if (this->errCode != NORMAL) // �θ�޼��忡�� �����߻��� �� �ν��Ͻ� ����
		{
			this->destroyList();
			return;
		}
	}
}

void* Set::makeInst()
{
	Set* newSet = new Set;

	if (newSet == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return nullptr;
	}
	else
		return newSet;
}

void Set::freeInst(Set* tgtInst)
{
	if (tgtInst == nullptr)
		return;

	tgtInst->init(nullptr, nullptr, nullptr,nullptr);
	delete tgtInst;
}

void* Set::deepCopyData(void* node) // ���տ����, ������տ� ���ο� �����͵��� �����ϱ����� ����
{
	typSingleList_Node* tgtNode = (typSingleList_Node*)node;
	void* tgtData = nullptr, *newData = nullptr;
	
	if (this->copyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		tgtData = this->get_Data(tgtNode);
		newData = this->copyDataFunc(tgtData);

		if (newData == nullptr)
			this->errCode = MEMORY_ERR;

		return newData;
	}
}