#pragma once

#include "List.h"

enum operationResult
{
    NO_OPERATION = 0,
    OPERATION_CMPLT,
    INVALID_TARGET,
    UNION_FAULT,
    INTERSECTION_FAULT,
    DIFFERENCE_FAULT
};

class Set : public List
{
public:
    Set();                                                                      //
    virtual ~Set();                                                             //

    /* Management */
    void Set_init();                                                            //
    int Set_insert(MyAddr* data);                                               //
    int Set_remove(MyAddr** data);                                              //

    /* Operations */
    operationResult Set_union(Set* set1, Set* set2);                            //
    operationResult Set_intersection(Set* set1, Set* set2);                     //
    operationResult Set_difference(Set* set1, Set* set2);                       // Sr = S1 - S2
    
    /* Utility */
    int Set_getSetSize();                                                       //
    ErrCode Set_getErrCode();                                                   //  
    bool Set_isElement(MyAddr* data);                                           //
    bool Set_isEqual(Set* AnotherSet);                                          //
    bool Set_isSubSet(Set* targetSet);                                          // S1 = S1 n S2 -> S1 is subset of S2 
    void Set_printAll();                                                        //

protected:    
    virtual bool Set_cmpData(const char* key1, const char* key2);               //

private:
};