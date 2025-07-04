#pragma once

#include "Libs.h"
#include "ListNode.h"
// single linkedList
//#define fordebug

typedef enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT
}typErrcode;

typedef enum compareResult
{
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
}typCmpResult;

class HashTable;  // 순환 참조를 방지하기위해, #include "HashTable.h" 대신, 전방선언을 사용해준다.

class List
{
    friend class HashTable; // List.h 의 구조를 바꿀 수 없는걸 가정하기에
public:
    /*Management*/
    List();
    virtual ~List();
    virtual bool init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
        , void (*printFunc)(const void* data)
        , void (*destroyDataFunc)(void* data));
    bool insert_nextNode(void* node, void* data);
	bool remove_nextNode(void* node, void** saveData);
	bool push_back(void* data);
    void* lookup_Node(void* data);
    virtual void destroyList();

    /*Utility*/
    virtual void printAll();
    int getSize();
	typErrcode getErrCode();
    virtual void set_Data(void* node, void* data);
    virtual void* get_Data(void* node);

#ifdef fordebug
    void* get_headAddr();
	void* get_nextAddr(void* node);
#endif 


protected:
    /*Utility-1*/
    virtual void* makeNode();
    virtual void initNode(void* node, void* data);
	virtual void deleteNode(void** node);
    virtual void* lookUp(void* data);
    virtual bool insertNext(void* node, void* data);
    virtual bool removeNext(void* node, void** saveData);
    virtual bool pushBack(void* data);
    virtual bool pushFront(void* data);
    

    /*Accessor*/
	typSingleList_Node* get_SingleList_head();
    void set_SingleList_head(typSingleList_Node* node);
	typSingleList_Node* get_SingleList_tail();
    void set_SingleList_tail(typSingleList_Node* node);
	bool is_emptyNode(void* node);
    virtual void set_nextNode(void* tgtNode, void* tgtAddr);
    virtual void* get_nextNode(void* node);

    /*Variance*/
    int size = 0;
    typErrcode errCode = NORMAL;
    typCmpResult(*cmpFunc)(const void* key1, const void* key2) = nullptr;
    void (*printFunc)(const void* data) = nullptr;
    void (*freeDataFunc)(void* data) = nullptr;

private:
    /*Private*/
    typSingleList_Node* singleList_head = nullptr;
	typSingleList_Node* singleList_tail = nullptr;
};