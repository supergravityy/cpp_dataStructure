#define _CRT_SECURE_NO_WARNINGS
#include "../header/bitree.h"
#include "../header/traverse.h"

// �ּ����� ����ü
struct SimpleData {
    char id[8];
    char name[32];
};

// ��� �Լ�
void printSimple(void* data) {
    if (!data) return;
    SimpleData* s = (SimpleData*)data;
    cout << "[ID: " << s->id << ", Name: " << s->name << "]" << endl;
}

// �� �Լ�
typCmpResult compareSimple(const void* a, const void* b) {
    const SimpleData* s1 = (const SimpleData*)a;
    const SimpleData* s2 = (const SimpleData*)b;
    return strcmp(s1->id, s2->id) < 0 ? LESS :
        strcmp(s1->id, s2->id) > 0 ? GREATER : EQUAL;
}

// �Ҹ��� �Լ�
void destroySimple(void* data) {
    delete (SimpleData*)data;
}

// ����ü ����
SimpleData* createSimple(const char* id, const char* name) {
    SimpleData* s = new SimpleData;
    strncpy(s->id, id, sizeof(s->id));
    strncpy(s->name, name, sizeof(s->name));
    return s;
}

// ���� ����Ʈ�� ���� ������ ���� ����
void insertBalanced(BiTree& tree, SimpleData** arr, int index, int size, void* parent, bool left) {
    if (index >= size) return;

    if (parent == nullptr)
        tree.insert_leftChild(nullptr, arr[index]);
    else
        left ? tree.insert_leftChild(parent, arr[index]) :
        tree.insert_rightChild(parent, arr[index]);

    // ���� ��� �ּ� ã�Ƽ� �ڽ� ������ �� ���
    void* nodeKey = arr[index];
    void* nodePtr = lookupTraverse::preOrder(tree.get_bitreeRoot_Addr(), &nodeKey);

    insertBalanced(tree, arr, 2 * index + 1, size, nodePtr, true);
    insertBalanced(tree, arr, 2 * index + 2, size, nodePtr, false);
}

int main() {
    BiTree tree;

    // 1. ����
    lookupTraverse::compareFunc = compareSimple;
    printTraverse::printNodeFunc = printSimple;
    tree.init(compareSimple, printSimple, destroySimple, lookupTraverse::preOrder);

    // 2. ������ �غ�
    const int NUM_NODES = 15;
    SimpleData* nodeArr[NUM_NODES];

    for (int i = 0; i < NUM_NODES; ++i) {
        char id[8];
        sprintf(id, "%02d", i);
        nodeArr[i] = createSimple(id, "tester");
    }

    // 3. ���� ���� Ʈ�� ����
    insertBalanced(tree, nodeArr, 0, NUM_NODES, nullptr, true);

    // 4. ���
    cout << "\n==== ���� ��ȸ ====" << endl;
    printTraverse::preOrder(tree.get_bitreeRoot_Addr());

    cout << "\n==== ���� ��ȸ ====" << endl;
    printTraverse::inOrder(tree.get_bitreeRoot_Addr());

    cout << "\n==== ���� ��ȸ ====" << endl;
    printTraverse::postOrder(tree.get_bitreeRoot_Addr());

    // 5. ���� ���
    cout << "\n==== Ʈ�� ���� ====" << endl;
    cout << "Height: " << tree.get_maxHeight() << endl;

    // 6. ���� �׽�Ʈ
    cout << "\n==== ���� �׽�Ʈ ====" << endl;

    SimpleData targetKey;
    strcpy(targetKey.id, "01");  // �θ� ��� "01"�� ��������

    void* key = &targetKey;
    void* parentNode = lookupTraverse::preOrder(tree.get_bitreeRoot_Addr(), &key);

    if (parentNode)
    {
        cout << "�� ���� �ڽ� ����" << endl;
        tree.remove_leftChild(parentNode);

        cout << "�� ���� �� ���� ��ȸ" << endl;
        printTraverse::preOrder(tree.get_bitreeRoot_Addr());
    }
    else
    {
        cout << "��� '01'�� ã�� �� �����ϴ�." << endl;
    }

    return 0;
}
