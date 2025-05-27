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
    cout << "Enter new node phoneNumber: ";
    cin >> data.phone;
}

void printData(MyAddr &data)
{
    cout << "ID : " << data.id << endl;
    cout << "Name : " << data.name << endl;
    cout << "Age : " << data.age << endl;
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

namespace compareFunc
{
    bool Ascending_Order_Func(int num1, int num2)
    {
        return num1 > num2;
    }

    bool Descending_Order_Func(int num1, int num2)
    {
        return num1 < num2;
    }

}

int main()
{
    Heap myHeap(compareFunc::Ascending_Order_Func);
    int choice = 0;
    int makeResult = 0;
    MyAddr *newData = nullptr;
    MyAddr *removedData = nullptr;

    while (myHeap.Heap_getErrCode() == NORMAL)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: // Insert

            break;

        case 2: // Extract

            break;

        case 3: // Reset

            break;

        case 4: // PrintAll

            break;

        case 0:
            return 0;

        default:
            break;
        }
    }

    return 0;
}