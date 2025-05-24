#pragma once

#include "BitreeNode.h"

enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT,
};

class BiTree
{
public:
    BiTree();
    virtual ~BiTree();

    /*Management*/
    void BiTree_init();
    int BiTree_ins_left(BiTreeNode* node, MyAddr* data);
    int BiTree_ins_right(BiTreeNode* node, MyAddr* data);
    bool BiTree_rem_left(BiTreeNode* node);
    bool BiTree_rem_right(BiTreeNode* node);
    bool BiTree_merge( BiTree* left, BiTree* right, MyAddr* data);
    void BiTree_printAll();

    bool BiTree_preOrder_find(BiTreeNode *node, MyAddr* tgt);
    bool BiTree_inOrder_find(BiTreeNode *node, MyAddr* tgt);
    bool BiTree_postOrder_find(BiTreeNode *node, MyAddr* tgt);
    
    /*Utility*/
    BiTreeNode* BiTree_preOrder_search(BiTreeNode* node, MyAddr* tgt);
    BiTreeNode* BiTree_inOrder_search(BiTreeNode* node, MyAddr* tgt);
    BiTreeNode* BiTree_postOrder_search(BiTreeNode* node, MyAddr* tgt);

    int BiTree_getSize();
    void BiTree_setSize(int size);
    ErrCode BiTree_getErrCode();
    bool BiTree_cmpData(const char* key1, const char* key2);
    BiTreeNode* BiTree_makeNode();
    void preOrderPrint(BiTreeNode* node);
	BiTreeNode* BiTree_getRoot();

private:
    ErrCode errCode;
    int treeSize;
    BiTreeNode* root;
};
