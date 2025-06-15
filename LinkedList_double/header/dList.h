#pragma once

#include "Libs.h"
#include "List.h"
#include "dListNode.h"
// double linkedList

class dList : public List
{
public:
    /*Management*/
    dList();
    virtual ~dList();

    // bool insert_nextNode(void* node, void* data);
	bool insert_prevNode(void* node, void* data);
	bool remove_tgtNode(void* node, void** saveData);
	// bool push_back(void* data);
	bool push_front(void* data);
	bool pop_back(void** saveData);
	bool pop_front(void** saveData);
	// void* lookup_node(void* data);
    

    /*Utility*/
    void printAll() override;
    // int getSize();
    // typErrcode getErrCode();
    void set_Data(void* node, void* data) override;
    void* get_Data(void* node) override;
    void destroyList() override;

protected:
    /*Utility-1*/
    void* makeNode() override;
    void initNode(void* node, void* data) override;
    void deleteNode(void** node) override;
    void* lookUp(void* data) override;

    bool insertNext(void* node, void* data) override;
    bool insertPrev(void* node, void* data);
    bool removeNode(void* node, void** saveData);

    bool pushBack(void* data) override;
    bool pushFront(void* data) override;
	bool popBack(void** saveData);
	bool popFront(void** saveData);

    /*Accessor*/
    typDoubleList_Node* get_DoubleList_head();
    void set_DoubleList_head(typDoubleList_Node* node);
    typDoubleList_Node* get_DoubleList_tail();
    void set_DoubleList_tail(typDoubleList_Node* node);
    // bool is_emptyNode(void* node);
    void* get_nextNode(void* node) override;
    void set_nextNode(void* tgtNode, void* tgtAddr) override;
	void* get_prevNode(void* node);
	void set_prevNode(void* tgtNode, void* tgtAddr);

    // /*Variance*/
    // int size = 0;
    // typErrcode errCode = NORMAL;
    // typCmpResult(*cmpFunc)(const void* key1, const void* key2) = nullptr;
    // void (*printFunc)(const void* data) = nullptr;
    // void (*freeDataFunc)(void* data) = nullptr;

private:
    /*Private*/
    bool remove_nextNode(void* node, void** saveData);
    typDoubleList_Node* doubleList_headNode = nullptr;
    typDoubleList_Node* doubleList_tailNode = nullptr ;
};