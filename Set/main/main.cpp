#include "../header/Set.h"

#define FOR_INSERT 1
#define FOR_REMOVE 2

void printMenu(int num)
{
    cout << "\n===== Set [" << num << "] Menu =====" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Remove" << endl;
    cout << "3. Get Set Size" << endl;
    cout << "4. Reset Set" << endl;
    cout << "5. Print All" << endl;
    cout << "6. Skip" << endl;
    cout << "0. Exit" << endl;
	cout << "==============================" << endl;
}

void printOperation()
{
    cout << "\n===== Set [result] Menu =====" << endl;
    cout << "1. Union" << endl;
    cout << "2. Intersection" << endl;
    cout << "3. Difference" << endl;
    cout << "4. Get Set Size" << endl;
    cout << "5. Reset Set" << endl;
    cout << "6. Print All" << endl;
    cout << "7. Skip" << endl;
    cout << "0. Exit" << endl;
    cout << "==============================" << endl;
}

void inputData(MyAddr& data, int num)
{
    if (num == FOR_INSERT)
    {
        cout << "Enter new node ID: ";
        cin >> data.id;
        cout << "Enter new node name: ";
        cin >> data.name;
        cout << "Enter new node phoneNumber: ";
        cin >> data.phone;
    }
    else if (num == FOR_REMOVE)
    {
        cout << "Enter node ID: ";
        cin >> data.id;
        cout << "Enter node name: ";
        cin >> data.name;
        cout << "Enter node phoneNumber: ";
        cin >> data.phone;
    }
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

int choice_mySet_menu(Set &mySet, int num)
{
    int choice;
    int makeResult;
    MyAddr *newData = nullptr;
    MyAddr *removedData = nullptr;

    if (mySet.Set_getErrCode() != NORMAL)
        return 1;

    while (true)
    {
        printMenu(num);
        cin >> choice;

        switch (choice)
        {
        case 1:
            makeResult = makeData(&newData);
            if (makeResult)
                break;

            inputData(*newData,FOR_INSERT);

            if (mySet.Set_insert(newData) == 0)
                cout << "Insert successfully!" << endl;
            else
                cout << "Failed to Insert!" << endl;
            break;

        case 2:
			makeData(&removedData);
			inputData(*removedData,FOR_REMOVE);

            if (mySet.Set_remove(&removedData) != 0)
            {
				cout << "Failed to Remove!" << endl;
			}
            else
            {
                cout << "Remove successfully!" << endl;
                printData(*removedData);
            }
            break;

        case 3:
            cout << "Current Set size: " << mySet.Set_getSetSize() << endl;
            break;

        case 4:
            mySet.Set_init();
            cout << "Set has been reset!" << endl;
            break;

        case 5:
            mySet.Set_printAll();
            break;

        case 6:
            return 0;
            break;

        case 0:
            return 1;

        default:
            break;
        }
    }

    return 0;
}

int choice_resultSet_menu(Set &resultSet, Set &set1, Set &set2)
{
    int choice, result = 0;

    if (resultSet.Set_getErrCode() != NORMAL)
        return 1;

    printOperation();
    cin >> choice;

    switch (choice)
    {
    case 1:
        if (resultSet.Set_union(&set1, &set2) != OPERATION_CMPLT)
        {
            cout << "Union operation Failed!" << endl;
            result = 1;
        }
        else
        {
			cout << "Union operation Success!" << endl;
			resultSet.Set_printAll();
        }
        break;
    case 2:
        if (resultSet.Set_intersection(&set1, &set2) != OPERATION_CMPLT)
        {
            cout << "Intersection operation Failed!" << endl;
            result = 1;
        }
        else
        {
			cout << "Intersection operation Success!" << endl;
			resultSet.Set_printAll();
        }
        break;
    case 3:
        if (resultSet.Set_difference(&set1, &set2) != OPERATION_CMPLT)
        {
            cout << "S1 - S2 operation Failed!" << endl;
            result = 1;
		}
        else
        {
			cout << "S1 - S2 operation Success!" << endl;
			resultSet.Set_printAll();
        }
        break;
    case 4:
        cout << "Current Set size: " << resultSet.Set_getSetSize() << endl;
        break;
    case 5:
        resultSet.Set_init();
        cout << "Set has been reset!" << endl;
        break;
    case 6:
        resultSet.Set_printAll();
        break;
    case 7:
        // do nothing
        break;
    case 0:
        return 1;
    default:
        break;
    }

    return result;
}

int main()
{
    Set mySet1, mySet2, resultSet;

    while (true)
    {
        if (choice_mySet_menu(mySet1, 1))
            break;

        if (choice_mySet_menu(mySet2, 2))
            break;

        if (choice_resultSet_menu(resultSet, mySet1, mySet2))
            break;
    }

    return 0;
}
