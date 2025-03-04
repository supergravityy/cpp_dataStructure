#include "../header/List.h"

// todo : cin >> str 대신 cin.getline(str,len) 을 사용할것

/*----utils----*/

void print_allData(const MyAddr *data)
{
    printf("Id : %s\n", data->id);
    printf("Name : %s\n", data->name);
    printf("Number : %s\n\n", data->phone);
}

/*----public----*/

List::List()
{
    // List initialize

    this->listSize = 0;
    this->headNode = nullptr;
    this->tailNode = nullptr;
}

List::~List()
{
    this->List_init();
}

int List::List_getSize()
{
    return this->listSize;
}

bool List::List_findData_byID(const char *tgt_id)
{
    bool result = false;
    Node *inst = this->List_getHeadAddr();
    int idxNum = 0;

    while (inst != NULL)
    {
        if (!strcmp(inst->data->id, tgt_id))
        {
            print_allData(inst->data);
            result = true;

            break; // id is always unique
        }
        else
        {
            idxNum++;
            inst = inst->nextNode;
        }
    }

    return result;
}
bool List::List_findData_byName(const char *tgt_name)
{
    bool result = false;
    Node *inst = this->List_getHeadAddr();
    int idxNum = 0;

    while (inst != NULL)
    {
        if (!strcmp(inst->data->name, tgt_name))
        {
            printf("found in %d index!\n\n", idxNum);
            print_allData(inst->data);
            result = true;
            // name is never always unique!
        }

        idxNum++;
        inst = inst->nextNode;
    }

    return result;
}
bool List::List_findData_byPhone(const char *tgt_phone)
{
    bool result = false;
    Node *inst = this->List_getHeadAddr();
    int idxNum = 0;

    while (inst != NULL)
    {
        if (!strcmp(inst->data->phone, tgt_phone))
        {
            printf("found in %d index!\n\n", idxNum);
            print_allData(inst->data);
            result = true;

            break; // phoneNumber is always unique
        }
        else
        {
            idxNum++;
            inst = inst->nextNode;
        }
    }

    return result;
}

bool List::List_insertNext()
{
    bool result = false;
    char tgtID[ID_MAX] = {0};
    Node *newNode = nullptr;
    Node *tempNode = nullptr;
    Node *tgtNode = nullptr;

    if (this->listSize == 0)
    // nodeList is empty!
    {
        newNode = List_makeNode();

        if (newNode == nullptr)
            return result;

        this->List_setHeadAddr(newNode);
        this->List_setTailAddr(newNode);

        this->listSize++;
        result = true;
        return result;
    }
    else
    {
        cout << "Enter the id of the target you want to add immediately afterwards " << endl;
        cout << "If you want to be at the front, enter NULL : ";
        cin >> tgtID;
        cout << endl;

        if ((!strcmp(tgtID, "NULL")) || (!strcmp(tgtID, "null")))
        // user wants to put data in the head
        {
            newNode = this->List_makeNode();
            if (newNode == nullptr)
                return result;

            tempNode = this->List_getHeadAddr();
            this->List_setHeadAddr(newNode);
            newNode->nextNode = tempNode;

            this->listSize++;
            result = true;
            return result;
        }
        else
        {
            tgtNode = this->List_findNode_byID(tgtID);
            if (tgtNode == nullptr)
            {
                printf("Target id not found...\n");
                return result;
            }
            else
            {

                newNode = this->List_makeNode();
                if (newNode == nullptr)
                    return result;

                if (tgtNode == this->List_getTailAddr())
                // put data in the tail
                {
                    tgtNode->nextNode = newNode;
                    List_setTailAddr(newNode);

                    this->listSize++;
                    result = true;
                }
                else
                // put data in the middle
                {
                    tempNode = tgtNode->nextNode;
                    newNode->nextNode = tempNode;
                    tgtNode->nextNode = newNode;

                    this->listSize++;
                    result = true;
                }
            }
        }
    }

    return result;
}
bool List::List_removeNext()
{
    bool result = false;
    char tgtID[ID_MAX] = {0};
    Node *oldNode = nullptr;
    Node *tgtNode = nullptr;

    if (this->listSize == 0)
    {
        printf("The list is empty. There are no items to remove..\n");
        result = false;
        return result;
    }
    else
    {
        cout << "Enter the ID of the target you want to remove.." << endl;
        cout << "If you want to be at the head, enter NULL : ";
        cin >> tgtID;
        cout << endl;

        if ((!strcmp(tgtID, "NULL")) || (!strcmp(tgtID, "null")))
        // user wants to remove data in the head
        {
            oldNode = this->List_getHeadAddr();

            if (!oldNode)
            {
                printf("Target ID not found in the list.\n");
                result = false;
            }

            if (this->listSize == 1) // list just has a single node!
            {
                this->List_setHeadAddr(nullptr);
                this->List_setTailAddr(nullptr);
            }

            else
                this->List_setHeadAddr(oldNode->nextNode);

            delete oldNode->data;
            delete oldNode;

            this->listSize--;
            result = true;
        }
        else
        // remove intermediate or last node
        {
            tgtNode = this->List_findNode_byID(tgtID);

            if (!tgtNode)
            {
                printf("Target ID not found in the list.\n");
                result = true;
            }
            else if (tgtNode->nextNode == nullptr)
            // Even if the number of lists is one, the request is rejected because the head is not selected
            {
                printf("To remove the tail of the list, you must select the previous list..\n");
                result = false;
            }
            else
            {
                oldNode = tgtNode->nextNode;
                tgtNode->nextNode = oldNode->nextNode;

                if (oldNode->nextNode == nullptr) // remove tail Node
                    this->List_setTailAddr(tgtNode);

                delete oldNode->data;
                delete oldNode;

                this->listSize--;
                result = true;
            }
        }

        return result;
    }
}

