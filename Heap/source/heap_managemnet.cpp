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
	
	tempAddr = this->reAlloc_treeAddr(this->size + 1);						// 1. �� �迭 ũ�� ���� (���Ҵ�)
	if (tempAddr == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	this->set_treeAddr(tempAddr);
	this->size++;

	currIdx = this->get_size() - 1;											// 2. �� ����� �ε����� �θ� ��� �ε��� ���
	parentIdx = this->get_parentIdx(currIdx);

	this->set_treeNode(currIdx, data);										// 3. �� ����� �����͸� ���� �ε����� ����

																			// 4. �� ���(leaf)�� �θ� ��庸�� ũ�� ��������� �� �Ӽ� ���� (�ִ��� ����)
	while ((currIdx > 0) &&
		(this->compareFunc(this->get_treeNode(currIdx), this->get_treeNode(parentIdx)) == GREATER)) 
		// ���� ��尡 �θ� ��庸�� ũ�� ���� �ö󰡾� �Ѵ�. (�ִ��� ����)
	{
		this->swapTreeNodes(currIdx, parentIdx);							// 5. ���� ���� �θ� ����� ������ ��ȯ
		
		currIdx = parentIdx;												// 6. ���� ��� �ε����� targetIdx�� ���� (�����)
		parentIdx = this->get_parentIdx(currIdx);
	}

	return true;
}

bool Heap::extract(void** extractData)
{
	void* saveData, **tempTree = nullptr;

	if (this->get_size() == 0)
		return false;

	*extractData = this->treeAddr[0];							// 1. ��Ʈ ����� �����͸� ����
	saveData = this->treeAddr[this->get_size() - 1];			// 2. �� ������ ����� ������ �ּ� �ӽú���
	this->size--;												// 3. ���� ũ�� ����

	if (this->get_size() > 0)
	{
		tempTree = this->reAlloc_treeAddr(this->get_size());	// 4. �� �迭 ũ�� ���� (���Ҵ�)
		if (tempTree == nullptr)
		{
			this->errCode = MEMORY_ERR;
			return false;
		}
		else
		{
			this->set_treeAddr(tempTree);						
			this->set_treeNode(0, saveData);					// 5. ��Ʈ��尡 �����⿡ �ش���ġ�� �� ������ ���� �����
			this->reHeapify();									// 6. ��������� ����ȭ

			return true;
		}
	}
	else
	{
		this->freeTreeAddr();									// 4-1. �� �迭 ũ�Ⱑ 0�� �Ǹ� Ʈ�� �ּ� ����
		this->treeAddr = nullptr;
		this->size = 0;

		return true;
	}
}

void Heap::reHeapify()	// ����� ����ȭ ���� (������� : �ִ���)
{
	int currIdx = 0, leftIdx = 0,rightIdx = 0, targetIdx = 0;

	while (true)
	{
		leftIdx = this->get_leftChildIdx(currIdx);					// 1. ����� ����ȭ�� ���� �ε�����ȣ ���
		rightIdx = this->get_rightChildIdx(currIdx);
		targetIdx = currIdx;

																	// 2. ���� �ڽĳ�尡 ���� ��庸�� ũ�� targetIdx�� ���� �ڽĳ��� ���� (�ִ��� ���� -> �θ�key�� > �ڽ�key��)
		if (leftIdx < this->get_size() &&
			this->compareFunc(this->get_treeNode(leftIdx), this->get_treeNode(targetIdx)) == GREATER)	
		{
			targetIdx = leftIdx;
		}

																	// 3. Ȥ�� ������ �ڽĳ�尡 ���� ��庸�� ũ�� targetIdx�� ������ �ڽĳ��� ���� (���ڷᱸ���� ��Ʈ�� �ִ�/�ּ� ���̸� �嶯)
		if (rightIdx < this->get_size() &&
			this->compareFunc(this->get_treeNode(rightIdx), this->get_treeNode(targetIdx)) == GREATER)	
		{
			targetIdx = rightIdx;
		}

		
		if (targetIdx == currIdx)									// 4. �ڽĳ����� ���� ��庸�� ũ�� ������ �� ��ȭ ����
			break;							
		else
		{
			this->swapTreeNodes(currIdx, targetIdx);				// 5. ���� ���� targetIdx ����� �����͸� ��ȯ 
			currIdx = targetIdx;									// 6. ���� ��� �ε����� targetIdx(�ڽ� �ε�����ȣ)�� ���� (�����)
		}
	}
}