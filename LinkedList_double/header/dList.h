#pragma once

#include "Libs.h"
#include "dNode.h"
// double linkedList

enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT,
};

class dList 
{
    public:
    dList();                                                    //
    virtual ~dList();                                           //

    void dList_init(); // == destroy                            //
    int dList_ins_next(dNode* tgt, MyAddr* data);               //
    int dList_ins_prev(dNode* tgt, MyAddr* data);               //
    int dList_remove(dNode* tgt, MyAddr** data);               //
    virtual int dList_cmpData(const char* key1, const char* key2);      //
    void dList_printAll();                                      //
    int dList_getListSize();                                    //
    ErrCode dList_getErrcode();                                 //

    dNode* dLiset_findNode_byID(const char* tgt_id);            //

    private:
    dNode* dList_makeNode(MyAddr* data);                        //
    int dList_deleteNode(dNode** tgt);                          //

    int listSize;
    ErrCode errCode;
    dNode* headNode;
    dNode* tailNode;
};