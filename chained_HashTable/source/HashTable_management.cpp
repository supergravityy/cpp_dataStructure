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
		this->destroyBuckets();							// 1. 기존에 있던 버킷들 모두 삭제

		this->bucketCnt = bucketNum;					// 2. 버킷사이즈에 맞게 테이블 크기 조정
		this->table = new List[this->bucketCnt];
		if (this->table == nullptr)
		{
			this->errCode = MEMORY_ERR;
			this->bucketCnt = 0;
			return false;
		}
		else
			this->size = 0;

		this->cmpFunc = cmpFunc;						// 3. 사용자 지정함수 세팅
		this->printFunc = printFunc;
		this->freeDataFunc = freeDataFunc;
		this->hashFunc = hashFunc;
		this->getKeyVal = getKeyVal;

		if (this->initBuckets() == false)				// 4. bucket 초기화과정
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

		if (this->lookup(&temp) == true)									// 1. 중복이 아닌 데이터인지 검색할 것. 
			result = false;
		else
		{
			hashedIdx = this->hashFunc(this->getKeyVal(temp),
				this->bucketCnt);											// 2. 해쉬값 계산
			tempList = &(this->table[hashedIdx]);							// 3. 지정된 버킷 주소 대입

			result = tempList->insert_nextNode(nullptr, data);				// 4. 지정된 버킷에 push
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
			this->bucketCnt);													// 1. 찾을 데이터로 해쉬값 계산

		tempList = &(this->table[hashedIdx]);									// 2. 해당 버킷의 주소 대입

		prevNode = nullptr;														// 3. 해당 버킷에서 찾는 data가 head임을 고려
		for (iterNode = (typSingleList_Node*)tempList->begin();
			iterNode != nullptr; 
			iterNode = (typSingleList_Node*)tempList->next(iterNode))	// 4. 해당 버킷(리스트)에서 순회하며 찾을 노드 탐색
		{
			if (this->cmpFunc(*saveData, tempList->data(iterNode)) == EQUAL)
			{
				if (tempList->remove_nextNode(prevNode, saveData))				// 5. 탐색했다면 노드 삭제
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
			else																// 5-1. 아니라면 prevNode 업데이트
				prevNode = iterNode;						
		}
	}

	return result;	// 탐색여부 ? true : false
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
		hashedIdx = this->hashFunc(this->getKeyVal(*saveData),this->bucketCnt);		// 1. 해쉬값 계산

		tempList = &this->table[hashedIdx];											// 2. 지정된 버킷 주소 대입

		for (iterNode = (typSingleList_Node*)tempList->begin();						// 3. data 내용을 갖는 노드 탐색
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