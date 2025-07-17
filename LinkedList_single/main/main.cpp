#define _CRT_SECURE_NO_WARNINGS
#include "../header/List.h"
#pragma comment (lib,"lib/singleLinkedList_debug.lib")


// 사용자 정의 구조체
typedef struct {
    int id;
    char name[32];
} UserData;

// 비교 함수
typCmpResult compareUser(const void* a, const void* b) {
    int id1 = ((UserData*)a)->id;
    int id2 = ((UserData*)b)->id;
    if (id1 < id2) return LESS;
    else if (id1 > id2) return GREATER;
    else return EQUAL;
}

// 출력 함수
void printUser(const void* data) {
    const UserData* user = (UserData*)data;
    cout << "[ID: " << user->id << ", Name: " << user->name << "]" << endl;
}

// 메모리 해제 함수
void destroyUser(void* data) {
    delete (UserData*)data;
}

int main() {
    List myList;

    if (!myList.init(compareUser, printUser, destroyUser)) {
        cout << "List initialization failed!" << endl;
        return -1;
    }

    cout << "List initialized.\n" << endl;

    // 삽입 테스트
    for (int i = 1; i <= 5; ++i) {
        UserData* user = new UserData{ i };
        sprintf(user->name, "User%d", i);
        myList.push_back(user);
    }

    cout << "After pushBack insertions:" << endl;
    myList.printAll();

    // 앞 삽입
    UserData* frontUser = new UserData{ 0, "Front" };
    myList.insert_nextNode(nullptr, frontUser);

    // 중간 삽입
    const typSingleList_Node* head = myList.begin();
    UserData* midUser = new UserData{ 999, "Middle" };
    myList.insert_nextNode((void*)head, midUser);

    // 끝 삽입
    UserData* rearUser = new UserData{ 212, "Rear" };
    myList.push_back(rearUser);

    cout << "\nAfter insertions:" << endl;
    myList.printAll();

    // 탐색 테스트
    cout << "\nLookup test:" << endl;
    UserData key = { 3 };
    void* found = myList.lookup_Node(&key);
    if (found) {
        cout << "Found: ";
        printUser(myList.data(found));
    }
    else {
        cout << "ID 3 not found." << endl;
    }

    UserData key2 = { 212 };
    found = myList.lookup_Node(&key2);
    if (found) {
        cout << "Found: ";
        printUser(myList.data(found));
    }
    else {
        cout << "ID 212 not found." << endl;
    }

    // 삭제 테스트
    cout << "\nDelete test:" << endl;
    void* deleted = nullptr;

    // head 삭제
    myList.remove_nextNode(nullptr, &deleted);
    printUser((UserData*)deleted);
    destroyUser(deleted);
    myList.printAll();

    // 중간 삭제
    void* prev = (void*)myList.begin();
    myList.remove_nextNode(prev, &deleted);
    printUser((UserData*)deleted);
    destroyUser(deleted);
    myList.printAll();

    // tail 앞 노드 삭제
    const typSingleList_Node* iter = myList.begin();
    const typSingleList_Node* next = myList.next(iter);

    while (myList.next(next) != nullptr) {
        iter = next;
        next = myList.next(iter);
    }

    myList.remove_nextNode((void*)iter, &deleted);
    printUser((UserData*)deleted);
    destroyUser(deleted);
    myList.printAll();

    cout << "\nFinal list size: " << myList.getSize() << endl;
    cout << "List destroy." << endl;

    myList.init(compareUser, printUser, destroyUser);
    myList.printAll();

    return 0;
}
