#pragma once

#include "Libs.h"
#include "Node.h"
// single linkedList

enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT,
};

class List
{
    public:
    List();
    virtual ~List();

    //protected: 
    // Changed to public to avoid adding wrapper functions in HashTable class, which would make the class too large.
    void List_init();
    int List_ins_next(Node* tgt, MyAddr* data);
    int List_rem_next(Node* tgt, MyAddr** data);
    virtual int List_cmpData(const char* key1, const char* key2);
    void List_printAll();
    int List_getListSize();
    ErrCode List_getErrcode();

    Node* List_findNode_byID(const char* tgt_id);

    Node* List_makeNode(MyAddr* data);
    int List_deleteNode(Node* tgt);

    int listSize;
    ErrCode errCode;
    Node* headNode;
    Node* tailNode;

    private:
};
