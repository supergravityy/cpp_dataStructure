#pragma once

#include "bitreeNode.h"
#include "Stack.h"
#pragma comment (lib,"lib/stack_debug.lib")

#define INSERT_SUCCESS          0
#define INSERT_FAILED           1
#define INSERT_CHILD_EXISTS     2
#define INSERT_MEMORY_ERR       3

class BiTree
{
public:
    /*Manangement*/
    BiTree();
    virtual ~BiTree();
    virtual bool init(typCmpResult(*compareFunc)(const void* key1, const void* key2)
        , void (*printFunc)(void* node)
        , void (*destroyDataFunc)(void* data)
        , void* (*traverseFunc)(void* node, void** saveData));
    int insert_leftChild(void* node, const void* data);
	int insert_rightChild(void* node, const void* data);
	bool remove_leftChild(void* node);
	bool remove_rightChild(void* node);
    bool mergeTree(void* leftTree, void* rightTree, void* data);
    
    /*Utility*/
    int get_Size();
    virtual int get_maxHeight();
	typErrcode get_ErrCode();
    virtual void* lookup(void** node);
    virtual void printAll();

    /*Accessor*/
    virtual void reset_iter();
    virtual const void* begin();
    virtual const void* end();
    virtual const void* next(void* node);
    virtual const void* data(void* node);

protected:
	/*Utility-1*/
    virtual void initNode(void* node, void* data);
    virtual bool makeNode(void** node);
    virtual bool deleteNode(void** node);

    virtual void destroyTree();
    virtual int insert_left(void* node, const void* data);
    virtual int insert_right(void* node, const void* data);
    virtual bool remove_left(void* node);
    virtual bool remove_right(void* node);
    virtual bool merge(void* leftTree, void* rightTree, void* data);

    virtual int cal_maxHeight(void* node);
    bool is_emptyNode(void* node);
    virtual bool is_leafNode(void* node);

    /*Accessors*/
    typBiTreeNode* get_BiTreeRoot();
    virtual void set_leftPtr(void* tgtNode, void* tgtAddr);
	virtual void set_rightPtr(void* tgtNode, void* tgtAddr);
	virtual void* get_leftPtr(void* node);
	virtual void* get_rightPtr(void* node);
	virtual void set_data(void* node, void* data);
    virtual void* get_data(void* node);

    /*Variance*/
    int treeSize = 0;
    typCmpResult (*compareFunc)(const void* key1, const void* key2) = nullptr;
    void (*printTreeFunc)(void* node) = nullptr;
    void (*destroyDataFunc)(void* data) = nullptr;
    void* (*traverseFunc)(void* node, void** saveData) = nullptr;
    typErrcode errCode = NORMAL;
    Stack parentsAddrs;

private:
    /*Private*/
    typBiTreeNode* BiTreeRoot = nullptr;
};