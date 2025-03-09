#include "../header/rList.h"

/*----utils----*/

void printData(MyAddr *data)
{
    cout << "ID : ";
    cout << data->id << endl;
    cout << "Name : ";
    cout << data->name << endl;
    cout << "PhoneNumber : ";
    cout << data->phone << endl;
}

/*----public----*/

rList::rList()
{
    this->headNode = nullptr;
    this->listSize = 0;
    this->errCode = NORMAL;
}

rList::~rList()
{
    this->rList_init();
}

void rList::rList_init()
{
    rNode *tgtNode = this->headNode;
    MyAddr *tempData = nullptr;

    while (listSize > 0)
    {
        this->rList_rem_next(tgtNode, &tempData);

        tgtNode = tgtNode->nextNode;
    }

    this->headNode = nullptr;
    this->listSize = 0;
}

int rList::rList_ins_next(rNode *tgt, MyAddr *data)
{
    rNode *newNode = nullptr;
    rNode *tempNode = nullptr;

    if((listSize > 0 && tgt == nullptr) || data == nullptr) 
        return 1;


    newNode = this->rList_makeNode(data);
    
    if(newNode == nullptr) 
    {
        this->errCode = MEMORY_ERR;
        return 1;
    }
    else
    {
        newNode->data = data;

        if(this->listSize == 0)
        {
            newNode->nextNode = newNode;    // for Ring shape
            this->headNode = newNode;       // no tail ptr
        }
        else
        {
            tempNode = tgt->nextNode;
            tgt->nextNode = newNode;
            newNode->nextNode = tempNode;
            // Target 's nextNode is tail (its nextNode point head of list)
            // However, this logic naturally includes this concept
        }

        this->listSize++;
        return 0;
    }
}

int rList::rList_rem_next(rNode *tgt, MyAddr **data)
{
    rNode* oldNode = nullptr;

    if(tgt == nullptr ) return 1;

    if(this->listSize < 1) return 1;
    
    else
    {
        *data = tgt->nextNode->data;
        oldNode = tgt->nextNode;

        if(tgt->nextNode == tgt) // If the next node points to itself, the size = 1
        {
            this->headNode = nullptr;
        }
        else
        {
            tgt->nextNode = oldNode->nextNode;

            if (oldNode == this->headNode) // Target 's nextNode is tail(its nextNode point head of list)
            {
                this->headNode = oldNode->nextNode;
            }
        }
    }

    this->rList_deleteNode(&oldNode);
    this->listSize--;

    return 0;
}

int rList::rList_cmpData(const char *key1, const char *key2)
{
    return !(strcmp(key1,key2));
}

void rList::rList_printAll()
{
    rNode* temp = this->headNode;
    if(this->listSize < 1) return;

    do // Just do it first
    {
        printData(temp->data);
        temp = temp->nextNode;
    } while (temp != this->headNode); 
    // It's a ring list, so it can't go back to head ptr
    
    return;
}

int rList::rList_getListSize()
{
    return this->listSize;
}

ErrCode rList::rList_getErrcode()
{
    return this->errCode;
}

rNode *rList::rList_findNode_byID(const char *tgt_id)
{
    rNode *idxNode = this->headNode;
    rNode *result = nullptr;

    if(this->listSize < 1) return nullptr;

    do // Just do it first
    {
        if (!strcmp(idxNode->data->id, tgt_id))
        {
            result = idxNode ; 
            return result;
        }
        else
            idxNode = idxNode->nextNode;

    } while (idxNode != this->headNode); 

    return result;
}

/*----private----*/

rNode *rList::rList_makeNode(MyAddr *data)
{
    rNode *newNode = new rNode;

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

int rList::rList_deleteNode(rNode **tgt)
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