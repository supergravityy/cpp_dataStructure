#pragma once

#include "List.h"

class Set : public List
{
public:
    Set();
    virtual ~Set();

    /* Management */
    void Set_init();
    int Set_insert(MyAddr* data);
    int Set_remove(MyAddr** data);

    /* Operations */
    Set* Set_union(const Set* AnotherSet);
    Set* Set_intersection(const Set* AnotherSet);
    Set* Set_difference(const Set* AnotherSet);
    
    /* Utility */
    int Set_getSetSize();
    ErrCode Set_getErrCode();

private:
    bool Set_isElement(MyAddr* data);
    bool Set_isEqual(const Set* AnotherSet);
    virtual int Set_cmpData(const char* key1, const char* key2);
};