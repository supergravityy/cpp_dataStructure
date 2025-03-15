#include "../header/Set.h"

// public
Set::Set()
{
    // do nothing
}

Set::~Set()
{
    // do nothing
}

/* Management */
void Set::Set_init()
{
    this->List_init();
}

int Set::Set_insert(MyAddr *data) // 0 : insert cmplt, 1 : insert fail, 2 : prevent duplication
{
    if (this->Set_isElement(data))
        return 2;

    return this->List_ins_next(this->tailNode, data);
}

int Set::Set_remove(MyAddr **data) // 0 : remove cmplt, 1 : remove fail, 2 : not found
{
    Node *target = nullptr;
    Node *prevNode = nullptr;

    for (target = this->headNode; target != nullptr; target = target->nextNode)
    {
        if (this->Set_cmpData((*data)->id, target->data->id))
            break;

        prevNode = target;
    }

    if (target == NULL)
        return 2;
    else
        return this->List_rem_next(prevNode, data);
}

/* Operations */

// operationResult Set::Set_union(Set *resultSet, Set *AnotherSet)
operationResult Set::Set_union(Set* set1, Set* set2)
{
    Node *tempNode = nullptr;
    MyAddr *tempData = nullptr;

    if (set1 == nullptr || set2 == nullptr)
        return INVALID_TARGET;

    else
    {
        // 1. insert this Set data into resultSet
        for (tempNode = set1->headNode; tempNode != nullptr; tempNode = tempNode->nextNode)
        {
            tempData = tempNode->data;

            if (this->Set_insert(tempData) != 0)
            {
                this->Set_init();
                return UNION_FAULT;
            }
        }

        // 2. insert AnotherSet data into resultSet
        for (tempNode = set2->headNode; tempNode != nullptr; tempNode = tempNode->nextNode)
        {
            if (this->Set_isElement(tempNode->data)) // prevent duplication
                continue;

            else
            {
                tempData = tempNode->data;

                if (this->Set_insert(tempData) != 0)
                {
                    this->Set_init();
                    return UNION_FAULT;
                }
            }
        }

        return OPERATION_CMPLT;
    }
}

//operationResult Set::Set_intersection(Set *resultSet, Set *AnotherSet)
operationResult Set::Set_intersection(Set* set1, Set* set2)
{
    Node *tempNode = nullptr;
    MyAddr *tempData = nullptr;

    if (set1 == nullptr || set2 == nullptr)
        return INVALID_TARGET;

    else
    {
        for (tempNode = set1->headNode; tempNode != nullptr; tempNode = tempNode->nextNode)
        {
            if (set2->Set_isElement(tempNode->data)) // Insert only common elements
            {
                tempData = tempNode->data;
                if (this->List_ins_next(this->tailNode, tempData) != 0)
                {
                    this->Set_init();
                    return INTERSECTION_FAULT;
                }
            }
            tempData = nullptr;
        }

        return OPERATION_CMPLT;
    }
}

//operationResult Set::Set_difference(Set *resultSet, Set *AnotherSet)
operationResult Set::Set_difference(Set* set1, Set* set2)
{
    Node *tempNode = nullptr;
    MyAddr *tempData = nullptr;

    if (set1 == nullptr || set2 == nullptr)
        return INVALID_TARGET;

    else
    {
        for (tempNode = set1->headNode; tempNode != nullptr; tempNode = tempNode->nextNode)
        // Sr = S1 - S2 (Elements in S1 but not in S2)
        {
            if (!(set2->Set_isElement(tempNode->data)))
            {
                tempData = tempNode->data;
                if (this->List_ins_next(this->tailNode, tempData) != 0)
                {
                    this->Set_init();
                    return DIFFERENCE_FAULT;
                }
            }
            tempData = nullptr;
        }
        return OPERATION_CMPLT;
    }
}

/* Utility */
int Set::Set_getSetSize()
{
    return this->listSize;
}

ErrCode Set::Set_getErrCode()
{
    return this->errCode;
}

bool Set::Set_isElement(MyAddr *data)
{
    Node *tempNode = nullptr;

    for (tempNode = this->headNode; tempNode != nullptr; tempNode = tempNode->nextNode)
    {
        if (this->Set_cmpData(data->id, tempNode->data->id))
            return true;
    }

    return false;
}

bool Set::Set_isSubSet(Set *targetSet)
{
    Node *tempNode = nullptr;

    if (this->listSize > targetSet->Set_getSetSize())
        return false;

    else
    {
        for (tempNode = this->headNode; tempNode != nullptr; tempNode = tempNode->nextNode)
        {
            if (!(targetSet->Set_isElement(tempNode->data))) return false;
        }

        return true;
    }
}

bool Set::Set_isEqual(Set *targetSet)
{
    if (this->listSize != targetSet->Set_getSetSize())
        return false;

    else
    {
        return this->Set_isSubSet(targetSet);
    }
}

bool Set::Set_cmpData(const char *key1, const char *key2)
{
    return !(strcmp(key1, key2));
}