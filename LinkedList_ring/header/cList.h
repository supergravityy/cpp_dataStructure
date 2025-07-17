#pragma once

#include "List.h"
#pragma comment (lib,"lib/singleLinkedList_debug.lib")
/*circular list*/

typedef typSingleList_Node typCircularList_Node;

class cList : public List
{
public:
	/*Management*/
	cList();
	virtual ~cList();
	bool push_front(void* data);
	bool pop_front(void** saveData);

	/*Utility*/
	void printAll() override;

	/*Accesor*/
	virtual const void* begin() override;
	virtual const void* end() override;

protected:
	/*Utility-1*/
	void* makeNode() override;
	void initNode(void* node, void* data) override;
	void deleteNode(void** node) override;
	
	void* lookUp(void* data) override;
	bool insertNext(void* node, void* data) override;
	bool removeNext(void* node, void** saveData) override;
	bool pushFront(void* data) override;
	bool pushBack(void* data) override; // 해당 메서드는 이 클래스에서 호출되면 안되게 조치함
	bool popFront(void** saveData);
	void destroyList() override;
	
	/*Accessor-1*/
	typCircularList_Node* get_CircularList_head();
	void set_CircularList_head(typCircularList_Node* head);
	void set_nextNode(void* tgtNode, void* tgtAddr) override;
	void* get_nextNode(void* node) override;
	void* get_Data(void* node) override;
	void set_Data(void* node, void* data) override;

private:
	/*Private*/
	typCircularList_Node* circularList_head = nullptr;
	using List::push_back; // 해당 메서드는 이 클래스에서 호출되면 안됨 (UI)
};