void List::List_printAll()
{
    Node *tempNode = this->List_getHeadAddr();

    while (tempNode != nullptr)
    {
        print_allData(tempNode->data);
        tempNode = tempNode->nextNode;
    }
}

// retVal : false (not found), true (found)
bool List::List_modifyData(const MyAddr *data)
{
    bool result = false;
    Node *tgtNode = nullptr;
    Node *newNode = nullptr;

    tgtNode = this->List_findNode_byID(data->id);

    if (!tgtNode)
    {
        cout << "invalid ID! try again!" << endl;
        return result;
    }
    else
    {
        newNode = this->List_makeNode(); // for reuse

        if (!newNode)
            return result;

        memcpy(tgtNode->data->id, newNode->data->id, ID_MAX);
        memcpy(tgtNode->data->name, newNode->data->name, NAME_MAX);
        memcpy(tgtNode->data->phone, newNode->data->phone, PHONE_MAX);

        delete newNode->data;
        delete newNode;
    }

    return result;
}

/*----private----*/

// retVal : NULL(not found), else(found)
Node *List::List_findNode_byID(const char *tgt_id)
{
    Node *inst = this->List_getHeadAddr();

    while (inst != NULL)
    {
        if (!strcmp(inst->data->id, tgt_id))
            break;
        else
            inst = inst->nextNode;
    }

    return inst;
}

Node *List::List_makeNode()
{
    char tempID[ID_MAX];
    char tempNAME[NAME_MAX];
    char tempPHONE[PHONE_MAX];

    cout << "Please enter the id : ";
    cin >> tempID;
    cout << endl
         << "Please enter the name : ";
    cin >> tempNAME;
    cout << endl
         << "Please enter the phone number : ";
    cin >> tempPHONE;

    Node *newNode = new Node;
    MyAddr *newData = new MyAddr;

    if (newNode == nullptr || newData == nullptr)
    {
        this->errCode = MEMORY_ERR;
        printf("An error occurred during memory allocation\n");
        return nullptr;
    }
    else
    {
        newNode->nextNode = nullptr;
        newNode->data = newData;

        memcpy(newNode->data->id, tempID, ID_MAX);
        memcpy(newNode->data->name, tempNAME, NAME_MAX);
        memcpy(newNode->data->phone, tempPHONE, PHONE_MAX);
    }

    return newNode;
}

Node *List::List_getHeadAddr()
{
    return this->headNode;
}
Node *List::List_getTailAddr()
{
    return this->tailNode;
}
void List::List_setHeadAddr(Node *tgt)
{
    this->headNode = tgt;
}
void List::List_setTailAddr(Node *tgt)
{
    this->tailNode = tgt;
}
void List::List_init()
{
    Node *tgt_nextNode = nullptr;
    Node *tgtNode = this->List_getHeadAddr();

    while (this->listSize > 0)
    {
        tgt_nextNode = tgtNode->nextNode;

        delete tgtNode->data;
        delete tgtNode;
        tgtNode = tgt_nextNode;

        this->listSize--;
    }

    this->List_setHeadAddr(nullptr);
    this->List_setTailAddr(nullptr);
}