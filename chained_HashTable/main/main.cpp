#include "../header/chainHashTable.h"

void printMenu()
{
    cout << "\n===== HashTable Menu =====" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Remove" << endl;
    cout << "3. Destroy" << endl;
    cout << "4. Lookup" << endl;
    cout << "5. Print All" << endl;
    cout << "6. Print Size" << endl;
    cout << "0. Exit" << endl;
    cout << "==============================" << endl;
}

void inputData(MyAddr &data)
{

    cout << "Enter new node ID: ";
    cin >> data.id;
    cout << "Enter new node name: ";
    cin >> data.name;
    cout << "Enter new node phoneNumber: ";
    cin >> data.phone;
}

void printData(MyAddr &data)
{
    cout << "ID : " << data.id << endl;
    cout << "Name : " << data.name << endl;
    cout << "PhoneNumber : " << data.phone << endl;
}

int makeData(MyAddr **newData)
{
    *newData = new MyAddr();

    if (*newData == nullptr)
    {
        cout << "Memory allocation Err!" << endl;
        return 1;
    }

    else
        return 0;
}

int main()
{
    HashTable myHashTable;
    int choice, key;
    MyAddr *newData = nullptr;
    MyAddr *removedData = nullptr;

    cout << "Enter the table size: ";
    cin >> choice;

    if (myHashTable.HashTable_init(choice) == false)
        cout << "The table size is not a prime number." << endl;
    else
        cout << "Table has been initialized." << endl;

    while (myHashTable.HashTable_getErrCode() == NORMAL)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            makeData(&newData);
            inputData(*newData);

            if (myHashTable.HashTable_insert(newData) == 0)
                cout << "Insert successfully!" << endl;
            else
                cout << "Failed to Insert!" << endl;
        break;

        case 2:
            delete removedData;
            makeData(&removedData);
            inputData(*removedData);

            if (myHashTable.HashTable_remove(&removedData) == 0)
            {
                cout << "Remove successfully!" << endl;
                printData(*removedData);
            }
            else
                cout << "Failed to Remove!" << endl;
            break;
        
        case 3:
            myHashTable.HashTable_destroy();
            cout << "Table has been destroyed." << endl;
            break;

        case 4:
            if (myHashTable.HashTable_lookup(&newData) == true)
            {
                cout << "Data found!" << endl;
                printData(*newData);
            }
            else
                cout << "Data not found!" << endl;
            break;
        
        case 5:
            myHashTable.HashTable_printAll();
            break;

        case 6:
            cout << "Current total size: " << myHashTable.HashTable_getNodeSize() << endl;
            break;
        
        case 0:
            return 0;
            break;

        default:
            cout << "Invalid input!" << endl;
            break;
        }
    }
    
    return 0;
}