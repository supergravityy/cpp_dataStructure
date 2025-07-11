#include "../header/heap.h"

int Heap::get_parentIdx(int currIdx)
{
	return (currIdx - 1) / 2;
}
int Heap::get_leftChildIdx(int currIdx)
{
	return (currIdx * 2) + 1;
}
int Heap::get_rightChildIdx(int currIdx)
{
	return (currIdx * 2) + 2;
}
void* Heap::get_treeNode(int idx)
{
	if (idx < this->size)
		return this->treeAddr[idx];
	else
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
}
void Heap::set_treeNode(int idx, void* data)
{
	if (idx < this->size)
		this->treeAddr[idx] = data;
	else
	{
		this->errCode = SYS_FAULT;
		return;
	}
}
void** Heap::get_treeAddr()
{
	return this->treeAddr;
}
void Heap::set_treeAddr(void** newArrayAddr)
{
	this->treeAddr = newArrayAddr;
}