#include "../header/Set.h"

#define DEBUG

Set* Set::unionOpr(Set* otherSet)
{
	Set* resultSet;
	typSingleList_Node* memberNode;
	void* new_memberData;

	if (this->cmpFunc == nullptr || this->printFunc == nullptr
		|| this->freeDataFunc == nullptr || this->copyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else if (otherSet == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		// 1. 새로운	Set 인스턴스 생성
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. 합집합 초기화 과정
		if(resultSet->init(this->cmpFunc, this->printFunc, this->freeDataFunc, this->copyDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			this->freeInst(resultSet);
			return nullptr;
		}

		// 3. 현재 Set의 모든 원소를 resultSet에 추가
		resultSet->deepCopySet(this);
		if (resultSet->errCode != NORMAL) 
		{
			this->errCode = resultSet->errCode;
			this->freeInst(resultSet);
			return nullptr;
		}

		// 4. 다른 Set의 모든 원소를 resultSet에 추가
		for (memberNode = otherSet->get_SingleList_head(); memberNode != nullptr;
			memberNode = (typSingleList_Node*)otherSet->get_nextNode(memberNode))
		{
			new_memberData = this->deepCopyData(memberNode);
			if (new_memberData == nullptr)
			{
				this->errCode = resultSet->errCode;
				this->freeInst(resultSet);
				return nullptr;
			}

			resultSet->insert(new_memberData);

			if(resultSet->errCode != NORMAL) // 부모메서드에서 오류발생시 새 인스턴스 삭제
			{
				this->errCode = resultSet->errCode;
				this->freeInst(resultSet);
				return nullptr;
			}
		}
		return resultSet;
	}
}

Set* Set::intersectOpr(Set* otherSet)
{
	Set* resultSet;
	typSingleList_Node* memberNode;
	void* new_memberData;

	if (this->cmpFunc == nullptr || this->printFunc == nullptr
		|| this->freeDataFunc == nullptr || this->copyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else if (otherSet == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		// 1. 새로운	Set 인스턴스 생성
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. 교집합 초기화 과정
		if (resultSet->init(this->cmpFunc, this->printFunc, this->freeDataFunc, this->copyDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			this->freeInst(resultSet);
			return nullptr;
		}
		
		// 3. 현재 Set과 인자로 받은 Set의 교집합을 구하여 resultSet에 추가
		for (memberNode = this->get_SingleList_head(); memberNode != nullptr;
			memberNode = (typSingleList_Node*)this->get_nextNode(memberNode))
		{
			new_memberData = this->deepCopyData(memberNode);
			if (new_memberData == nullptr)
			{
				this->errCode = resultSet->errCode;
				this->freeInst(resultSet);
				return nullptr;
			}

			if (otherSet->isMember(new_memberData)) // 현재 Set의 원소가 다른 Set에 존재할 경우, resultSet에 추가
			{
				resultSet->insertNext(resultSet->get_SingleList_tail(), new_memberData); 

				if(resultSet->errCode != NORMAL) // 부모메서드에서 오류발생시 새 인스턴스 삭제
				{
					this->errCode = resultSet->errCode;
					this->freeInst(resultSet);
					return nullptr;
				}
			}
		}
		return resultSet;
	}
}

Set* Set::diffOpr(Set* otherSet)
{
	Set* resultSet;
	typSingleList_Node* memberNode;
	void* new_memberData;

	if (this->cmpFunc == nullptr || this->printFunc == nullptr 
		|| this->freeDataFunc == nullptr || this->copyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else if (otherSet == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		// 1. 새로운	Set 인스턴스 생성
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. 차집합 초기화 과정
		if (resultSet->init(this->cmpFunc, this->printFunc, this->freeDataFunc, this->copyDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			this->freeInst(resultSet);
			return nullptr;
		}

		// 3. 현재 set의 원소에서 인자로 받은 set의 원소가 아닌 것만 대입
		for (memberNode = this->get_SingleList_head(); memberNode != nullptr;
			memberNode = (typSingleList_Node*)this->get_nextNode(memberNode))
		{
			new_memberData = this->deepCopyData(memberNode);
			if (new_memberData == nullptr)
			{
				this->errCode = resultSet->errCode;
				this->freeInst(resultSet);
				return nullptr;
			}

			if (!otherSet->isMember(new_memberData))
			{
				resultSet->insertNext(resultSet->get_SingleList_tail(), new_memberData);

				if (resultSet->errCode != NORMAL) // 부모메서드에서 오류발생시 새 인스턴스 삭제
				{
					this->errCode = resultSet->errCode;
					this->freeInst(resultSet);
					return nullptr;
				}
			}
		}
		return resultSet;
	}
}

Set* Set::symmDiffOpr(Set* otherSet)
{
	Set* resultSet;
	typSingleList_Node* memberNode;
	void* new_memberData;

	if (this->cmpFunc == nullptr || this->printFunc == nullptr
		|| this->freeDataFunc == nullptr || this->copyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else if (otherSet == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		// 1. 새로운	Set 인스턴스 생성
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. 대칭 차집합 초기화 과정
		if (resultSet->init(this->cmpFunc, this->printFunc, this->freeDataFunc, this->copyDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			this->freeInst(resultSet);
			return nullptr;
		}

		// 3. this - other
		for (memberNode = this->get_SingleList_head(); memberNode != nullptr;
			memberNode = (typSingleList_Node*)this->get_nextNode(memberNode))
		{
			new_memberData = this->deepCopyData(memberNode);
			if (new_memberData == nullptr)
			{
				this->errCode = resultSet->errCode;
				this->freeInst(resultSet);
				return nullptr;
			}

			if (!otherSet->isMember(new_memberData))
			{
				resultSet->insertNext(resultSet->get_SingleList_tail(), new_memberData);

				if (resultSet->errCode != NORMAL)
				{
					this->errCode = resultSet->errCode;
					this->freeInst(resultSet);
					return nullptr;
				}
			}
		}

		// 4. other - this
		for (memberNode = otherSet->get_SingleList_head(); memberNode != nullptr;
			memberNode = (typSingleList_Node*)otherSet->get_nextNode(memberNode))
		{
			new_memberData = this->deepCopyData(memberNode);
			if (new_memberData == nullptr)
			{
				this->errCode = resultSet->errCode;
				this->freeInst(resultSet);
				return nullptr;
			}

			if (!this->isMember(new_memberData))
			{
				resultSet->insertNext(resultSet->get_SingleList_tail(), new_memberData);

				if (resultSet->errCode != NORMAL)
				{
					this->errCode = resultSet->errCode;
					this->freeInst(resultSet);
					return nullptr;
				}
			}
		}
		return resultSet;
	}
}