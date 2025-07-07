#define _CRT_SECURE_NO_WARNINGS
#include "../header/bitree.h"
#include "../header/traverse.h"

// 최소한의 구조체
struct SimpleData {
    char id[8];
    char name[32];
};

// 출력 함수
void printSimple(void* data) {
    if (!data) return;
    SimpleData* s = (SimpleData*)data;
    cout << "[ID: " << s->id << ", Name: " << s->name << "]" << endl;
}

// 비교 함수
typCmpResult compareSimple(const void* a, const void* b) {
    const SimpleData* s1 = (const SimpleData*)a;
    const SimpleData* s2 = (const SimpleData*)b;
    return strcmp(s1->id, s2->id) < 0 ? LESS :
        strcmp(s1->id, s2->id) > 0 ? GREATER : EQUAL;
}

// 소멸자 함수
void destroySimple(void* data) {
    delete (SimpleData*)data;
}

// 구조체 생성
SimpleData* createSimple(const char* id, const char* name) {
    SimpleData* s = new SimpleData;
    strncpy(s->id, id, sizeof(s->id));
    strncpy(s->name, name, sizeof(s->name));
    return s;
}

// 완전 이진트리 순서 삽입을 위한 헬퍼
void insertBalanced(BiTree& tree, SimpleData** arr, int index, int size, void* parent, bool left) {
    if (index >= size) return;

    if (parent == nullptr)
        tree.insert_leftChild(nullptr, arr[index]);
    else
        left ? tree.insert_leftChild(parent, arr[index]) :
        tree.insert_rightChild(parent, arr[index]);

    // 현재 노드 주소 찾아서 자식 삽입할 때 사용
    void* nodeKey = arr[index];
    void* nodePtr = lookupTraverse::preOrder(tree.get_bitreeRoot_Addr(), &nodeKey);

    insertBalanced(tree, arr, 2 * index + 1, size, nodePtr, true);
    insertBalanced(tree, arr, 2 * index + 2, size, nodePtr, false);
}

int main() {
    BiTree tree;

    // 1. 설정
    lookupTraverse::compareFunc = compareSimple;
    printTraverse::printNodeFunc = printSimple;
    tree.init(compareSimple, printSimple, destroySimple, lookupTraverse::preOrder);

    // 2. 데이터 준비
    const int NUM_NODES = 15;
    SimpleData* nodeArr[NUM_NODES];

    for (int i = 0; i < NUM_NODES; ++i) {
        char id[8];
        sprintf(id, "%02d", i);
        nodeArr[i] = createSimple(id, "tester");
    }

    // 3. 균형 이진 트리 삽입
    insertBalanced(tree, nodeArr, 0, NUM_NODES, nullptr, true);

    SimpleData *tempData = new SimpleData { "99","addedBylookup" };
    SimpleData findData = { "14","" };
    SimpleData* tempPtr = &findData;

    if (tree.insert_leftChild(tree.lookup((void**)&tempPtr), tempData) == INSERT_SUCCESS)
    {
        cout << "lookup기반 삽입 성공!" << endl;
        printTraverse::preOrder(tree.get_bitreeRoot_Addr());
    }
    else
        cout << "lookup기반 삽입 실패!" << endl;

    if (tree.remove_leftChild(tree.lookup((void**)&tempPtr)))
        cout << "lookup기반 삭제 성공!" << endl;
    else
        cout << "lookup기반 삭제 실패!" << endl;
    
    // 4. 출력
    cout << "\n==== 전위 순회 ====" << endl;
    printTraverse::preOrder(tree.get_bitreeRoot_Addr());

    cout << "\n==== 중위 순회 ====" << endl;
    printTraverse::inOrder(tree.get_bitreeRoot_Addr());

    cout << "\n==== 후위 순회 ====" << endl;
    printTraverse::postOrder(tree.get_bitreeRoot_Addr());

    // 5. 높이 출력
    cout << "\n==== 트리 높이 ====" << endl;
    cout << "Height: " << tree.get_maxHeight() << endl;

    // 6. 삭제 테스트
    cout << "\n==== 삭제 테스트 ====" << endl;

    SimpleData targetKey;
    strcpy(targetKey.id, "01");  // 부모 노드 "01"을 기준으로

    void* key = &targetKey;
    void* parentNode = lookupTraverse::preOrder(tree.get_bitreeRoot_Addr(), &key);

    if (parentNode)
    {
        cout << "→ 왼쪽 자식 삭제" << endl;
        tree.remove_leftChild(parentNode);

        cout << "→ 삭제 후 전위 순회" << endl;
        printTraverse::preOrder(tree.get_bitreeRoot_Addr());
    }
    else
    {
        cout << "노드 '01'을 찾을 수 없습니다." << endl;
    }

   // 7. 새로운 트리 otherTree 구성
    cout << "\n==== 새로운 트리(otherTree) 생성 ====" << endl;
    BiTree otherTree;
    otherTree.init(compareSimple, printSimple, destroySimple, lookupTraverse::preOrder);

    SimpleData* otherNodes[15];
    for (int i = 0; i < 15; ++i) {
        char id[8];
        sprintf(id, "X%02d", i); // 다른 prefix로 구분
        otherNodes[i] = createSimple(id, "other");
    }

    insertBalanced(otherTree, otherNodes, 0, NUM_NODES, nullptr, true);
    cout << "→ otherTree 전위 순회:" << endl;
    printTraverse::preOrder(otherTree.get_bitreeRoot_Addr());

    // -------------------------------
    // 8. merge 테스트
    cout << "\n==== merge 테스트 ====" << endl;
    BiTree mergedTree;
    mergedTree.init(compareSimple, printSimple, destroySimple, lookupTraverse::preOrder);

    // 새로운 루트 노드 생성 및 삽입
    SimpleData* rootNode = createSimple("ROOT", "merged");

    // 병합 실행: tree → left, otherTree → right
    mergedTree.mergeTree(&tree, &otherTree, rootNode);

    cout << "→ merge 후 전위 순회:" << endl;
    printTraverse::preOrder(mergedTree.get_bitreeRoot_Addr());

    // -------------------------------
    // 9. 병합 트리 높이 확인
    cout << "\n==== 병합 트리 높이 ====" << endl;
    cout << "Height of mergedTree: " << mergedTree.get_maxHeight() << endl;

    return 0;
}
