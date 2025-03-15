#include "../header/Set.h"

void printMenu(int num)
{
    cout << "\n===== Set [" << num << "] Menu =====" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Remove" << endl;
    cout << "3. Get Set Size" << endl;
    cout << "4. Reset Set" << endl;
    cout << "0. Exit" << endl;
}

void printOperation()
{
    cout << "\n===== Set [" << 1 << "] Menu =====" << endl;
    cout << "1. Union" << endl;
    cout << "2. Intersection" << endl;
    cout << "3. Difference" << endl;
    cout << "4. Get Set Size" << endl;
    cout << "5. Reset Set" << endl;
    cout << "6. Skip" << endl;
    cout << "0. Exit" << endl;
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

int checkSet_stat(Set &set1, Set &set2)
{
    if (set1.Set_getErrCode() == NORMAL && set2.Set_getErrCode() == NORMAL)
        return 1;
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

    printMenu(num);
    cin >> choice;

    switch (choice)
    {
    case 1:
        makeResult = makeData(&newData);
        if (makeResult)
            break;

        inputData(*newData);

        if (mySet.Set_insert(newData) == 0)
            cout << "Insert successfully!" << endl;
        else
            cout << "Failed to Insert!" << endl;
        break;

    case 2:
        if (mySet.Set_remove(&removedData) == 0)
            printData(*removedData);
        else
            cout << "Failed to removed!" << endl;
        break;

    case 3:
        cout << "Current Set size: " << mySet.Set_getSetSize() << endl;
        break;

    case 4:
        mySet.Set_init();
        cout << "Set has been reset!" << endl;
        break;

    case 0:
        return 1;

    default:
        break;
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

    // cout << "1. Union" << endl;
    // cout << "2. Intersection" << endl;
    // cout << "3. Difference" << endl;
    // cout << "4. Get Set Size" << endl;
    // cout << "5. Reset Set" << endl;
    // cout << "6. Skip" << endl;

    switch (choice)
    {
    case 1:
        if (resultSet.Set_union(&set1, &set2) != OPERATION_CMPLT)
        {
            cout << "Union operation Failed!" << endl;
            result = 1;
        }
        break;
    case 2:
        if (resultSet.Set_intersection(&set1, &set2) != OPERATION_CMPLT)
        {
            cout << "Intersection operation Failed!" << endl;
            result = 1;
        }
        break;
    case 3:
        if (resultSet.Set_difference(&set1, &set2) != OPERATION_CMPLT)
        {
            cout << "S1 - S2 operation Failed!" << endl;
            result = 1;
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

    while (checkSet_stat(mySet1, mySet2))
    {
        if (choice_mySet_menu(mySet1, 1))
            break;

        if (choice_mySet_menu(mySet2, 2))
            break;

        if (choice_resultSet_menu(resultSet, mySet1, mySet2))
            break;
    }
}
