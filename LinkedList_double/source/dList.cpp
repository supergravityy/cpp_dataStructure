#include "../header/dList.h"

/*----utils----*/

void printData(MyAddr* data) // 함수포인터로 작성하게 하면 더 좋을듯 ??
{
    cout << "ID : ";
    cout << data->id << endl;
    cout << "Name : ";
    cout << data->name << endl;
    cout << "PhoneNumber : ";
    cout << data->phone << endl;
}

/*----public----*/

dList::dList()
{
    this->headNode = nullptr;
    this->tailNode = nullptr;
    this->listSize = 0;
    this->errCode = NORMAL;
}

dList::~dList()
{
    this->dList_init();
}

void dList::dList_init()
{
    dNode *tgtNode = this->headNode;
    dNode *nextNode = nullptr;
    MyAddr *tempData = nullptr;

    while (tgtNode != nullptr)
    {
        nextNode = tgtNode->nextNode;

        this->dList_remove(tgtNode, &tempData);
        tgtNode = nextNode;
    }

    this->headNode = nullptr;
    this->tailNode = nullptr;
    this->listSize = 0;
}

int dList::dList_ins_next(dNode *tgt, MyAddr *data)
{
    dNode *newNode = nullptr;
    dNode *nextNode_ofTgt = nullptr;

    newNode = this->dList_makeNode(data);

    if ((this->listSize > 0 && tgt == nullptr) || newNode == nullptr || this->errCode != NORMAL)
        return 1;

    else
    {
        if (this->listSize == 0)
        {
            this->headNode = newNode;
            this->tailNode = newNode;
            newNode->nextNode = nullptr;
            newNode->prevNode = nullptr;
        }
        else
        {
            nextNode_ofTgt = tgt->nextNode;

            newNode->nextNode = nextNode_ofTgt;
            newNode->prevNode = tgt;

            if (tgt->nextNode == nullptr)
                this->tailNode = newNode;

            else
                nextNode_ofTgt->prevNode = newNode;
            
            tgt->nextNode = newNode;
        }

        this->listSize++;

        return 0;
    }
}

int dList::dList_ins_prev(dNode *tgt, MyAddr *data)
{
    dNode *newNode = nullptr;
    dNode *prevNode_ofTgt = nullptr;

    newNode = this->dList_makeNode(data);

    if ((this->listSize > 0 && tgt == nullptr) || newNode == nullptr || this->errCode != NORMAL)
        return 1;

    else
    {
        if (this->listSize == 0)
        {
            this->headNode = newNode;
            this->tailNode = newNode;
            newNode->nextNode = nullptr;
            newNode->prevNode = nullptr;
        }
        else
        {
            prevNode_ofTgt = tgt->prevNode;

            newNode->nextNode = tgt;
            newNode->prevNode = prevNode_ofTgt;
            

            if (tgt->prevNode == nullptr)
                this->headNode = newNode;

            else
                prevNode_ofTgt->nextNode = newNode;
            
            newNode->prevNode = prevNode_ofTgt;
        }

        this->listSize++;

        return 0;
    }
}

int dList::dList_remove(dNode* tgt, MyAddr** data) // 0 : normal, 1 : noElement
{
    dNode* temp = tgt;

    if (tgt == nullptr || this->listSize < 1) return 1;

    else
    {
        *data = tgt->data; // pop data

        if (tgt == this->headNode)
        {
            this->headNode = tgt->nextNode;

            if (this->headNode == nullptr) 
                this->tailNode = nullptr;
                // If listsize was 1, headptr = tailptr = null by deleting last node
            else
                tgt->nextNode->prevNode = nullptr;
                // General status of deleting headNode nextNode of target 's prevNode ptr is pointing null now
        }

        else
        {
            tgt->prevNode->nextNode = tgt->nextNode;

            if (tgt->nextNode == nullptr)
                this->tailNode = tgt->prevNode;
                // If target was tail node, tail ptr must update its obj
            else
                tgt->nextNode->prevNode = tgt->prevNode;
                // nextNode of target 's prevNode ptr is pointing prevNode of target now
        }

        this->dList_deleteNode(&temp);
        this->listSize--;

        return 0;
    }
}

void dList::dList_printAll()
{
    dNode* temp = this->headNode;

    while (temp != nullptr)
    {
        printData(temp->data);
        temp = temp->nextNode;
    }
}

int dList::dList_cmpData(const char* key1, const char* key2)
{
    return (!strcmp(key1, key2));
}

int dList::dList_getListSize()
{
    return this->listSize;
}

ErrCode dList::dList_getErrcode()
{
    return this->errCode;
}

/*----protected----*/

dNode *dList::dLiset_findNode_byID(const char *tgt_id)
{
    dNode *idxNode = this->headNode;
    dNode *result = nullptr;

    while (idxNode != nullptr)
    {
        if (!strcmp(idxNode->data->id, tgt_id))
        {
            result = idxNode ; 
            return result;
        }

        idxNode = idxNode->nextNode;
    }

    return result;
}

/*----private----*/

dNode *dList::dList_makeNode(MyAddr *data)
{
    dNode *newNode = new dNode;

    if (newNode == nullptr)
    {
        this->errCode = MEMORY_ERR;
        return nullptr;
    }
    else
    {
        newNode->data = data;
        return newNode;
    }
}

int dList::dList_deleteNode(dNode** tgt)  
{
    if (*tgt == nullptr)
        return 1;
    else
    {
        delete (*tgt);
        (*tgt) = nullptr;
        return 0;
    }
}
