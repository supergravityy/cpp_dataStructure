#include "../header/bitree.h"
#include "../header/AVLtree.h"

//#define LLTEST
//#define LRTEST
//#define RRTEST
//#define RLTEST

struct MyData
{
	int key;
};

typCmpResult compareFunc(const void* key1, const void* key2) 
{
    const MyData* d1 = static_cast<const MyData*>(key1);
    const MyData* d2 = static_cast<const MyData*>(key2);
    if (d1->key < d2->key)
        return LESS;
    else if (d1->key > d2->key)
        return GREATER;
    else
        return EQUAL;
}

void printFunc(const void* data) {
    const MyData* mydata = static_cast<const MyData*>(data);
    cout << mydata->key << " ";
}

void destroyDataFunc(void* data) 
{
	delete static_cast<MyData*>(data);
}

int main()
{
    AvlTree avlTree;

    // �ʱ�ȭ (compare, print, destroy �Լ� ���)
    if (!avlTree.init(compareFunc, printFunc, destroyDataFunc)) {
        std::cout << "1. Initialization failed" << std::endl;
        return 1;
    }
    else
        cout << "1. Initalization successed" << endl;

    // �׽�Ʈ ������ ����
#if defined(LLTEST)
    int testData[] = { 50, 30, 70, 20, 40, 60, 80, 25, 35 };
#elif defined(LRTEST)
    int testData[] = { 50, 30, 70, 20, 40, 10, 25, 60, 80 };
#elif defined(RRTEST)
    int testData[] = { 50, 30, 70, 60, 80, 90, 100, 85, 95 };
#elif defined(RLTEST)
    int testData[] = { 50, 30, 70, 60, 80, 75, 90, 85, 77 };
#else
    int testData[] = { 50, 30, 70, 20, 40, 60, 80, 25, 35 };
#endif
    const int N = sizeof(testData) / sizeof(testData[0]);

	for (int i = 0; i < N; ++i) {
		MyData* data = new MyData{ testData[i] };
		if (avlTree.insert(data) != INSERT_SUCCESS) {
			std::cout << "2. Insert failed for key: " << data->key << std::endl;
			delete data; // �޸� ����
            return 0;
		}
		else 
			std::cout << "Inserted: " << data->key << std::endl;
	}
    cout << "2. Inserting successed" << endl;


    // �˻� �׽�Ʈ
    MyData query1{ 25 };
    MyData* query1ptr = &query1;
    if (avlTree.lookup((const void**)&query1ptr)) {
        std::cout << "3. found 25 in the tree." << std::endl;
    }
    else {
        std::cout << "3. 25 not found." << std::endl;
        return 0;
    }

    // ���� �� �˻� �׽�Ʈ
    MyData query2{ 25 };
    MyData* query2ptr = &query2;
    avlTree.remove((const void*)&query2);
    if (avlTree.lookup((const void**)&query2ptr)) {
        std::cout << "4. found 25 (should not happen)." << std::endl;
        return 0;
    }
    else {
        std::cout << "4. 25 not found after deletion." << std::endl;
    }

    std::cout << "5. Final In-order traversal: ";
    avlTree.printAll();
    std::cout << std::endl;

    // ��ü Ʈ�� ����
    avlTree.destroyTree();
    std::cout << "6. Tree destroyed." << std::endl;

	return 0;
}