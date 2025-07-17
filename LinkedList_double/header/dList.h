#pragma once

#include "List.h"
#include "dListNode.h"
#pragma comment (lib,"lib/singleLinkedList_debug.lib")
// double linkedList

class dList : public List
{
public:
    /*Management*/
    dList();
    virtual ~dList();

	bool insert_prevNode(void* node, void* data);
	bool remove_tgtNode(void* node, void** saveData);
	bool push_back(void* data);
	bool push_front(void* data);
	bool pop_back(void** saveData);
	bool pop_front(void** saveData);

    /*Utility*/
    void printAll() override;
    
    /*Accesor*/
    virtual const void* begin() override;
    virtual const void* end() override;
    virtual const void* next(const void* node) override;

protected:
    /*Utility-1*/
    void* makeNode() override;
    void initNode(void* node, void* data) override;
    void deleteNode(void** node) override;
    void destroyList() override;
    void* lookUp(void* data) override;

    bool insertNext(void* node, void* data) override;
    bool insertPrev(void* node, void* data);
    bool removeNode(void* node, void** saveData);

    bool pushBack(void* data) override;
    bool pushFront(void* data) override;
	bool popBack(void** saveData);
	bool popFront(void** saveData);

    /*Accessor-1*/
    typDoubleList_Node* get_DoubleList_head();
    void set_DoubleList_head(typDoubleList_Node* node);
    typDoubleList_Node* get_DoubleList_tail();
    void set_DoubleList_tail(typDoubleList_Node* node);

    void* get_nextNode(void* node) override;
    void set_nextNode(void* tgtNode, void* tgtAddr) override;
	void* get_prevNode(void* node);
	void set_prevNode(void* tgtNode, void* tgtAddr);
    void set_Data(void* node, void* data) override;
    void* get_Data(void* node) override;

private:
    /*Private*/
    using List::push_back;
    using List::push_front;
    using List::remove_nextNode; // 해당 메서드는 이 클래스에서 호출되면 안됨
    typDoubleList_Node* doubleList_headNode = nullptr;
    typDoubleList_Node* doubleList_tailNode = nullptr ;
};