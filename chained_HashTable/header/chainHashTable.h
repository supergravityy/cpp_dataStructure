#pragma once

#include "List.h"
#include "HashingFunc.h"


class HashTable : public List, HashingFunc
{
public:
    HashTable();
    virtual ~HashTable();

    /* Management */
    bool HashTable_init(int tableSize);
    void HashTable_destroy();
    int HashTable_insert(MyAddr* data);
    int HashTable_remove(MyAddr** data);
    bool HashTable_lookup(MyAddr** data);
    
    /* Utility */
    // HashingFunc_setBucketSize, HashingFunc_getBucketSize are in HashingFunc
    void HashTable_printAll();
    int HashTable_getNodeSize();
    ErrCode HashTable_getErrCode(); 
    virtual bool HashTable_cmpData(const char* key1, const char* key2);
    void HashTable_updatdErrCode();

private:
    int NodeSize;
    List* table;
};

