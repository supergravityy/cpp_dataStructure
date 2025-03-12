#include "../header/Queue.h"

void printMenu()
{
    cout << "\n===== Queue Menu =====" << endl;
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Peek" << endl;
    cout << "4. Get Queue size" << endl;
    cout << "5. Reset (Destroy) Queue" << endl;
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
    Queue myQueue;
    int choice;
    int makeResult = 0;
    MyAddr *newData = nullptr;
    MyAddr *removedData = nullptr;

    while (myQueue.Queue_getErrCode() == NORMAL)
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

            if (myQueue.Queue_enqueue(newData) == 0)
                cout << "Enqueue successfully!" << endl;
            else
                cout << "Failed to Enqueue!" << endl;
            break;

        case 2:
            if (myQueue.Queue_dequeue(&removedData) == 0)
            {
                printData(*removedData);
            }
            else
            {
                cout << "Failed to dequeue!" << endl;
            }
            break;

        case 3:
            if (myQueue.Queue_peek(removedData) == 0)
            {
                printData(*removedData);
            }
            else
            {
                cout << "Failed to peek!" << endl;
            }
            break;

        case 4:
            cout << "Current Stack size: " << myQueue.Queue_getQueueSize() << endl;
            break;

        case 5:
            myQueue.Queue_init();
            cout << "Stack has been reset!" << endl;
            break;
            
        case 0:
            return 0;

        default:
            break;
        }
    }

    return 0;
}