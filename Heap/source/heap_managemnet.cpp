#include "../header/heap.h"

Heap::Heap() 
{
	this->size = 0;
	this->errCode = NORMAL;
	this->compareFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->printDataFunc = nullptr;
	this->treeAddr = nullptr;
}

Heap::~Heap()
{
	this->destroyTree();

	this->size = 0;
	this->errCode = NORMAL;
	this->compareFunc = nullptr;
	this->destroyDataFunc = nullptr;
	this->printDataFunc = nullptr;
	this->treeAddr = nullptr;
}

bool Heap::init(typCmpResult(*compareFunc)(const void* key1, const void* key2),
	void (*destroyDataFunc)(void* data),
	void (*printDataFunc)(void* data))
{
	if(compareFunc == nullptr || destroyDataFunc == nullptr || printDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	else
	{
		this->size = 0;
		this->errCode = NORMAL;
		this->compareFunc = compareFunc;
		this->destroyDataFunc = destroyDataFunc;
		this->printDataFunc = printDataFunc;
		this->treeAddr = nullptr;

		return true;
	}
}

void* Heap::peek()
{
	if (this->get_size() == 0)
		return nullptr;
	else
		return this->treeAddr[0];
}

bool Heap::insert(void* data)
{
	void** tempAddr = nullptr;
	int currIdx, parentIdx;

	if (data == nullptr)
	{
		this->errCode = SYS_FAULT;
		return false;
	}
	
	tempAddr = this->reAlloc_treeAddr(this->size + 1);						// 1. 힙 배열 크기 증가 (재할당)
	if (tempAddr == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	this->set_treeAddr(tempAddr);
	this->size++;

	currIdx = this->get_size() - 1;											// 2. 새 노드의 인덱스와 부모 노드 인덱스 계산
	parentIdx = this->get_parentIdx(currIdx);

	this->set_treeNode(currIdx, data);										// 3. 새 노드의 데이터를 현재 인덱스에 저장

																			// 4. 새 노드(leaf)가 부모 노드보다 크면 상향식으로 힙 속성 유지 (최대힙 기준)
	while ((currIdx > 0) &&
		(this->compareFunc(this->get_treeNode(currIdx), this->get_treeNode(parentIdx)) == GREATER)) 
		// 현재 노드가 부모 노드보다 크면 위로 올라가야 한다. (최대힙 기준)
	{
		this->swapTreeNodes(currIdx, parentIdx);							// 5. 현재 노드와 부모 노드의 내용을 교환
		
		currIdx = parentIdx;												// 6. 현재 노드 인덱스를 targetIdx로 갱신 (상향식)
		parentIdx = this->get_parentIdx(currIdx);
	}

	return true;
}

bool Heap::extract(void** extractData)
{
	void* saveData, **tempTree = nullptr;

	if (this->get_size() == 0)
		return false;

	*extractData = this->treeAddr[0];							// 1. 루트 노드의 데이터를 저장
	saveData = this->treeAddr[this->get_size() - 1];			// 2. 맨 마지막 노드의 데이터 주소 임시보관
	this->size--;												// 3. 힙의 크기 감소

	if (this->get_size() > 0)
	{
		tempTree = this->reAlloc_treeAddr(this->get_size());	// 4. 힙 배열 크기 감소 (재할당)
		if (tempTree == nullptr)
		{
			this->errCode = MEMORY_ERR;
			return false;
		}
		else
		{
			this->set_treeAddr(tempTree);						
			this->set_treeNode(0, saveData);					// 5. 루트노드가 빠졌기에 해당위치에 맨 마지막 노드로 덮어쓰기
			this->reHeapify();									// 6. 하향식으로 재힙화

			return true;
		}
	}
	else
	{
		this->freeTreeAddr();									// 4-1. 힙 배열 크기가 0이 되면 트리 주소 해제
		this->treeAddr = nullptr;
		this->size = 0;

		return true;
	}
}

void Heap::reHeapify()	// 하향식 재힙화 과정 (설명기준 : 최대힙)
{
	int currIdx = 0, leftIdx = 0,rightIdx = 0, targetIdx = 0;

	while (true)
	{
		leftIdx = this->get_leftChildIdx(currIdx);					// 1. 하향식 재힙화를 위한 인덱스번호 계산
		rightIdx = this->get_rightChildIdx(currIdx);
		targetIdx = currIdx;

																	// 2. 왼쪽 자식노드가 현재 노드보다 크면 targetIdx를 왼쪽 자식노드로 설정 (최대힙 기준 -> 부모key값 > 자식key값)
		if (leftIdx < this->get_size() &&
			this->compareFunc(this->get_treeNode(leftIdx), this->get_treeNode(targetIdx)) == GREATER)	
		{
			targetIdx = leftIdx;
		}

																	// 3. 혹은 오른쪽 자식노드가 현재 노드보다 크면 targetIdx를 오른쪽 자식노드로 설정 (힙자료구조는 루트만 최대/최소 값이면 장땡)
		if (rightIdx < this->get_size() &&
			this->compareFunc(this->get_treeNode(rightIdx), this->get_treeNode(targetIdx)) == GREATER)	
		{
			targetIdx = rightIdx;
		}

		
		if (targetIdx == currIdx)									// 4. 자식노드들이 현재 노드보다 크지 않으면 재 힙화 종료
			break;							
		else
		{
			this->swapTreeNodes(currIdx, targetIdx);				// 5. 현재 노드와 targetIdx 노드의 데이터를 교환 
			currIdx = targetIdx;									// 6. 현재 노드 인덱스를 targetIdx(자식 인덱스번호)로 갱신 (하향식)
		}
	}
}