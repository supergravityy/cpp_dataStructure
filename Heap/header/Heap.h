#pragma once

#include "Libs.h"

typedef enum 
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT
}typErrCode;

typedef enum compareResult
{
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
}typCmpResult;

class Heap
{
public:
    /*Management*/
    Heap();
    virtual ~Heap();
    bool init(typCmpResult (*compareFunc)(const void* key1, const void* key2),
        void (*destroyDataFunc)(void* data), 
        void (*printDataFunc)(void* data));
    bool insert(void* data);
    bool extract(void** extractData);
	void* peek();
    
    /*Utility*/
    void printAll();
    int get_size();
    typErrCode get_errCode();

protected:
    /*Utility-1*/
	void reHeapify();
    void destroyTree();
	void freeTreeAddr();
    void** reAlloc_treeAddr(int newSize);
    void swapTreeNodes(int i, int j);

    /*Accessors*/
    int get_parentIdx(int currIdx);
    int get_leftChildIdx(int currIdx);
    int get_rightChildIdx(int currIdx);
	void* get_treeNode(int idx);
	void set_treeNode(int idx, void* data);
    void** get_treeAddr();
	void set_treeAddr(void** newArrayAddr);

    /*Variables*/
    int size;
    typErrCode errCode;
    typCmpResult (*compareFunc)(const void* key1, const void* key2);
    void (*destroyDataFunc)(void* data);
    void (*printDataFunc)(void* data);

private:
    /*Privates*/
    void** treeAddr;
};