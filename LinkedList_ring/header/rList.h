#pragma once

#include "Libs.h"
#include "rNode.h"
// ring linkerList

enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT,
};

class rList
{
    public:
    rList();                                                            //
    virtual ~rList();                                                   //

    void rList_init(); // == destroy                                    //
    int rList_ins_next(rNode* tgt, MyAddr* data);                       // 
    int rList_rem_next(rNode* tgt, MyAddr** data);                      //
    virtual int rList_cmpData(const char* key1, const char* key2);      //
    void rList_printAll();                                              //
    int rList_getListSize();                                            //
    ErrCode rList_getErrcode();                                         //

    rNode* rList_findNode_byID(const char* tgt_id);            

    private:
    rNode* rList_makeNode(MyAddr* data);                        
    int rList_deleteNode(rNode** tgt);                          

    int listSize;
    ErrCode errCode;
    rNode* headNode;
};