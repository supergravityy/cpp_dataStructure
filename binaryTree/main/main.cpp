#define _CRT_SECURE_NO_WARNINGS
#include "../header/bitree.h"
#include "../header/traverse.h"

#pragma comment (lib,"lib/biTree_debug.lib")
#pragma comment (lib,"lib/traverse_debug.lib")

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
    void* nodePtr = lookupTraverse::preOrder((void*)tree.begin(), &nodeKey);

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
        cout << "[Insert] Success using lookup" << endl;
        printTraverse::preOrder((void*)tree.begin());
    }
    else
        cout << "[Insert] Failed using lookup" << endl;

    if (tree.remove_leftChild(tree.lookup((void**)&tempPtr)))
        cout << "[Remove] Success using lookup" << endl;
    else
        cout << "[Remove] Failed using lookup" << endl;

    // -------------------------------
    // 4. 출력
    // -------------------------------
    cout << "\n==== Preorder Traversal ====" << endl;
    printTraverse::preOrder((void*)tree.begin());

    cout << "\n==== Inorder Traversal ====" << endl;
    printTraverse::inOrder((void*)tree.begin());

    cout << "\n==== Postorder Traversal ====" << endl;
    printTraverse::postOrder((void*)tree.begin());

    cout << "\n==== Iterator Test! ====" << endl;
    tree.reset_iter();
    for (const void* it = tree.begin(); it != tree.end(); it = tree.next((void*)it)) {
        printSimple((void*)tree.data((void*)it));
    }

    // -------------------------------
    // 5. 높이 출력
    // -------------------------------
    cout << "\n==== Tree Height ====" << endl;
    cout << "Height: " << tree.get_maxHeight() << endl;

    // -------------------------------
    // 6. 삭제 테스트
    // -------------------------------
    cout << "\n==== Deletion Test ====" << endl;

    SimpleData targetKey;
    strcpy(targetKey.id, "01");  // 부모 노드 "01"을 기준으로

    void* key = &targetKey;
    void* parentNode = lookupTraverse::preOrder((void*)tree.begin(), &key);

    if (parentNode)
    {
        cout << "-> Removing left child" << endl;
        tree.remove_leftChild(parentNode);

        cout << "-> Preorder traversal after removal" << endl;
        printTraverse::preOrder((void*)tree.begin());
    }
    else
    {
        cout << "Node '01' not found." << endl;
    }

    // -------------------------------
    // 7. 새로운 트리 otherTree 구성
    // -------------------------------

    cout << "\n==== Create new tree (otherTree) ====" << endl;
    BiTree otherTree;
    otherTree.init(compareSimple, printSimple, destroySimple, lookupTraverse::preOrder);

    SimpleData* otherNodes[15];
    for (int i = 0; i < 15; ++i) {
        char id[8];
        sprintf(id, "X%02d", i); // 다른 prefix로 구분
        otherNodes[i] = createSimple(id, "other");
    }

    insertBalanced(otherTree, otherNodes, 0, NUM_NODES, nullptr, true);
    cout << "-> Preorder traversal of otherTree:" << endl;
    printTraverse::preOrder((void*)otherTree.begin());

    // -------------------------------
    // 8. merge 테스트
    // -------------------------------

    cout << "\n==== Merge Test ====" << endl;
    BiTree mergedTree;
    mergedTree.init(compareSimple, printSimple, destroySimple, lookupTraverse::preOrder);

    // 새로운 루트 노드 생성 및 삽입
    SimpleData* rootNode = createSimple("ROOT", "merged");

    // 병합 실행: tree → left, otherTree → right
    mergedTree.mergeTree(&tree, &otherTree, rootNode);

    cout << "-> Preorder traversal after merge:" << endl;
    printTraverse::preOrder((void*)mergedTree.begin());

    // -------------------------------
    // 9. 병합 트리 높이 확인
    // -------------------------------

    cout << "\n==== Merged Tree Height ====" << endl;
    cout << "Height of mergedTree: " << mergedTree.get_maxHeight() << endl;

    return 0;
}
