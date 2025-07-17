#include "../header/HashTable.h"

HashTable::HashTable()
{
	this->bucketCnt = 0;
	this->size = 0;
	this->errCode = NORMAL;
	this->table = nullptr;

	this->cmpFunc = nullptr;
	this->freeDataFunc = nullptr;
	this->getKeyVal = nullptr;
	this->hashFunc = nullptr;
	this->printFunc = nullptr;
}

HashTable::~HashTable()
{
	this->destroyBuckets();

	this->bucketCnt = 0;
	this->size = 0;
	this->errCode = NORMAL;
	this->table = nullptr;

	this->cmpFunc = nullptr;
	this->freeDataFunc = nullptr;
	this->getKeyVal = nullptr;
	this->hashFunc = nullptr;
	this->printFunc = nullptr;
}

bool HashTable::init(typCmpResult(*cmpFunc)(const void* key1, const void* key2),
	void (*printFunc)(const void* data),
	void (*freeDataFunc)(void* data),
	void* (*getKeyVal) (void* data), int bucketNum,
	int (*hashFunc) (const void* key, int bucketCnt))
{
	if (printFunc == nullptr || freeDataFunc == nullptr || cmpFunc == nullptr || getKeyVal == nullptr )
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else if (bucketNum == 0)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->destroyBuckets();							// 1. ������ �ִ� ��Ŷ�� ��� ����

		this->bucketCnt = bucketNum;					// 2. ��Ŷ����� �°� ���̺� ũ�� ����
		this->table = new List[this->bucketCnt];
		if (this->table == nullptr)
		{
			this->errCode = MEMORY_ERR;
			this->bucketCnt = 0;
			return false;
		}
		else
			this->size = 0;

		this->cmpFunc = cmpFunc;						// 3. ����� �����Լ� ����
		this->printFunc = printFunc;
		this->freeDataFunc = freeDataFunc;
		this->hashFunc = hashFunc;
		this->getKeyVal = getKeyVal;

		if (this->initBuckets() == false)				// 4. bucket �ʱ�ȭ����
		{
			this->errCode = SYS_FAULT;
			this->destroyBuckets();
			this->bucketCnt = 0;
			return false;
		}
		else
			return true;
		
	}
}

bool HashTable::insert(void* data)
{
	void* temp;
	int hashedIdx;
	bool result;
	List* tempList = nullptr;

	if (data == nullptr)
	{
		this->errCode = SYS_FAULT;
		result = false;
	}
	else
	{
		temp = data;

		if (this->lookup(&temp) == true)									// 1. �ߺ��� �ƴ� ���������� �˻��� ��. 
			result = false;
		else
		{
			hashedIdx = this->hashFunc(this->getKeyVal(temp),
				this->bucketCnt);											// 2. �ؽ��� ���
			tempList = &(this->table[hashedIdx]);							// 3. ������ ��Ŷ �ּ� ����

			result = tempList->insert_nextNode(nullptr, data);				// 4. ������ ��Ŷ�� push
			this->size++;
		}
	}

	return result;
}

bool HashTable::remove(void** saveData)
{
	typSingleList_Node* iterNode, *prevNode;
	List* tempList;
	int hashedIdx;
	bool result = false;

	if (*saveData == nullptr)
	{
		this->errCode = SYS_FAULT;
		result = false;
	}
	else
	{
		hashedIdx = this->hashFunc(this->getKeyVal(*saveData),
			this->bucketCnt);													// 1. ã�� �����ͷ� �ؽ��� ���

		tempList = &(this->table[hashedIdx]);									// 2. �ش� ��Ŷ�� �ּ� ����

		prevNode = nullptr;														// 3. �ش� ��Ŷ���� ã�� data�� head���� ���
		for (iterNode = (typSingleList_Node*)tempList->begin();
			iterNode != nullptr; 
			iterNode = (typSingleList_Node*)tempList->next(iterNode))	// 4. �ش� ��Ŷ(����Ʈ)���� ��ȸ�ϸ� ã�� ��� Ž��
		{
			if (this->cmpFunc(*saveData, tempList->data(iterNode)) == EQUAL)
			{
				if (tempList->remove_nextNode(prevNode, saveData))				// 5. Ž���ߴٸ� ��� ����
				{
					this->size--;
					result = true;
				}
				else
				{
					this->errCode = tempList->getErrCode();
					result = false;
				}
				break;
			}
			else																// 5-1. �ƴ϶�� prevNode ������Ʈ
				prevNode = iterNode;						
		}
	}

	return result;	// Ž������ ? true : false
}

bool HashTable::lookup(void** saveData)
{
	typSingleList_Node* iterNode;
	List* tempList;
	int hashedIdx;
	bool result = false;

	if (*saveData == nullptr)
	{
		this->errCode = SYS_FAULT;
		result = false;
	}
	else
	{
		hashedIdx = this->hashFunc(this->getKeyVal(*saveData),this->bucketCnt);		// 1. �ؽ��� ���

		tempList = &this->table[hashedIdx];											// 2. ������ ��Ŷ �ּ� ����

		for (iterNode = (typSingleList_Node*)tempList->begin();						// 3. data ������ ���� ��� Ž��
			iterNode != nullptr;
			iterNode = (typSingleList_Node*)tempList->next(iterNode))
		{
			if (this->cmpFunc(*saveData, tempList->data(iterNode)) == EQUAL)
			{
				*saveData = (void*)tempList->data(iterNode);
				result = true;
				break;
			}
		}

		return result;
	}
	return result;
}