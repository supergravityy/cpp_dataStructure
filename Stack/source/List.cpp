#include "../header/List.h"

/*----utils----*/

void printData(MyAddr* data) 
{
    cout << "ID : ";
    cout << data->id << endl;
    cout << "Name : ";
    cout << data->name << endl;
    cout << "PhoneNumber : ";
    cout << data->phone << endl;
}

/*----public----*/

List::List()
{
    this->listSize = 0;
    this->errCode = NORMAL;
    this->headNode = nullptr;
    this->tailNode = nullptr;
}

List::~List()
{
    Node* temp = this->headNode;
    MyAddr* temp2 = nullptr;

    while (temp != nullptr)
    {
        this->List_rem_next(temp,&temp2); 
        temp = temp->nextNode;
    }

    // Above logic will remove nextNode of headNode
    this->List_rem_next(temp,&temp2);


    this->listSize = 0;
    this->errCode = NORMAL;
    this->headNode = nullptr;
    this->tailNode = nullptr;
}

int List::List_ins_next(Node* tgt, MyAddr* data)
{
    Node* newNode = this->List_makeNode(data);
    
    if (newNode == nullptr) return 1;
    
    else
    {
        if(tgt == nullptr)
        {
            if(this->tailNode == nullptr && listSize == 0) // list is empty now
                this->tailNode = newNode;

            newNode->nextNode = headNode; 
            // if listSize = 0, it doesnt make a problem too. because headNode = nullptr
            this->headNode = newNode;
        }
        else
        {
            if(tgt->nextNode == nullptr) // insertion position is tail
                this->tailNode = newNode;

            newNode->nextNode = tgt->nextNode;
            tgt->nextNode = newNode;
        }
    }
    
    this->listSize++;
    return 0;
}

int List::List_rem_next(Node* tgt, MyAddr** data)
{
    Node* oldNode = nullptr;

    if(this->headNode == nullptr && this->tailNode == nullptr) return 1;

    //if(tgt->nextNode == nullptr) return 1; // if tgt is nullptr, nextnode of nullptr is invalid access!
        
    if(tgt == nullptr) // remove head
    {
        oldNode = this->headNode;
        *data = oldNode->data;

        if(this->headNode == this->tailNode) // list size is 1
            this->tailNode = nullptr;

        this->headNode = oldNode->nextNode;
        // if listSize = 1, it doesnt make a problem. because headNode's nextNode = null
    }
    else
    {
        oldNode = tgt->nextNode;
        *data = oldNode->data;

        if(oldNode->nextNode == this->tailNode) // remove tail
            this->tailNode = tgt;

        tgt->nextNode = oldNode->nextNode;
    }
    
    this->List_deleteNode(oldNode);
    this->listSize--;

    return 0;
}

int List::List_cmpData(const char* key1, const char* key2)
{
    return !strcmp(key1,key2);
}

void List::List_printAll()
{
    Node* temp = this->headNode;
    MyAddr* data = nullptr;

    while (temp != nullptr)
    {
        printData(data); 
        temp = temp->nextNode;
    }
}

int List::List_getListSize()
{
    return this->listSize;
}

ErrCode List::List_getErrcode()
{
    return this->errCode;
}

Node *List::List_findNode_byID(const char *tgt_id)
{
    Node *idxNode = this->headNode;
    Node *result = nullptr;

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

Node *List::List_makeNode(MyAddr *data)
{
    Node *newNode = new Node;

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

int List::List_deleteNode(Node* tgt)  
{
    if (tgt == nullptr)
        return 1;
    else
    {
        delete tgt;
        return 0;
    }
}