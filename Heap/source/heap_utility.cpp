#include "../header/heap.h"

int Heap::get_size()
{
	return this->size;
}
typErrCode Heap::get_errCode()
{
	return this->errCode;
}
void Heap::freeTreeAddr()
{
	delete[] this->treeAddr;
}
void** Heap::reAlloc_treeAddr(int newSize)
{
	return (void**)realloc(this->treeAddr, sizeof(void*) * newSize);
}

void Heap::printAll()
{
	if (this->printDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else
	{
		for (int i = 0; i < this->get_size(); i++)
		{
			this->printDataFunc(this->treeAddr[i]);		// 각 노드의 데이터 출력
		}
	}
}
void Heap::destroyTree()
{
	int i;

	if (this->treeAddr == nullptr) return;
		
	else if (this->destroyDataFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return;
	}
	else
	{
		for (i = 0; i < this->get_size(); i++)			// 각 노드의 데이터 삭제
		{
			this->destroyDataFunc(this->treeAddr[i]);	
		}
		this->size = 0;
		this->freeTreeAddr();							// 트리 주소 해제
		return;
	}
}
void Heap::swapTreeNodes(int i, int j) 
{
	void* temp = this->get_treeNode(i);
	this->set_treeNode(i, this->get_treeNode(j));
	this->set_treeNode(j, temp);
}