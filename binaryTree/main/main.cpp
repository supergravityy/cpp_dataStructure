#include "../header/BiTree.h"

using namespace std;

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
    cout << "3. Print All" << endl;
    cout << "4. Skip" << endl;
    cout << "0. Exit" << endl;
    cout << "==============================" << endl;
}

void inputData(MyAddr &data)
{
    cout << "Enter node ID: ";
    cin >> data.id;
    cout << "Enter node name: ";
    cin >> data.name;
    cout << "Enter node phoneNumber: ";
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
	MyAddr parentsData = { 0, 0, 0 };
	BiTreeNode* target = nullptr;

    if (myTree.BiTree_getErrCode() != NORMAL)
        return 1;

    while (myTree.BiTree_getErrCode() == NORMAL && terminationCmd == false)
    {
        printMenu(num);
        cin >> choice;

        switch (choice)
        {
		case 1: // left insert

			makeResult = makeData(&newData); // 1. 데이터를 저장할 newData를 생성
            if (makeResult)
            {
                terminationCmd = true;
                break;
            }

			cout << "Enter new Data " << endl;
			inputData(*newData); // 2. newData에 데이터를 입력

			if (myTree.BiTree_preOrder_find(myTree.BiTree_getRoot(), newData)) // 3. 만약, newData가 이미 존재한다면
			{
				cout << "Already exist!" << endl;
				terminationCmd = true;
				break;
			}


			if (myTree.BiTree_getSize() == 0) // 4. 만약, 트리가 비어있다면
			{
				cout << "Tree is Empty!" << endl;
                target = nullptr;
			}
			else // 4.1. 트리가 비어있지 않다면
            {
                cout << "Enter target Info " << endl;
				inputData(parentsData); // 4.1.1 부모 노드의 정보를 입력받는다.

                target = myTree.BiTree_preOrder_search(myTree.BiTree_getRoot(), &parentsData);  // 4.1.2 부모 노드가 있는지를 탐색
                if (target == nullptr)
                {
                    cout << "Target node not found!" << endl;
                    break;
                }
                else {}

				if (target->left != nullptr) // 4.1.3 부모노드의 leftChild가 이미 존재한다면
                {
                    cout << "Left child already exists!" << endl;
                    break;
                }
                else {}
            }
		
			if (myTree.BiTree_ins_left(target, newData) == 0) // 5. 부모 노드의 leftChild로 newData를 삽입
                cout << "Insert successfully!" << endl;
            else
                cout << "Failed to Insert!" << endl;

            break;

		case 2: // right insert
            makeResult = makeData(&newData); // 1. 데이터를 저장할 newData를 생성
            if (makeResult)
            {
                terminationCmd = true;
                break;
            }

            cout << "Enter new Data " << endl;
            inputData(*newData); // 2. newData에 데이터를 입력

            if (myTree.BiTree_preOrder_find(myTree.BiTree_getRoot(), newData)) // 3. 만약, newData가 이미 존재한다면
            {
                cout << "Already exist!" << endl;
                terminationCmd = true;
                break;
            }


            if (myTree.BiTree_getSize() == 0) // 4. 만약, 트리가 비어있다면
            {
                cout << "Tree is Empty!" << endl;
                target = nullptr;
            }
            else // 4.1. 트리가 비어있지 않다면
            {
                cout << "Enter target Info " << endl;
                inputData(parentsData); // 4.1.1 부모 노드의 정보를 입력받는다.

                target = myTree.BiTree_preOrder_search(myTree.BiTree_getRoot(), &parentsData);  // 4.1.2 부모 노드가 있는지를 탐색
                if (target == nullptr)
                {
                    cout << "Target node not found!" << endl;
                    break;
                }
                else {}

                if (target->right != nullptr) // 4.1.3 부모노드의 rightChild가 이미 존재한다면
                {
                    cout << "Right child already exists!" << endl;
                    break;
                }
                else {}
            }

            if (myTree.BiTree_ins_right(target, newData) == 0) // 5. 부모 노드의 rightChild로 newData를 삽입
                cout << "Insert successfully!" << endl;
            else
                cout << "Failed to Insert!" << endl;

			break;

		case 3: // left remove
            
			cout << "Enter target Info " << endl;
            inputData(parentsData);

            target = myTree.BiTree_preOrder_search(myTree.BiTree_getRoot(), &parentsData);
            if (target == nullptr)
            {
                cout << "Target node not found!" << endl;
                break;
            }

            if (target->left == nullptr)
            {
                cout << "Left child does not exist!" << endl;
                break;
            }

            if (myTree.BiTree_rem_left(target))
            {
                cout << "Remove successfully! " << endl;
                printData(*(target->data));
            }
            else
                cout << "Failed to Remove!" << endl;
            break;

		case 4: // right remove

            cout << "Enter target Info " << endl;
            inputData(parentsData);

            target = myTree.BiTree_preOrder_search(myTree.BiTree_getRoot(), &parentsData);
            if (target == nullptr)
            {
                cout << "Target node not found!" << endl;
                break;
            }

            if (target->right == nullptr)
            {
                cout << "Right child does not exist!" << endl;
                break;
            }

            if (myTree.BiTree_rem_right(target))
            {
                cout << "Remove successfully! " << endl;
                printData(*(target->data));
            }
            else
                cout << "Failed to Remove!" << endl;
            break;

		case 5: // get size
            cout << "currentSize : " << myTree.BiTree_getSize() << endl;
            break;

		case 6: // reset tree
            myTree.BiTree_init();
            cout << "destroying Tree completed!" << endl;
            break;

		case 7: // print all
			myTree.preOrderPrint(myTree.BiTree_getRoot());
            break;

		case 8: // skip
            return 0;
            break;

        case 0:
            terminationCmd = true;
			return 0;
            break;

		default:
			cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }

    return 0;
}

int choice_myBiTree_merging(BiTree &mergeTree, BiTree &myTree1, BiTree &myTree2)
{
    int choice;
    int makeResult;

    MyAddr* newData = nullptr;

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
		case 1: // merge

            makeResult = makeData(&newData);
            if (makeResult)
            {
                terminationCmd = true;
                break;
            }

			cout << "Enter new Data for mergeTree " << endl;
            inputData(*newData);

            if (mergeTree.BiTree_merge(&myTree1, &myTree2, newData) == true)
                cout << "Merge successfully!" << endl;
            else
                cout << "Failed to Merge!" << endl;
            break;

		case 2: // reset tree
            mergeTree.BiTree_init();
            cout << "destroying Tree completed!" << endl;
            break;

		case 3: // print all
			cout << "mergeTree's all nodes.." << endl;
			mergeTree.preOrderPrint(mergeTree.BiTree_getRoot());
            break;

        case 4:
            return 0;
            break;

        case 0:
            terminationCmd = true;
            return 0;
            break;

		default:   
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
    return 0;
}

int main()
{
    BiTree tree1, tree2, tree3;

    while (!terminationCmd)
    {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Manage Tree 1\n";
        cout << "2. Manage Tree 2\n";
        cout << "3. Merge Tree1 & Tree2 into Tree3\n";
        cout << "0. Exit\n";
        cout << "==================\n";
        cout << "Select: ";

        int topChoice;
        cin >> topChoice;

        switch (topChoice)
        {
        case 1:
            choice_myBiTree_menu(tree1, 1);
            break;
        case 2:
            choice_myBiTree_menu(tree2, 2);
            break;
        case 3:
            choice_myBiTree_merging(tree3, tree1, tree2);
            break;
        case 0:
            terminationCmd = true;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }

    return 0;
}
