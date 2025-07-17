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
	bool lookup(void** saveData); // input : 찾을 데이터, output : 찾은 데이터 -> 이상하지 않은가? 
	// => cmpFunc는 구조체 안에 특정 멤버로만 검색하기에, 모두 입력하지 않은 구조체를 넘겨도 됨

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