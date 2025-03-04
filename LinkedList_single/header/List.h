#pragma once

#include "Libs.h"
#include "Node.h"
#include "Data.h"
// single linkedList

enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT
};

class List
{
    public:
    List();
    ~List();

    int List_getSize();                                     //
    bool List_insertNext();                                 //
    bool List_removeNext();                                 //
    bool List_modifyData(const MyAddr* data);               //
    void List_printAll();                                   //
    bool List_findData_byID(const char* tgt_id);            //
    bool List_findData_byName(const char* tgt_name);        //
    bool List_findData_byPhone(const char* tgt_phone);      //
    void List_init();                                       //
    
    private:
    Node* List_findNode_byID(const char* tgt_id);           //
    Node* List_makeNode();                                  //
    Node* List_getHeadAddr();                               //
    Node* List_getTailAddr();                               //
    void List_setHeadAddr(Node* tgt);                       //
    void List_setTailAddr(Node* tgt);                       //
    

    int listSize;
    Node* headNode;
    Node* tailNode;
    ErrCode errCode;
};