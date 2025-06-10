#pragma once

#include "../header/bitree.h"
#include "../header/AvlTreeNode.h"

class AvlTree : public BiTree
{
public:
    /*Manangement*/
    int insert(const void* data);
    bool remove(const void* data);
    bool lookup(const void** data);
    void printAll() override;

    /*Utility*/
    AvlTree();
    ~AvlTree();
    bool init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
        , void (*printFunc)(const void* data)
        , void (*destroyDataFunc)(void* data)) override;
    void destroyTree() override;

protected:
    /*Utility-1*/
    virtual void initNode(void* node, void* data) override;
    virtual bool makeNode(void** node) override;
    virtual bool deleteNode(void** node) override;
    void inOrder_printNode(typAvlTreeNode* node);

    /*Overriding parent's methods*/
    virtual int insert_left(void* node, const void* data) override;
    virtual int insert_right(void* node, const void* data) override;
    virtual bool remove_left(void* node) override;
    virtual bool remove_right(void* node) override;

    /*Accessors*/
	void set_balFactor(typAvlTreeNode* node, typBalFactor balFactor);
    void set_hiddenFlag(typAvlTreeNode* node, typHiddenFlag hiddenFlag);
    typBalFactor get_balFactor(typAvlTreeNode* node);
	typHiddenFlag get_hiddenFlag(typAvlTreeNode* node);
    typAvlTreeNode* get_AvlTreeRoot();

    virtual void* get_leftPtr(void* node) override;
    virtual void* get_rightPtr(void* node) override;
    virtual void* get_data(void* node) override;

    virtual bool is_leafNode(void* node) override;
    virtual void set_leftPtr(void* tgtNode, void* tgtAddr) override;
    virtual void set_rightPtr(void* tgtNode, void* tgtAddr) override;
    virtual void set_data(void* node, void* data) override;


    /*Utility_2*/
    void rotate_left(typAvlTreeNode** node);
    void rotate_right(typAvlTreeNode** node);
    void destroy_left(typAvlTreeNode* node);
    void destroy_right(typAvlTreeNode* node);
    int recursive_insert(typAvlTreeNode** node, const void* data, typBalancedFlag* balanced);
    bool recursive_hide(typAvlTreeNode* node, const void* data);
    bool recursive_lookup(typAvlTreeNode* node, void** data);

private:
    /*Private*/
    typAvlTreeNode* AvlTreeRoot = nullptr;
};