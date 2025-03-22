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
    
    /*Utility*/
    int BiTree_getSize();
    void BiTree_setSize(int size);
    ErrCode BiTree_getErrCode();
    bool BiTree_cmpData(const char* key1, const char* key2);
    BiTreeNode* BiTree_makeNode();

private:
    ErrCode errCode;
    int treeSize;
    BiTreeNode* root;
};

/*    cout << "1. Merge" << endl;
    cout << "2. Skip" << endl;
    cout << "3. Reset tree" << endl;
    cout << "4. Print All" << endl;
    cout << "0. Exit" << endl;*/
