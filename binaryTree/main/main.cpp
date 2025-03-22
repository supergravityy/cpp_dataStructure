#include "../header/BiTree.h"

bool terminationCmd = false;

void printMenu(int num)
{
    cout << "\n===== BinaryTree [" << num << "] Menu =====" << endl;
    cout << "1. Insert left" << endl;
    cout << "2. Insert right" << endl;
    cout << "3. Remove left" << endl;
    cout << "4. Remove right" << endl;
    cout << "5. Get Tree Size" << endl;
    cout << "6. Reset Tree" << endl;
    cout << "7. Print All" << endl;
    cout << "8. Skip" << endl;
    cout << "0. Exit" << endl;
    cout << "==============================" << endl;
}

void printOperation()
{
    cout << "\n===== BinaryTree [mergeTree] Menu =====" << endl;
    cout << "1. Merge" << endl;
    cout << "2. Reset tree" << endl;
    cout << "3. Print Al" << endl;
    cout << "4. Skip" << endl;
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

int choice_myBiTree_menu(BiTree &myTree, int num)
{
    int choice;
    int makeResult;
    BiTreeNode *tgtNode = nullptr;
    MyAddr *newData = nullptr;
    MyAddr *removedData = nullptr;

    if (myTree.BiTree_getErrCode() != NORMAL)
        return 1;

    while (myTree.BiTree_getErrCode() == NORMAL)
    {
        printMenu(num);
        cin >> choice;

        switch (choice)
        {
        case 1:
            makeResult = makeData(&newData);
            if (makeResult)
            {
                terminationCmd = true;
                break;
            }
            // TODO : traverse 함수를 만들어서, 노드찾는기능 추가

            inputData(*newData);
            if (myTree.BiTree_ins_left() == 0)
                cout << "Insert successfully!" << endl;
            else
                cout << "Failed to Insert!" << endl;
            break;

        case 2:
            makeResult = makeData(&newData);
            if (makeResult)
            {
                terminationCmd = true;
                break;
            }
            // TODO : traverse 함수를 만들어서, 노드찾는기능 추가

            inputData(*newData);
            if (myTree.BiTree_ins_right() == 0)
                cout << "Insert successfully!" << endl;
            else
                cout << "Failed to Insert!" << endl;
            break;

        case 3:
            // TODO : traverse 함수를 만들어서, 노드찾는기능 추가

            if (myTree.BiTree_rem_left() == 0)
                cout << "Remove successfully!" << endl;
            else
                cout << "Failed to Remove!" << endl;
            break;

        case 4:
            // TODO : traverse 함수를 만들어서, 노드찾는기능 추가

            if (myTree.BiTree_rem_right() == 0)
                cout << "Remove successfully!" << endl;
            else
                cout << "Failed to Remove!" << endl;
            break;

        case 5:
            cout << "currentSize : " << myTree.BiTree_getSize() << endl;
            break;

        case 6:
            myTree.BiTree_init();
            cout << "destroying Tree completed!" << endl;
            break;

        case 7:
            // TODO : 트리 순회하며 모두 출력하는 기능 구현
            break;

        case 8:
            break;

        case 0:
            terminationCmd = true;
            break;
        }
    }
}

int choice_myBiTree_merging(BiTree &mergeTree, BiTree &myTree1, BiTree &myTree2)
{
    int choice;
    int makeResult;

    if (mergeTree.BiTree_getErrCode() != NORMAL 
    || myTree1.BiTree_getErrCode() != NORMAL 
    || myTree2.BiTree_getErrCode() != NORMAL)
        return 1;

    while (mergeTree.BiTree_getErrCode() == NORMAL)
    {
        printOperation();
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (mergeTree.BiTree_merge(&myTree1, &myTree2) == 0)
                cout << "Merge successfully!" << endl;
            else
                cout << "Failed to Merge!" << endl;
            break;

        case 2:
            mergeTree.BiTree_init();
            cout << "destroying Tree completed!" << endl;
            break;

        case 3:
            // TODO : traverse 함수를 만들어서, 노드찾는기능 추가
            break;

        case 4:
            break;

        case 0:
            terminationCmd = true;
            break;
        }
    }
}

int main()
{
    BiTree tree1, tree2, tree3;

    while (true)
    {
    }

    return 0;
}