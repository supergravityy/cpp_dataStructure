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

	if (this->getSize() > otherSet->getSize()) // 더 빠른 체크 => 부분집합은 항상 크기가 작거나 같다.
		result = false;
	else
	{
		while (currNode != nullptr)
		{
			if (otherSet->isMember(this->get_Data(currNode)) == false) // set1의 원소가 set2에 있는지 확인
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

	if (this->getSize() != otherSet->getSize()) // 크기가 다르면 같지 않음
		return false;
	else
		return isSubset_1(otherSet);		// 크기가 같으면서 부분집합관계면 두 집합은 같음
}

void Set::deepCopySet(Set* otherSet)
{
	typSingleList_Node* memberNode;
	void* new_memberData;

	// 1. 현재집합 초기화
	this->init(otherSet->cmpFunc, otherSet->printFunc, otherSet->freeDataFunc, otherSet->copyDataFunc);
	this->errCode = otherSet->getErrCode();

	// 2. 인자로 받은 set의 노드 하나하나 대입
	for (memberNode = otherSet->get_SingleList_head(); memberNode != nullptr;
		memberNode = (typSingleList_Node*)otherSet->get_nextNode(memberNode))
	{
		// 3. 기존 노드를 그대로 동적할당해서 this는 원본과 독립적인 data를 가짐
		new_memberData = this->deepCopyData(memberNode);
		if (new_memberData == nullptr)
		{
			this->destroyList();
			return;
		}

		// 4. 새로 동적할당한 data를 삽입
		this->insert(new_memberData);

		if (this->errCode != NORMAL) // 부모메서드에서 오류발생시 새 인스턴스 삭제
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

void* Set::deepCopyData(void* node) // 집합연산시, 결과집합에 새로운 데이터들을 삽입하기위한 과정
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