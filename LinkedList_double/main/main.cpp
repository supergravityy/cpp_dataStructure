#include "../header/dList.h"
#pragma comment (lib,"lib/dobuleLinkedList_debug.lib")

// ����� ���� ������ ����
typedef struct {
    int id;
    char name[32];
} UserData;

// �� �Լ�
typCmpResult compareUser(const void* a, const void* b) {
    const UserData* userA = (const UserData*)a;
    const UserData* userB = (const UserData*)b;
    if (userA->id < userB->id) return LESS;
    if (userA->id > userB->id) return GREATER;
    return EQUAL;
}

// ��� �Լ�
void printUser(const void* data) {
    const UserData* user = (const UserData*)data;
    cout << "ID: " << user->id << ", Name: " << user->name << endl;
}

// �޸� ���� �Լ�
void destroyUser(void* data) {
    delete (UserData*)data;
}

int main() {
    dList myList;
    myList.init(compareUser, printUser, destroyUser);

    // ---------- 1. insert_nextNode (�߰� & �� �� ����) ----------
    auto* u1 = new UserData{ 1, "Alice" };
    auto* u2 = new UserData{ 2, "Bob" };
    auto* u3 = new UserData{ 3, "Charlie" };

    myList.insert_nextNode(nullptr, u1);  // �� �� ����
    void* node1 = myList.lookup_Node(u1); // u1 ��ġ ã��
    myList.insert_nextNode(node1, u2);    // u2�� u1 �ڿ� ����
    myList.insert_nextNode(node1, u3);    // u3�� u1�� u2 ���̿� ����

    cout << "\n[After insert_nextNode tests]" << endl;
    myList.printAll();

    // ---------- 1-1. push_back ----------
    auto* u4 = new UserData{ 4, "Diana" };
    myList.push_back(u4);

    cout << "\n[After push_back]" << endl;
    myList.printAll();

    // ---------- 2. insert_prevNode ----------
    auto* u5 = new UserData{ 5, "Eve" };
    auto* u6 = new UserData{ 6, "Frank" };

    void* node3 = myList.lookup_Node(u3);
    myList.insert_prevNode(node3, u5); // u5�� u3 �տ� ����
    myList.push_front(u6);             // �� �� ����

    // ---------- 2-2. ���� ���� ----------
    auto* u7 = new UserData{ 7, "Grace" };
    void* node4 = myList.lookup_Node(u4);
    myList.insert_prevNode(node4, u7); // u7�� u4 �տ� ����

    cout << "\n[After insert_prevNode and push_front]" << endl;
    myList.printAll();

    // ---------- 3. remove_tgtNode ----------
    void* data = nullptr;

    void* node2 = myList.lookup_Node(u2);  // u2 ����
    myList.remove_tgtNode(node2, &data);
    destroyUser(data);

    cout << "\n[After remove_tgtNode (u2)]" << endl;
    myList.printAll();

    // ---------- 3-1. pop_back ----------
    myList.pop_back(&data);
    destroyUser(data);

    cout << "\n[After pop_back]" << endl;
    myList.printAll();

    // ---------- 3-2. pop_front ----------
    myList.pop_front(&data);
    destroyUser(data);

    cout << "\n[After pop_front]" << endl;
    myList.printAll();

    // ---------- 4. lookup ----------
    auto* findMe = new UserData{ 5, "" };  // ID�θ� ��
    void* foundNode = myList.lookup_Node(findMe);
    if (foundNode) {
        UserData* foundData = (UserData*)myList.data(foundNode);
        cout << "\n[Lookup] Found ID " << foundData->id << " (" << foundData->name << ")" << endl;
    }
    else {
        cout << "\n[Lookup] Not found." << endl;
    }
    delete findMe;

    // ---------- 5. destroy ----------
    myList.init(compareUser, printUser, destroyUser);
    cout << "\n[After destroyList]" << endl;
    myList.printAll();  // �ƹ��͵� ��µ��� �ʾƾ� ��

    return 0;
}
