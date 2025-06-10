#pragma once

#include "../header/Libs.h"
#include "../header/BiTreeNode.h"

#define INSERT_SUCCESS          0
#define INSERT_FAILED           1
#define INSERT_CHILD_EXISTS     2
#define INSERT_MEMORY_ERR       3

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

class BiTree
{
public:
    /*Manangement*/
    int insert_leftChild(void* node, const void* data);
	int insert_rightChild(void* node, const void* data);
	bool remove_leftChild(void* node);
	bool remove_rightChild(void* node);
    virtual bool merge(void* leftTree, void* rightTree, void* data);
    virtual void printAll();

    /*Utility*/
    BiTree();
    virtual ~BiTree();
	virtual void destroyTree();
    virtual bool init(typCmpResult (*compareFunc)(const void* key1, const void* key2)
        , void (*printFunc)(const void* data)
        , void (*destroyDataFunc)(void* data));
    int get_Size();
	typErrcode get_ErrCode();

protected:
	/*Utility-1*/
    virtual void initNode(void* node, void* data);
    virtual bool makeNode(void** node);
    virtual bool deleteNode(void** node);
    virtual int insert_left(void* node, const void* data);
    virtual int insert_right(void* node, const void* data);
    virtual bool remove_left(void* node);
    virtual bool remove_right(void* node);

    /*Traverse*/
    bool preOrder(typBiTreeNode* node, void* data);
    bool inOrder(typBiTreeNode* node, void* data);
    bool postOrder(typBiTreeNode* node, void* data);
    void preOrder_printNode(typBiTreeNode* node);

    /*Accessors*/
    typBiTreeNode* get_BiTreeRoot();
    bool is_emptyNode(void* node);
    virtual bool is_leafNode(void* node);
    virtual void set_leftPtr(void* tgtNode, void* tgtAddr);
	virtual void set_rightPtr(void* tgtNode, void* tgtAddr);
	virtual void* get_leftPtr(void* node);
	virtual void* get_rightPtr(void* node);
	virtual void set_data(void* node, void* data);
    virtual void* get_data(void* node);

    /*Variance*/
    int treeSize = 0;
    typCmpResult (*compareFunc)(const void* key1, const void* key2) = nullptr;
    void (*printFunc)(const void* data) = nullptr;
    void (*destroyDataFunc)(void* data) = nullptr;
    typErrcode errCode = NORMAL;

private:
    /*Private*/
    typBiTreeNode* BiTreeRoot = nullptr;
};