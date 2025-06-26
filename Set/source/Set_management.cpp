#include "../header/Set.h"

Set::Set()
{
	this->copyDataFunc = nullptr;
}

Set::~Set()
{
	this->copyDataFunc = nullptr;
}

bool Set::insert(void* data)
{
	if (this->isMember(data))
		return false; // 이미 존재하는 데이터는 삽입하지 않음
	else
		return this->insertNext(this->get_SingleList_tail(), data);
}

bool Set::remove(void* data, void** saveData)
{
	typSingleList_Node* currNode = this->get_SingleList_head(),
		*prevNode = nullptr;

	bool result = false;

	while (!this->is_emptyNode(currNode)) // 삭제할 원소 찾기
	{
		if (this->cmpFunc(data, this->get_Data(currNode)))
			break;
		else
		{
			prevNode = currNode;
			currNode = (typSingleList_Node*)this->get_nextNode(currNode);
		}
	}

	if (this->is_emptyNode(currNode)) // 삭제할 원소가 없는 경우
		result = false;
	else
		result = this->removeNext(prevNode, saveData);
	
	return result;
}

// 연산자 오버로딩 여기에 구현
Set* Set::operator|(Set& other) 
{
	return this->unionOpr(&other);
}

Set* Set::operator&(Set& other) 
{
	return this->intersectOpr(&other);
}

Set* Set::operator-(Set& other) 
{
	return this->diffOpr(&other);
}

Set* Set::operator^(Set& other) 
{
	return this->symmDiffOpr(&other);
}

bool Set::operator==(Set& other) 
{
	return this->isEqual(&other);
}

bool Set::operator<(Set& other) 
{
	return this->isSubset_1(&other);
}

bool Set::operator>(Set& other) 
{
	return this->isSubset_2( &other);
}

bool Set::init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
	, void (*printFunc)(const void* data)
	, void (*destroyDataFunc)(void* data)
	, void* (*copyDataFunc)(void* data))
{
	if (compareFunc == nullptr || printFunc == nullptr || destroyDataFunc == nullptr || copyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->destroyList();

		this->set_SingleList_head(nullptr);
		this->size = 0;
		this->cmpFunc = compareFunc;
		this->printFunc = printFunc;
		this->freeDataFunc = destroyDataFunc;
		this->copyDataFunc = copyDataFunc;
		this->errCode = NORMAL;
		return true;
	}
}

// 복사 대입
void Set::operator=(Set& otherSet)
{
	 this->deepCopySet(&otherSet);
}