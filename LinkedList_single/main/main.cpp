#include "../header/List.h"

void printMenu()
{
    cout << "\n====== Linked List Menu ======" << endl;
    cout << "1. Insert Node" << endl;
    cout << "2. Remove Node" << endl;
    cout << "3. Modify Node Data" << endl;
    cout << "4. Print All Nodes" << endl;
    cout << "5. Find Node by ID" << endl;
    cout << "6. Find Node by Name" << endl;
    cout << "7. Find Node by Phone Number" << endl;
    cout << "8. Clean List" << endl;
    cout << "0. Exit Program" << endl;
    cout << "================================" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    List myList;
    int choice;
    MyAddr tempData;
    char searchID[ID_MAX];
    char searchName[NAME_MAX];
    char searchPhone[PHONE_MAX];

    while (true)
    {
        printMenu();
        cin >> choice;

        // 잘못된 입력 방지
        if (cin.fail())
        {
            cin.clear(); // 오류 플래그 초기화
            cin.ignore(100, '\n'); // 입력 버퍼 비우기
            cout << "Invalid input. Please enter a number between 0 and 7.\n";
            continue;
        }

        switch (choice)
        {
        case 1: // Insert Node

            if (myList.List_insertNext())
                cout << "Node inserted successfully!" << endl;
            else
                cout << "Failed to insert node." << endl;
            break;

        case 2: // Remove Node
            if (myList.List_removeNext())
                cout << "Node removed successfully!" << endl;
            else
                cout << "Failed to remove node. ID not found." << endl;
            break;

        case 3: // Modify Node
            cout << "Enter ID to modify: ";
            cin.ignore();
            cin.getline(tempData.id, ID_MAX);
            cout << "Enter new Name: ";
            cin.getline(tempData.name, NAME_MAX);
            cout << "Enter new Phone Number: ";
            cin.getline(tempData.phone, PHONE_MAX);

            if (myList.List_modifyData(&tempData))
                cout << "Node modified successfully!" << endl;
            else
                cout << "Failed to modify node. ID not found." << endl;
            break;

        case 4: // Print All Nodes
            myList.List_printAll();
            break;

        case 5: // Find by ID
            cout << "Enter ID to search: ";
            cin.ignore();
            cin.getline(searchID, ID_MAX);
            if (!myList.List_findData_byID(searchID))
                cout << "No node found with given ID." << endl;
            break;

        case 6: // Find by Name
            cout << "Enter Name to search: ";
            cin.ignore();
            cin.getline(searchName, NAME_MAX);
            if (!myList.List_findData_byName(searchName))
                cout << "No node found with given Name." << endl;
            break;

        case 7: // Find by Phone Number
            cout << "Enter Phone Number to search: ";
            cin.ignore();
            cin.getline(searchPhone, PHONE_MAX);
            if (!myList.List_findData_byPhone(searchPhone))
                cout << "No node found with given Phone Number." << endl;
            break;

        case 8: // Clean List 
            cout << "Removing List..." << endl;
            myList.List_init();
            break;

        case 0: // Exit
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please enter a number between 0 and 7.\n";
            break;
        }
    }
    return 0;
}