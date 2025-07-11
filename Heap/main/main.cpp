#include <vector>
#include <set>
#include <ctime>
#include <algorithm>
#include "../header/heap.h"

using namespace std;

typedef struct {
	int id;   // 식별자
	int key;  // 우선순위 기준 값
} TestData;

// 메모리 해제
void destroyTestData(void* data) {
	delete (TestData*)data;
}

// 출력 함수
void printTestData(void* data) {
	TestData* t = (TestData*)data;
	cout << "[ID: " << t->id << ", Key: " << t->key << "]" << endl;
}

// 최대 힙 비교 함수
typCmpResult compareMax(const void* a, const void* b) {
	// a-b
	int keyA = ((TestData*)a)->key;
	int keyB = ((TestData*)b)->key;

	if (keyA > keyB) return GREATER;
	else if (keyA < keyB) return LESS;
	else return EQUAL;
}

// 최소 힙 비교 함수
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

	set<int> uniqueKeys;       // 중복 방지용
	vector<int> keysVec;       // STL 비교용

	cout << "==== 중복 없는 100개 삽입 ====" << endl;

	while ((int)uniqueKeys.size() < 100) {
		int val = (rand() % 512) - 256;
		if (uniqueKeys.insert(val).second) { // 새로 삽입된 경우만 진행
			keysVec.push_back(val);
			TestData* d1 = new TestData{ (int)uniqueKeys.size(), val };
			TestData* d2 = new TestData{ (int)uniqueKeys.size(), val };
			maxHeap.insert(d1);
			minHeap.insert(d2);
		}
	}

	// STL 기반 max/min 확인
	int stlMax = *max_element(keysVec.begin(), keysVec.end());
	int stlMin = *min_element(keysVec.begin(), keysVec.end());

	TestData* maxPeek = (TestData*)maxHeap.peek();
	TestData* minPeek = (TestData*)minHeap.peek();

	cout << "\n==== peek() 테스트 ====" << endl;
	cout << "[Max Heap] STL max = " << stlMax << ", Heap.peek = " << maxPeek->key << ", 결과 : " << ((stlMax == maxPeek->key) ? "true" : "false") << endl;
	cout << "[Min Heap] STL min = " << stlMin << ", Heap.peek = " << minPeek->key << ", 결과 : " << ((stlMin == minPeek->key) ? "true" : "false") << endl;

	void* maxExtracted = nullptr;
	void* minExtracted = nullptr;

	for (int i = 0; i < 3; i++)
	{
		// STL에서 max/min 제거 → 현재 벡터에서 2순위 추출
		stlMax = *max_element(keysVec.begin(), keysVec.end());
		stlMin = *min_element(keysVec.begin(), keysVec.end());

		keysVec.erase(remove(keysVec.begin(), keysVec.end(), stlMax), keysVec.end());
		keysVec.erase(remove(keysVec.begin(), keysVec.end(), stlMin), keysVec.end());

		int nextMax = *max_element(keysVec.begin(), keysVec.end());
		int nextMin = *min_element(keysVec.begin(), keysVec.end());

		maxHeap.extract(&maxExtracted);
		minHeap.extract(&minExtracted);

		printf("\n==== %d번째 extract() 후 테스트 ====\n", i + 1);
		TestData* maxPeek2 = (TestData*)maxHeap.peek();
		TestData* minPeek2 = (TestData*)minHeap.peek();

		cout << "[Max Heap] STL 2nd max = " << nextMax << ", Heap.peek = " << maxPeek2->key << ", 결과 : " << ((nextMax == maxPeek2->key) ? "true" : "false") << endl;
		cout << "[Min Heap] STL 2nd min = " << nextMin << ", Heap.peek = " << minPeek2->key << ", 결과 : " << ((nextMin == minPeek2->key) ? "true" : "false") << endl;
	}

	destroyTestData(maxExtracted);
	destroyTestData(minExtracted);

	return 0;
}
