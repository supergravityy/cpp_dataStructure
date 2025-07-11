#pragma once

#include "bitree.h"
#include "avltreeNode.h"

// todo : traverse 함수 avl에 맞게 수정하기

class AvlTree : public BiTree
{
public:
	/*Manangement*/
	int insert(const void* data);
	bool remove(const void* data);
	bool search(void** data);
	
	/*Utility*/
	AvlTree();
	~AvlTree();
	void printAll() override;
	int get_maxHeight() override;
	int get_Count();
	// init()
protected:
	/*Utility-1*/
	virtual void initNode(void* node, void* data) override;
	virtual bool makeNode(void** node) override;
	virtual bool deleteNode(void** node) override;
	void destroyTree() override;
	int cal_maxHeight(void* node) override;
	using BiTree::get_Size; // Prevent using BiTree's get_Size method
	using BiTree::mergeTree; // Prevent using BiTree's mergeTree method

	/*Overriding parent's methods*/
	int insert_left(void* node, const void* data) override;
	int insert_right(void* node, const void* data) override;
	bool remove_left(void* node) override;
	bool remove_right(void* node) override;

	/*Accessors*/
	void set_balFactor(typAvlTreeNode* node, typBalFactor balFactor);
	void set_hiddenFlag(typAvlTreeNode* node, typHiddenFlag hiddenFlag);
	typBalFactor get_balFactor(typAvlTreeNode* node);
	typHiddenFlag get_hiddenFlag(typAvlTreeNode* node);
	typAvlTreeNode* get_AvlTreeRoot();
	void set_AvlTreeRoot(typAvlTreeNode* node);

	virtual void* get_leftPtr(void* node) override;
	virtual void* get_rightPtr(void* node) override;
	virtual void* get_data(void* node) override;

	virtual bool is_leafNode(void* node) override;
	virtual void set_leftPtr(void* tgtNode, void* tgtAddr) override;
	virtual void set_rightPtr(void* tgtNode, void* tgtAddr) override;
	virtual void set_data(void* node, void* data) override;

	/*Manangement_2*/
	void rotate_left(typAvlTreeNode** node);
	void rotate_right(typAvlTreeNode** node);
	void destroy_left(typAvlTreeNode* node);
	void destroy_right(typAvlTreeNode* node);
	int recursive_insert(typAvlTreeNode** node, const void* data, typBalancedFlag* balanced);
	bool recursive_hide(typAvlTreeNode* node, const void* data);
	bool recursive_lookup(typAvlTreeNode* node, void** data);

	/*Variables*/
	int availableNodeCnt = 0;

private:
	/*Private*/
	using BiTree::lookup; // Prevent using BiTree's lookup method
	typAvlTreeNode* AvlTreeRoot = nullptr;
};