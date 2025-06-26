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
		// 1. ���ο�	Set �ν��Ͻ� ����
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. ������ �ʱ�ȭ ����
		if(resultSet->init(this->cmpFunc, this->printFunc, this->freeDataFunc, this->copyDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			this->freeInst(resultSet);
			return nullptr;
		}

		// 3. ���� Set�� ��� ���Ҹ� resultSet�� �߰�
		resultSet->deepCopySet(this);
		if (resultSet->errCode != NORMAL) 
		{
			this->errCode = resultSet->errCode;
			this->freeInst(resultSet);
			return nullptr;
		}

		// 4. �ٸ� Set�� ��� ���Ҹ� resultSet�� �߰�
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

			if(resultSet->errCode != NORMAL) // �θ�޼��忡�� �����߻��� �� �ν��Ͻ� ����
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
		// 1. ���ο�	Set �ν��Ͻ� ����
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. ������ �ʱ�ȭ ����
		if (resultSet->init(this->cmpFunc, this->printFunc, this->freeDataFunc, this->copyDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			this->freeInst(resultSet);
			return nullptr;
		}
		
		// 3. ���� Set�� ���ڷ� ���� Set�� �������� ���Ͽ� resultSet�� �߰�
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

			if (otherSet->isMember(new_memberData)) // ���� Set�� ���Ұ� �ٸ� Set�� ������ ���, resultSet�� �߰�
			{
				resultSet->insertNext(resultSet->get_SingleList_tail(), new_memberData); 

				if(resultSet->errCode != NORMAL) // �θ�޼��忡�� �����߻��� �� �ν��Ͻ� ����
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
		// 1. ���ο�	Set �ν��Ͻ� ����
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. ������ �ʱ�ȭ ����
		if (resultSet->init(this->cmpFunc, this->printFunc, this->freeDataFunc, this->copyDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			this->freeInst(resultSet);
			return nullptr;
		}

		// 3. ���� set�� ���ҿ��� ���ڷ� ���� set�� ���Ұ� �ƴ� �͸� ����
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

				if (resultSet->errCode != NORMAL) // �θ�޼��忡�� �����߻��� �� �ν��Ͻ� ����
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
		// 1. ���ο�	Set �ν��Ͻ� ����
		resultSet = (Set*)this->makeInst();
		if (resultSet == nullptr)	return nullptr;

		// 2. ��Ī ������ �ʱ�ȭ ����
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