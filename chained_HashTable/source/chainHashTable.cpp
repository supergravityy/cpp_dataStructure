#include "../header/chainHashTable.h"
#include "../header/List.h"

HashTable::HashTable()
{
    this->table = nullptr;
    this->NodeSize = 0;
    this->tableSize = 0;
}
HashTable::~HashTable()
{
    HashTable_destroy();
}

/* Management */

bool HashTable::HashTable_init(int Size)
{
    if(this->HashingFunc_setTableSize(Size) == false) 
        return false;

    else
    {
        this->tableSize = Size;

        this->table = new List[this->tableSize];
        if(this->table == nullptr)
        {
            this->errCode = MEMORY_ERR;
            return false;
        }  

        for (int i = 0; i < this->tableSize; i++)
        {
            this->table[i].List_init();
        }
    }

    this->HashTable_updatdErrCode();
    return true;
}

void HashTable::HashTable_destroy()
{
    for (int i = 0; i < this->tableSize; i++)
    {
        this->table[i].List_init();
    }

    delete[] this->table;
    this->table = nullptr;
}

int HashTable::HashTable_insert(MyAddr* data) // 0: success, 1: prevent duplication, 2: list insertion failed
{
    void *temp = nullptr;

    int bucket = this->HashingFunc_String(data->id);
    int retVal = 0;

    if(this->HashTable_lookup(&data) == true) 
        return 1; // prevent duplication
    else
    {
        retVal = this->table[bucket].List_ins_next(nullptr,data);

        if(retVal != 0) 
        {
            this->HashTable_updatdErrCode();
            return 2; // list insertion failed
        }   
        else 
        {
            this->NodeSize++;
            this->HashTable_updatdErrCode();
            return 0; // success
        }
    }
}

int HashTable::HashTable_remove(MyAddr** data) // 0: success, 1: list removal failed, 2: data not found
{
    Node* temp = nullptr;
    Node* prev = nullptr;

    int bucket = this->HashingFunc_String((*data)->id);
    temp = this->table[bucket].headNode;

    for (; temp != nullptr; temp = temp->nextNode)
    {
        if(this->HashTable_cmpData(temp->data->id, (*data)->id) == true)
        {
            if(this->table[bucket].List_rem_next(prev, data) == 0) 
            {
                this->NodeSize--;

                this->HashTable_updatdErrCode();
                return 0; // success
            }
            else
            {
                this->HashTable_updatdErrCode();
                return 1; // list removal failed
            }
        }

        prev = temp;
    }

    this->HashTable_updatdErrCode();
    return 2; // data not found
}

bool HashTable::HashTable_lookup(MyAddr** data)
{
    Node* temp = nullptr;
    int bucket = this->HashingFunc_String((*data)->id);

    temp = this->table[bucket].headNode;
    for(;temp != nullptr; temp = temp->nextNode)
    {
        if(this->HashTable_cmpData(temp->data->id, (*data)->id))
        {
            *data = temp->data;
            this->HashTable_updatdErrCode();
            return true;
        }
    }
    
    this->HashTable_updatdErrCode();
    return false;
}

/* Utility */

void HashTable::HashTable_printAll()
{
    for(int i = 0; i < this->tableSize; i++)
    {
        printf("[%d] Bucket's contents\n",i);

        this->table[i].List_printAll();
    }
}

int HashTable::HashTable_getNodeSize()
{
    return this->NodeSize;
}

ErrCode HashTable::HashTable_getErrCode()
{
    return this->errCode;
}

bool HashTable::HashTable_cmpData(const char* key1, const char* key2)
{
    return !(strcmp(key1,key2));
}

void HashTable::HashTable_updatdErrCode()
{
    for(int i = 0; i < this->tableSize; i++)
    {
        this->errCode = this->table[i].List_getErrcode();
    }
}