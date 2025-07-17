#include <cmath>
#include "../header/HashTable.h"
#pragma comment (lib,"lib/hashTable_debug.lib")


struct Student {
    int id;
    char name[20];
};

typCmpResult cmpStudent(const void* d1, const void* d2) {
    int k1 = ((Student*)d1)->id;
    int k2 = ((Student*)d2)->id;
    return (k1 < k2) ? LESS : (k1 > k2) ? GREATER : EQUAL;
}

void printStudent(const void* data) {
    const Student* s = (const Student*)data;
    cout << "[ID:" << s->id << ", Name:" << s->name << "]" << endl;
}

void freeStudent(void* data) {
    delete (Student*)data;
}

void* getKeyFromStudent(void* data) {
    return &(((Student*)data)->id);
}

void test_basic_crud() {
    cout << "==== [1~3] 기본 기능 및 충돌/중복 테스트 ====" << endl;
    HashTable table;
    table.init(cmpStudent, printStudent, freeStudent, getKeyFromStudent, 10);

    Student* s1 = new Student{ 1, "Alice" };
    Student* s2 = new Student{ 2, "Bob" };
    Student* s3 = new Student{ 3, "Charlie" };
    Student* s4 = new Student{ 15, "Dave" };  // 충돌 유도

    table.insert(s1);
    table.insert(s2);
    table.insert(s3);
    table.insert(s4);

    cout << endl << "====printAll_1====" << endl;
    table.print_allData();

    void* query = new Student{ 2 };
    table.lookup(&query);
    if (query) printStudent(query);

    query = new Student{ 3 };
    table.remove(&query);
    delete (Student*)query;

    Student* s3_dup = new Student{ 3, "Charlie" };
    table.insert(s3_dup); // 중복 삽입 실패 예상

    cout << endl << "====printAll_2====" << endl;
    table.print_allData();
}

void test_string_key() {
    cout << "==== [6.2] 문자열 키 테스트 ====" << endl;

    struct Named {
        char name[20];
    };

    auto cmpName = [](const void* d1, const void* d2) -> typCmpResult {
        return strcmp(((Named*)d1)->name, ((Named*)d2)->name) == 0 ? EQUAL : GREATER;
        };

    auto getKeyFromName = [](void* data) -> void* {
        return ((Named*)data)->name;
        };

    auto printName = [](const void* data) {
        cout << "[Name:" << ((Named*)data)->name << "]" << endl;
        };

    auto freeName = [](void* data) {
        delete (Named*)data;
        };

    HashTable table;
    table.init(cmpName, printName, freeName, getKeyFromName, 10, defaultFunc::method_multiplication);

    table.insert(new Named{ "Tom" });
    table.insert(new Named{ "Jerry" });
    table.insert(new Named{ "Spike" });
    table.insert(new Named{ "Mike" });
    table.insert(new Named{ "Charles" });
    table.insert(new Named{ "James" });
    table.insert(new Named{ "John" });
    table.insert(new Named{ "Muhammad" });
    table.insert(new Named{ "Kimberly" });
    table.insert(new Named{ "Santos" });
    table.insert(new Named{ "Miguel" });
    table.insert(new Named{ "Francisco" });
    table.insert(new Named{ "Emma" });
    table.insert(new Named{ "Edward" });
    table.insert(new Named{ "Charlotte" });
    table.insert(new Named{ "Sofia" });
    table.insert(new Named{ "Valentina" });
    table.insert(new Named{ "Dmitry" });
    table.insert(new Named{ "Pyotr" });
    table.insert(new Named{ "Ivan" });
    table.insert(new Named{ "Zoey" });
    table.insert(new Named{ "Alex" });

    cout << "====printAll====" << endl;
    table.print_allData();
}

void test_bucket_distribution() {
    cout << "==== [5.2] 버킷 분포 분석 테스트 ====" << endl;

    HashTable table;
    int* Arr;
    int elementNum = 0;
    table.init(cmpStudent, printStudent, freeStudent, getKeyFromStudent, 25);

    for (int i = 0; i < 2000; i++) {
        int id = rand() % 10000;
        Student* s = new Student{ id, "bulk" };
        table.insert(s);
    }

    Arr = table.get_bucketSizeArr();

    for (int i = 0; i < table.get_tableSize(); i++)
    {
        cout << "Bucket[" << i << "] size : " << Arr[i] << endl;
        elementNum += Arr[i];
    }

    cout << "Total element Number : " << elementNum << endl;
    cout << "Bucket's elements Number Average : " << elementNum / table.get_tableSize() << endl;

    double varianceSum = 0.0;
    for (int i = 0; i < table.get_tableSize(); i++) {
        double diff = Arr[i] - elementNum / table.get_tableSize();
        varianceSum += diff * diff;
    }
    double stddev = sqrt(varianceSum / table.get_tableSize());
    cout << "Standard Deviation of Bucket Sizes : " << stddev << endl;

    delete[] Arr;
}

int main() {
    test_basic_crud();
    cout << endl;

    test_string_key();
    cout << endl;

    test_bucket_distribution();
    return 0;
}
