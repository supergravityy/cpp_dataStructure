#include "../header/HashTable.h"

int HashTable::get_tableSize()
{
	return this->bucketCnt;
}

int HashTable::get_size()
{
	return this->size;
}

typErrcode HashTable::get_errCode()
{
	return this->errCode;
}

void HashTable::print_allData()
{
	for (int i = 0; i < this->bucketCnt; i++)
	{
		this->table[i].printAll();
		cout << "==========" << endl;
	}
}

int* HashTable::get_bucketSizeArr()
{
	int* resultArr;

	if (this->bucketCnt == 0)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
	{
		resultArr = new int[this->bucketCnt];

		if (resultArr == nullptr)
			this->errCode = MEMORY_ERR;
		else
		{
			for (int i = 0; i < this->bucketCnt; i++)
			{
				resultArr[i] = this->table[i].getSize();
			}
		}
		return resultArr;
	}
}

bool HashTable::initBuckets()
{
	for (int i = 0; i < this->bucketCnt; i++)
	{
		if (this->table[i].init(this->cmpFunc, this->printFunc, this->freeDataFunc) == false)
		{
			this->errCode = SYS_FAULT;
			return false;
		}
	}
	
	return true;
}

void HashTable::destroyBuckets()
{
	for (int i = 0; i < this->bucketCnt; i++)
	{
		this->table[i].destroyList();
	}

	delete[] this->table;
}