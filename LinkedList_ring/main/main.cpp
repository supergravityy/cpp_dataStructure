#include <iostream>
#include <string>
#include "../header/rList.h"

void printMenu()
{
    cout << "\n===== Ring Linked List Menu =====" << endl;
    cout << "1. Insert node after (next)" << endl;
    cout << "2. Remove next node" << endl;
    cout << "3. Get list size" << endl;
    cout << "4. Reset (Destroy) list" << endl;
    cout << "5. print list Contents" << endl;
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
    rList myList; 
    int choice;
    int makeResult = 0;
    string inputID;
    MyAddr *newData;
    rNode *targetNode;
    MyAddr *removedData;

    while (myList.rList_getErrcode() == NORMAL)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
            case 1: // Insert next
                cout << "Enter target node ID (or 'null' for first node): ";
                cin >> inputID;

                makeResult = makeData(&newData);
                if (makeResult) break;
                inputData(*newData);

                if (inputID == "null" || inputID == "NULL")
                    targetNode = myList.rList_getListSize() == 0 ? nullptr : myList.rList_findNode_byID(inputID.c_str());
                else
                    targetNode = myList.rList_findNode_byID(inputID.c_str());

                if (myList.rList_ins_next(targetNode, newData) == 0)
                    cout << "Node inserted successfully!" << endl;
                else
                    cout << "Failed to insert node!" << endl;
                break;

            case 2: // Remove next node
                cout << "Enter target node ID: ";
                cin >> inputID;

                targetNode = myList.rList_findNode_byID(inputID.c_str());

                if (myList.rList_rem_next(targetNode, &removedData) == 0)
                {
                    cout << "Node '" << removedData->id << "' removed successfully!" << endl;
                    delete removedData;
                }
                else
                {
                    cout << "Failed to remove node!" << endl;
                }
                break;

            case 3: // Get list size
                cout << "Current list size: " << myList.rList_getListSize() << endl;
                break;

            case 4: // Destroy list
                myList.rList_init();
                cout << "List has been reset!" << endl;
                break;

            case 5: // Print list contents
                myList.rList_printAll();
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