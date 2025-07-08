#include "../header/avltree.h"
#include "../header/traverse.h"
#include <iostream>
#include <string>

using namespace std;

struct MyData {
    int key;
    std::string name;
};

// ----------------------- 유틸리티 함수 -----------------------

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

// ----------------------- 테스트 본문 -----------------------

int main() {
    // 1. 트리 4개 생성 (LL, LR, RR, RL)
    AvlTree treeLL, treeLR, treeRR, treeRL;

    avltree_lookupTraverse::compareFunc = compareFunc;
    avltree_printTraverse::printNodeFunc = printFunc;

    treeLL.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);
    treeLR.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);
    treeRR.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);
    treeRL.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);

    // 데이터 삽입
    int keysLL[] = { 50, 30, 70, 20, 40, 10, 25, 5, 3, 1, 0};     // LL
    int keysLR[] = { 50, 30, 70, 20, 40, 10, 25, 15, 27, 26 };  // LR
    int keysRR[] = { 50, 30, 70, 60, 80, 90, 100, 110, 105, 120, 25 }; // RR
    int keysRL[] = { 50, 30, 70, 60, 80, 75, 90, 85, 77, 76, 25 };     // RL

    for (int k : keysLL) treeLL.insert(create(k, "LL"));
	cout << "===Result of Inserting...===" << endl;
	cout << "Inserted into treeLL: ";
	treeLL.printAll();
	cout << endl ;
    for (int k : keysLR) treeLR.insert(create(k, "LR"));
    cout << "Inserted into treeLR: ";
    treeLR.printAll();
    cout << endl ;
    for (int k : keysRR) treeRR.insert(create(k, "RR"));
    cout << "Inserted into treeRR: ";
    treeRR.printAll();
    cout << endl ;
    for (int k : keysRL) treeRL.insert(create(k, "RL"));
    cout << "Inserted into treeRL: ";
    treeRL.printAll();
    cout << endl ;

    // 2. 각 트리의 높이 측정
    cout << endl << "===Print of height of Trees...===" << endl;
    cout << "treeLL height: " << treeLL.get_maxHeight() << endl;
    cout << "treeLR height: " << treeLR.get_maxHeight() << endl;
    cout << "treeRR height: " << treeRR.get_maxHeight() << endl;
    cout << "treeRL height: " << treeRL.get_maxHeight() << endl;

    // 3. 검색 테스트
    cout << endl << "===Search of ID=25 nodes...===" << endl;
    for (auto tree : { &treeLL, &treeLR, &treeRR, &treeRL }) {
        MyData query = { 25, "" };
        MyData* ptr = &query;
        if (tree->search((void**)&ptr)) {
            cout << "Found 25 in tree: " ;
			printFunc(ptr);
            cout << endl;
        }
        else {
            cout << "25 not found in tree!" << endl;
        }
    }

    // 4. 모든 트리에서 삭제 및 재검색 테스트
    cout << endl << "===Delete and Retry of Searching Test..===" << endl;
    cout << "[삭제 및 재검색 테스트]\n";
    for (auto tree : { &treeLL, &treeLR, &treeRR, &treeRL }) {
        MyData* q = new MyData{ 25, "" };
        tree->remove(q);
        if (tree->search((void**)&q)) {
            cout << "삭제 실패: 25 여전히 존재\n";
        }
        else {
            cout << "삭제 성공: 25 없음\n";
            tree->printAll();
			cout << endl;
        }
        delete q;
    }

    // 5. 두 트리 병합 후 출력
    cout << "\n===[트리 병합 테스트 - treeLL + treeRR]===\n";
    AvlTree mergedTree;
    mergedTree.init(compareFunc, avltree_printTraverse::inOrder, destroyFunc, avltree_lookupTraverse::preOrder);

    MyData* rootData = create(999, "merged");
    mergedTree.mergeTree(&treeLL, &treeRR, rootData);

    mergedTree.printAll();
    cout << endl;

    // 6. 병합 트리 높이 출력
    cout << "mergedTree height: " << mergedTree.get_maxHeight() << endl;

    return 0;
}
