#include "../header/Set.h"

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

int Set::Set_insert(MyAddr* data) // 0 : insert cmplt, 1 : insert fail, 2 : prevent duplication
{
    if(this->Set_isElement(data)) return 2;

    return this->List_ins_next(this->tailNode, data);
}

int Set::Set_remove(MyAddr** data) // 0 : remove cmplt, 1 : remove fail, 2 : not found
{
    Node* target = nullptr;
    Node* prevNode = nullptr;

    for(target = this->headNode; target != nullptr; target = target->nextNode)
    {
        if(this->Set_cmpData((*data)->id, target->data->id))
            break;

        prevNode = target;
    }

    if(target == NULL) 
        return 2;
    else
        return this->List_rem_next(target,data);
}

