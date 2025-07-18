#include "../header/avltree.h"
#pragma comment (lib,"lib/avlTree_debug.lib")
#include "../header/traverse.h"
#pragma comment (lib,"lib/traverse2_debug.lib")

struct MyData {
    int key;
    std::string name;
};

// ----------------------- ��ƿ��Ƽ �Լ� -----------------------

typCmpResult compareFunc(const void* a, const void* b) {
    const MyData* d1 = static_cast<const MyData*>(a);
    const MyData* d2 = static_cast<const MyData*>(b);
    if (d1->key < d2->key) return LESS;
    else if (d1->key > d2->key) return GREATER;
    else return EQUAL;
}

void printFunc(void* data) {
    const MyData* d = static_cast<MyData*>(data);
    cout << d->key << "(" << d->name << ") ";
}

void destroyFunc(void* data) {
    delete static_cast<MyData*>(data);
}

MyData* create(int key, const string& name) {
    return new MyData{ key, name };
}

// ----------------------- �׽�Ʈ ���� -----------------------

int main() {
    // 1. Ʈ�� 4�� ���� (LL, LR, RR, RL)
    AvlTree treeLL, treeLR, treeRR, treeRL;

    avltree_lookupTraverse::compareFunc = compareFunc;
    avltree_printTraverse::printNodeFunc = printFunc;

    treeLL.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);
    treeLR.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);
    treeRR.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);
    treeRL.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);

    // ������ ����
    int keysLL[] = { 50, 30, 70, 20, 40, 10, 25, 5, 3, 1, 0};           // LL
    int keysLR[] = { 50, 30, 70, 20, 27, 35, 10, 45, 32, 38, 36 };      // LR
    int keysRR[] = { 50, 30, 70, 60, 80, 90, 100, 110, 105, 120, 25 };  // RR
	int keysRL[] = { 50, 70, 60, 65, 30, 90, 100, 55, 63, 68, 67 };     // RL
    
    cout << "===Result of Inserting...===" << endl;
    for (int k : keysLL) treeLL.insert(create(k, "LL"));
    cout << "Inserted into treeLL: " << treeLL.get_Count() << endl;
	treeLL.printAll(); 
	cout << endl ;
    for (int k : keysLR) treeLR.insert(create(k, "LR"));
    cout << "Inserted into treeLR: " << treeLR.get_Count() << endl;
    treeLR.printAll();
    cout << endl ;
    for (int k : keysRR) treeRR.insert(create(k, "RR"));
    cout << "Inserted into treeRR: " << treeRR.get_Count() << endl;
    treeRR.printAll();
    cout << endl ;
    for (int k : keysRL) treeRL.insert(create(k, "RL"));
    cout << "Inserted into treeRL: " << treeRL.get_Count() << endl;
    treeRL.printAll();
    cout << endl ;

    // 2. �� Ʈ���� ���� ����
    cout << endl << "===Print of height of Trees...===" << endl;
    cout << "treeLL height: " << treeLL.get_maxHeight() << endl;
    cout << "treeLR height: " << treeLR.get_maxHeight() << endl;
    cout << "treeRR height: " << treeRR.get_maxHeight() << endl;
    cout << "treeRL height: " << treeRL.get_maxHeight() << endl;

    // 3. �˻� �׽�Ʈ
    cout << endl << "===Search of ID=70 nodes...===" << endl;
    for (auto tree : { &treeLL, &treeLR, &treeRR, &treeRL }) {
        MyData query = { 70, "" };
        MyData* ptr = &query;
        if (tree->search((void**)&ptr)) {
            cout << "Found 70 in tree: " ;
			printFunc(ptr);
            cout << endl;
        }
        else {
            cout << "70 not found in tree!" << endl;
        }
    }

    // 4. ��� Ʈ������ ���� �� ��˻� �׽�Ʈ
    cout << endl << "===Delete and Retry of Searching Test..===" << endl;
    cout << "[���� �� ��˻� �׽�Ʈ]\n";
    for (auto tree : { &treeLL, &treeLR, &treeRR, &treeRL }) {
        MyData* q = new MyData{ 70, "" };
        tree->remove(q);
        if (tree->search((void**)&q)) {
            cout << "���� ����: 70 ������ ����\n";
        }
        else {
            cout << "���� ����: 70 ����. ���� :" << tree->get_Count() << endl;
            tree->printAll();
			cout << endl;
        }
    }

    return 0;
}
