#include "../header/Heap.h"

void printMenu()
{
    cout << "\n===== Stack Menu =====" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Extract" << endl;
    cout << "3. Reset" << endl;
    cout << "4. PrintAll" << endl;
    cout << "0. Exit program" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
}

void inputData(MyAddr &data)
{
    cout << "Enter new node ID: ";
    cin >> data.id;
    cout << "Enter new node name: ";
    cin >> data.name;
    cout << "Enter new node age :";
    cin >> data.age;
}

void printData(MyAddr &data)
{
    //cout << "ID : " << data.id << endl;
    //cout << "Name : " << data.name << endl;
    cout << "Age : " << data.age << endl;
}

bool makeData(MyAddr **newData)
{
    *newData = new MyAddr();

    if (*newData == nullptr)
    {
        cout << "Memory allocation Err!" << endl;
        return true;
    }

    else
        return false;
}

namespace compareFunc
{
    bool Descending_Order_Func(int parentNode, int childNode)
    {
        return parentNode > childNode;
    }

    bool Ascending_Order_Func(int parentNode, int childNode)
    {
        return parentNode < childNode;
    }
}

int main()
{
    Heap myHeap(compareFunc::Ascending_Order_Func);
    int choice = 0;
    bool makeResult = 0;
    MyAddr *newData = nullptr;
    MyAddr *removedData = nullptr;

    while (myHeap.Heap_getErrCode() == NORMAL)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: // Insert
            makeResult = makeData(&newData);
            if (makeResult)
                break;
            else
            {
                inputData(*newData);

                if(myHeap.Heap_insert(newData) == true)
                {
                    cout << "Node inserted successfully!" << endl;
                }
                else
                {
                    cout << "Failed to insert node!" << endl;
                }
            }
            break;

        case 2: // Extract
            if(myHeap.Heap_extract(&removedData) == true)
            {
                printData(*removedData);
            }
            else
            {
                cout << "Failed to extract!" << endl;
            }
            break;

        case 3: // Reset
            myHeap.Heap_init(compareFunc::Ascending_Order_Func);
            cout << "Heap has been reset!" << endl;
            break;

        case 4: // PrintAll
            cout << "Heap size : " << myHeap.Heap_getSize() << endl;
            myHeap.Heap_printAll();
            break;

        case 0:
            return 0;

        default:
            break;
        }
    }

    return 0;
}