#include <vector>
#include <set>
#include <ctime>
#include <algorithm>
#include "../header/heap.h"

using namespace std;

typedef struct {
	int id;   // �ĺ���
	int key;  // �켱���� ���� ��
} TestData;

// �޸� ����
void destroyTestData(void* data) {
	delete (TestData*)data;
}

// ��� �Լ�
void printTestData(void* data) {
	TestData* t = (TestData*)data;
	cout << "[ID: " << t->id << ", Key: " << t->key << "]" << endl;
}

// �ִ� �� �� �Լ�
typCmpResult compareMax(const void* a, const void* b) {
	// a-b
	int keyA = ((TestData*)a)->key;
	int keyB = ((TestData*)b)->key;

	if (keyA > keyB) return GREATER;
	else if (keyA < keyB) return LESS;
	else return EQUAL;
}

// �ּ� �� �� �Լ�
typCmpResult compareMin(const void* a, const void* b) {
	// b-a
	int keyA = ((TestData*)a)->key;
	int keyB = ((TestData*)b)->key;

	if (keyA < keyB) return GREATER;
	else if (keyA > keyB) return LESS;
	else return EQUAL;
}

int main()
{
	Heap maxHeap, minHeap;
	maxHeap.init(compareMax, destroyTestData, printTestData);
	minHeap.init(compareMin, destroyTestData, printTestData);

	set<int> uniqueKeys;       // �ߺ� ������
	vector<int> keysVec;       // STL �񱳿�

	cout << "==== �ߺ� ���� 100�� ���� ====" << endl;

	while ((int)uniqueKeys.size() < 100) {
		int val = (rand() % 512) - 256;
		if (uniqueKeys.insert(val).second) { // ���� ���Ե� ��츸 ����
			keysVec.push_back(val);
			TestData* d1 = new TestData{ (int)uniqueKeys.size(), val };
			TestData* d2 = new TestData{ (int)uniqueKeys.size(), val };
			maxHeap.insert(d1);
			minHeap.insert(d2);
		}
	}

	// STL ��� max/min Ȯ��
	int stlMax = *max_element(keysVec.begin(), keysVec.end());
	int stlMin = *min_element(keysVec.begin(), keysVec.end());

	TestData* maxPeek = (TestData*)maxHeap.peek();
	TestData* minPeek = (TestData*)minHeap.peek();

	cout << "\n==== peek() �׽�Ʈ ====" << endl;
	cout << "[Max Heap] STL max = " << stlMax << ", Heap.peek = " << maxPeek->key << ", ��� : " << ((stlMax == maxPeek->key) ? "true" : "false") << endl;
	cout << "[Min Heap] STL min = " << stlMin << ", Heap.peek = " << minPeek->key << ", ��� : " << ((stlMin == minPeek->key) ? "true" : "false") << endl;

	void* maxExtracted = nullptr;
	void* minExtracted = nullptr;

	for (int i = 0; i < 3; i++)
	{
		// STL���� max/min ���� �� ���� ���Ϳ��� 2���� ����
		stlMax = *max_element(keysVec.begin(), keysVec.end());
		stlMin = *min_element(keysVec.begin(), keysVec.end());

		keysVec.erase(remove(keysVec.begin(), keysVec.end(), stlMax), keysVec.end());
		keysVec.erase(remove(keysVec.begin(), keysVec.end(), stlMin), keysVec.end());

		int nextMax = *max_element(keysVec.begin(), keysVec.end());
		int nextMin = *min_element(keysVec.begin(), keysVec.end());

		maxHeap.extract(&maxExtracted);
		minHeap.extract(&minExtracted);

		printf("\n==== %d��° extract() �� �׽�Ʈ ====\n", i + 1);
		TestData* maxPeek2 = (TestData*)maxHeap.peek();
		TestData* minPeek2 = (TestData*)minHeap.peek();

		cout << "[Max Heap] STL 2nd max = " << nextMax << ", Heap.peek = " << maxPeek2->key << ", ��� : " << ((nextMax == maxPeek2->key) ? "true" : "false") << endl;
		cout << "[Min Heap] STL 2nd min = " << nextMin << ", Heap.peek = " << minPeek2->key << ", ��� : " << ((nextMin == minPeek2->key) ? "true" : "false") << endl;
	}

	destroyTestData(maxExtracted);
	destroyTestData(minExtracted);

	return 0;
}
