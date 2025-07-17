#pragma once

#include "List.h"
#include "ListNode.h"
#include "HashFunc.h"
#pragma comment (lib,"lib/singleLinkedList_debug.lib")
#pragma comment (lib,"lib/hashFunc_debug.lib")
// hash table

class HashTable
{
public:
	/*Management*/
	HashTable();
	~HashTable();

	bool init(typCmpResult(*cmpFunc)(const void* key1, const void* key2), 
		void (*printFunc)(const void* data),
		void (*freeDataFunc)(void* data),
		void* (*getKeyVal) (void* data), int bucketNum,
		int (*hashFunc) (const void* key, int bucketCnt) = defaultFunc::method_Division);

	bool insert(void* data);
	bool remove(void** saveData);
	bool lookup(void** saveData); // input : ã�� ������, output : ã�� ������ -> �̻����� ������? 
	// => cmpFunc�� ����ü �ȿ� Ư�� ����θ� �˻��ϱ⿡, ��� �Է����� ���� ����ü�� �Ѱܵ� ��

	/*Utility*/
	int get_tableSize();
	int get_size();
	void print_allData();
	int* get_bucketSizeArr();
	typErrcode get_errCode();

protected:
	/*Utility-1*/
	void destroyBuckets();
	bool initBuckets();

	/*Variables*/
	int bucketCnt;
	int size;
	typErrcode errCode;
	typCmpResult(*cmpFunc)(const void* key1, const void* key2);
	void (*printFunc)(const void* data);
	void (*freeDataFunc)(void* data);
	int (*hashFunc) (const void* key, int bucketCnt);
	void* (*getKeyVal) (void* data);

private:
	/*Private*/
	List* table;
};