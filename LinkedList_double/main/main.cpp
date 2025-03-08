#include <iostream>
#include <string>
#include "../header/dList.h"

void printMenu()
{
    cout << "\n===== Double Linked List Menu =====" << endl;
    cout << "1. Insert node after (next)" << endl;
    cout << "2. Insert node before (prev)" << endl;
    cout << "3. Remove node" << endl;
    cout << "4. Get list size" << endl;
    cout << "5. Reset (Destroy) list" << endl;
    cout << "6. print list Contents" << endl;
    cout << "0. Exit program" << endl;
    cout << "===================================" << endl;
    cout << "Enter your choice: ";
}

void inputData(MyAddr& data)
{
    cout << "Enter new node ID: ";
    cin >> data.id;
    cout << "Enter new node name: ";
    cin >> data.name;
    cout << "Enter new node phoneNumber: ";
    cin >> data.phone;
}

int makeData(MyAddr **newData)
{
    *newData = new MyAddr();

    if(*newData == nullptr) 
    {
        cout << "Memory allocation Err!" <<endl;
        return 1;
    }
        
    else 
        return 0;
}

int main()
{
    dList myList;  // 리스트 객체 생성
    int choice;
    int makeResult = 0;
    string inputID;
    MyAddr *newData;
    dNode *targetNode;
    MyAddr *removedData;

    while (myList.dList_getErrcode() == NORMAL)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
            case 1: // Insert next
                cout << "Enter target node ID (or 'null' for first node): ";
                cin >> inputID;

                makeResult = makeData(&newData);
                if(makeResult) break;
                inputData(*newData);

                if (inputID == "null" || inputID == "NULL")
                    targetNode = nullptr;
                else
                    targetNode = myList.dLiset_findNode_byID(inputID.c_str());

                if (myList.dList_ins_next(targetNode, newData) == 0)
                    cout << "Node inserted successfully!" << endl;
                else
                    cout << "Failed to insert node!" << endl;
                break;

            case 2: // Insert prev
                cout << "Enter target node ID: ";
                cin >> inputID;

                makeResult = makeData(&newData);
                if(makeResult) break;

                inputData(*newData);

                targetNode = myList.dLiset_findNode_byID(inputID.c_str());

                if (myList.dList_ins_prev(targetNode, newData) == 0)
                    cout << "Node inserted successfully!" << endl;
                else
                    cout << "Failed to insert node!" << endl;
                break;

            case 3: // Remove node
                cout << "Enter node ID to remove: ";
                cin >> inputID;

                targetNode = myList.dLiset_findNode_byID(inputID.c_str());

                if (myList.dList_remove(targetNode, &removedData) == 0)
                {
                    cout << "Node '" << removedData->id << "' removed successfully!" << endl;
                    delete removedData;
                }
                else
                {
                    cout << "Failed to remove node!" << endl;
                }
                break;

            case 4: // Get list size
                cout << "Current list size: " << myList.dList_getListSize() << endl;
                break;

            case 5: // Destroy list
                myList.dList_init();
                cout << "List has been reset!" << endl;
                break;

            case 6: // print list
                myList.dList_printAll();
                break;

            case 0: // Exit
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    }

    return 0;
}
