#include "../header/Heap.h"

/*For reuse*/

#define REALLOCATE_ARR(Arr, byteSize) ((MyAddr **)realloc(Arr, byteSize))
#define GET_PPOS(childPos) (int)(childPos / 2)
#define GET_LCPOS(parentPos) (int)(parentPos * 2 + 1)
#define GET_RCPOS(parentPos) (int)(parentPos * 2 + 2)

void printNode(MyAddr* node, int number)
{
	cout << "Node[" << number << "]" << endl;
	//cout << "ID : " << node->id << endl;
	//cout << "Name : " << node->name << endl;
	cout << "Age : " << node->age << endl;
}

/*Management*/

Heap::Heap(bool (*compareFunc)(int num1, int num2))
{
	this->Heap_init(compareFunc);
}

Heap::~Heap()
{
	this->Heap_destroy();
	this->Heap_init(nullptr);
}

void Heap::Heap_init(bool (*compareFunc)(int num1, int num2))
{
	this->compare = compareFunc;
	this->treeSize = 0;
	this->errCode = NORMAL;
	this->treeArr = nullptr;

	return;
}

void Heap::Heap_destroy()
{
	int idx = 0;

	while (idx != this->treeSize)
	{
		delete treeArr[idx];
		idx++;
	}

	delete[] treeArr;

	return;
}

bool Heap::Heap_insert(MyAddr* data)
{
	bool result = false;
	MyAddr** tempArr = nullptr;
	MyAddr* tempNode = nullptr;
	int insertPos = 0, parentPos = 0;

	tempArr = REALLOCATE_ARR(this->treeArr, (this->treeSize + 1) * sizeof(MyAddr*));

	if (tempArr == nullptr)
	{
		this->errCode = MEMORY_ERR;
	}
	else
	{
		this->treeArr = tempArr;
		insertPos = this->treeSize; // child
		parentPos = GET_PPOS(insertPos);
		this->treeSize++;

		this->treeArr[insertPos] = data; // 배열에 노드 그냥 추가 (아직 heap화 안됨)

		while ((insertPos > 0) &&
			(this->compare(this->treeArr[parentPos]->age, this->treeArr[insertPos]->age) == true)) // (p < c) ? true : false;
		{
			// 현재노드와 부모노드의 내용을 교체 -> (c < p) -> root에 가까워 질수록 오름차순
			tempNode = this->treeArr[parentPos];
			this->treeArr[parentPos] = this->treeArr[insertPos];
			this->treeArr[insertPos] = tempNode;

			// 재 heap 화를 위해 트리의 상위 depth로 이동
			insertPos = parentPos;
			parentPos = GET_PPOS(insertPos);
		}

		result = true;
	}

	return result;
}

bool Heap::Heap_extract(MyAddr** data)
{
	MyAddr* saveNode = nullptr, **tempArr = nullptr, *tempNode = nullptr;
	int insertPos, LchildPos, RchildPos, selectedPos;
	insertPos = LchildPos = RchildPos = selectedPos = 0;
	bool result = false;

	if (this->treeSize == 0)
	{
		result = false;
	}
	else
	{
		*data = this->treeArr[0]; // root 추출

		// 마지막 노드 데이터 임시 저장
		saveNode = this->treeArr[this->treeSize - 1];

		// 힙에 사용된 메모리 조정
		if (this->treeSize - 1 > 0)
		{
			tempArr = REALLOCATE_ARR(this->treeArr, (this->treeSize - 1) * sizeof(MyAddr*));

			if (tempArr == nullptr)
			{
				this->errCode = MEMORY_ERR;
				result = false;
				goto exit;
			}
			else
			{
				this->treeArr = tempArr;
				goto next;
			}
		}
		else // 마지막 노드 추출시
		{
			delete[] this->treeArr;
			this->treeArr = nullptr;
			this->treeSize = 0;

			goto exit;
		}
	}

next:
	this->treeArr[0] = saveNode; // 마지막 노드를 최상위로 복사

	// 최상위 노드의 내용때문에 재 heap 화 -> root에서 말단으로
	insertPos = 0;
	LchildPos = GET_LCPOS(insertPos);
	RchildPos = GET_RCPOS(insertPos);

	while (true)
	{
		// 현재 노드와 바꿀 자식노드 선택
		LchildPos = GET_LCPOS(insertPos);
		RchildPos = GET_RCPOS(insertPos);

		// 왼쪽자식노드와 현재노드(부모위치) 비교
		if ((LchildPos < this->treeSize - 1) &&
			(this->compare(this->treeArr[insertPos]->age, this->treeArr[LchildPos]->age) == true)) // (p < c) ? true : false; 
		{
			selectedPos = LchildPos;
		}
		else
		{
			selectedPos = insertPos;
		}

		// 오른쪽자식노드와 현재노드 비교
		if ((RchildPos < this->treeSize - 1) &&
			(this->compare(this->treeArr[insertPos]->age, this->treeArr[RchildPos]->age) == true)) // (p < c) ? true : false;
		{
			if (this->compare(this->treeArr[selectedPos]->age, this->treeArr[RchildPos]->age)) // (lc < rc) ? true : false;
				selectedPos = RchildPos; // lc < rc 이면 오른쪽 자식노드 선택(우선순위가 더 높음)
			else {
				// do nothing
			}

		}
		else {
			// do nothing
		}

		// selectedPos = insertPos 일 때, 힙의 특성(p > c)이 복구됨
		if (selectedPos == insertPos) // (p < c) 인 부분이 없었음 -> 복구완료
		{
			result = true;
			break;
		}
		else
		{
			// 현재노드와 선택된 노드의 내용을 바꿈
			tempNode = this->treeArr[selectedPos];
			this->treeArr[selectedPos] = this->treeArr[insertPos];
			this->treeArr[insertPos] = tempNode;

			insertPos = selectedPos; // 재 heap 화를 위해 다음 단계로
		}
	}

	this->treeSize--;

exit:
	return result;
}

void Heap::Heap_printAll() // depth를 단위로 노드들을 출력
{
	int depth, startIdx, endIdx, cnt = 0;
	int treeDepth = ceil(log2(this->treeSize + 1)); // depth에 모든 노드가 들어있지 않을수도 있음
	// log(n)에서 n = 0 이 들어갈 수 없음

	if (this->treeSize == 0)
		return;

	for (depth = 0; depth < treeDepth; depth++)
	{
		cout << endl << "depth[" << depth << "] : Data" << endl << endl;

		startIdx = (int)pow(2, depth) - 1;
		endIdx = (int)pow(2, depth + 1) - 1;

		for (; (startIdx < endIdx) && (startIdx < this->treeSize); startIdx++)
		{
			printNode(this->treeArr[startIdx], ++cnt);
			cout << endl;
		}
	}
}

/*Utility*/

int Heap::Heap_getSize()
{
	return this->treeSize;
}

ErrCode Heap::Heap_getErrCode()
{
	return this->errCode;
}