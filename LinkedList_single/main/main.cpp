#define _CRT_SECURE_NO_WARNINGS
#include "../header/List.h"

// 테스트용 사용자 데이터 구조체
typedef struct {
    int id;
    char name[32];
} UserData;

// 비교 함수: id 기준
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
    UserData* deleteData = (UserData*)data;

    if (deleteData == nullptr)
        return;
    else
        delete deleteData;
    
    return;
}

int main() {
    List myList;

    // 1. 객체 생성 및 초기화
    if (!myList.init(compareUser, printUser, destroyUser)) {
        cout << "List initialization failed!" << endl;
        return -1;
    }
    cout << "List initialized.\n" << endl;

    // 2. 여러 번의 삽입 (pushBack + head + 중간)
    for (int i = 1; i <= 5; ++i) {
        UserData* user = new UserData{ i, "" };
        sprintf(user->name, "User%d", i);
        myList.push_back(user); // pushBack
    }

    cout << " After pushBack insertions:" << endl;
    myList.printAll();

    // 맨 앞 삽입
    UserData* frontUser = new UserData{ 0, "Front" };
    myList.insert_nextNode(nullptr, frontUser);

    // 중간 삽입: head 다음에 삽입
    void* head = myList.get_headAddr();
    UserData* midUser = new UserData{ 999, "Middle" };
    myList.insert_nextNode(head, midUser);

    // 끝 삽입 : tail 업데이트
    UserData* rearUser = new UserData{ 212, "Rear" };
    myList.push_back(rearUser);

    cout << "\n After insertions:" << endl;
    myList.printAll();

    // 3. 임의 검색 테스트
    cout << "\n Lookup test:" << endl;
    UserData key = { 3 };
    void* found = myList.lookup_Node(&key);
    if (found) {
        cout << " Found: ";
        printUser(myList.get_Data(found));
    }
    else {
        cout << " ID 3 not found." << endl;
    }

    UserData FoundKey = { 212 };
    found = myList.lookup_Node(&FoundKey);
    if (!found) {
        cout << " Correctly not found (ID = 212)" << endl;
    }
    else{
        cout << " Found: ";
        printUser(myList.get_Data(found));
    }

    // 4. 일부 삭제 테스트
    cout << "\n Delete test:" << endl;
    void* deletedData_addr = nullptr;
    UserData* deletedData = nullptr;

    // head 삭제
    myList.remove_nextNode(nullptr, &deletedData_addr);
	deletedData = (UserData*)deletedData_addr;
    cout << " After deleting head:" << deletedData->id << ", " << deletedData->name << endl;
    destroyUser(deletedData);
    myList.printAll();

    // 중간 삭제 (head의 다음 노드)
    void* prev = myList.get_headAddr();
    myList.remove_nextNode(prev, &deletedData_addr);
    deletedData = (UserData*)deletedData_addr;
    cout << " After deleting middle node:" << deletedData->id << ", " << deletedData->name << endl;
    destroyUser(deletedData);
    myList.printAll();

    // tail 앞 노드 삭제
    void* prevTail = myList.get_headAddr();
    
    while (myList.get_nextAddr(myList.get_nextAddr(prevTail)) != nullptr) {
        prevTail = myList.get_nextAddr(prevTail);
    }
    myList.remove_nextNode(prevTail, &deletedData_addr);
    deletedData = (UserData*)deletedData_addr;
    cout << " After deleting node before tail:" << deletedData->id << ", " << deletedData->name << endl;
    destroyUser(deletedData);
    myList.printAll();

    cout << "\n Final list size: " << myList.getSize() << endl;
	cout << "List destroy." << endl;
	myList.destroyList(); // 리스트 파괴
    myList.printAll();

    return 0;
}
