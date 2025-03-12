#include "../header/Stack.h"

void printMenu()
{
    cout << "\n===== Stack Menu =====" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Peek" << endl;
    cout << "4. Get Stack size" << endl;
    cout << "5. Reset (Destroy) Stack" << endl;
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
    Stack myStack;
    int choice;
    int makeResult = 0;
    MyAddr *newData;
    MyAddr *removedData;
    // chatGPT write here 1

    while (myStack.Stack_getErrCode() == NORMAL)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            makeResult = makeData(&newData);
            if (makeResult)
                break;
            inputData(*newData);

            if (myStack.Stack_push(newData) == 0)
                cout << "Node inserted successfully!" << endl;
            else
                cout << "Failed to insert node!" << endl;
            break;

        case 2:
            if (myStack.Stack_pop(&removedData) == 0)
            {
                printData(*removedData);
            }
            else
            {
                cout << "Failed to pop!" << endl;
            }
            break;

        case 3:
            if (myStack.Stack_peek(removedData) == 0)
            {
                printData(*removedData);
            }
            else
            {
                cout << "Failed to peek!" << endl;
            }
            break;

        case 4:
            cout << "Current Stack size: " << myStack.Stack_getStackSize() << endl;
            break;

        case 5:
            myStack.Stack_init();
            cout << "Stack has been reset!" << endl;
            break;
            
        case 0:
            return 0;

        default:
            break;
        }
        // chatGPT write here 2
    }

    return 0;
}