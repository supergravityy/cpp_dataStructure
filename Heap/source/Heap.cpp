#include "../header/Heap.h"

#define REALLOCATE_ARR(Arr, byteSize) ((MyAddr **)realloc(Arr, byteSize))
#define GET_PPOS(childPos) (int)(childPos / 2)
#define GET_LCPOS(parentPos) (int)(parentPos * 2 + 1)
#define GET_RCPOS(parentPos) (int)(parentPos * 2 + 2)

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

bool Heap::Heap_insert(MyAddr *data)
{
    bool result = false;
    MyAddr **tempArr = nullptr;
    MyAddr *tempNode = nullptr;
    int insertPos = 0, parentPos = 0;

    tempArr = REALLOCATE_ARR(this->treeArr, (this->treeSize + 1) * sizeof(MyAddr*));

    if (tempArr == nullptr)
    {
        this->errCode = MEMORY_ERR;
    }
    else
    {
        this->treeArr = tempArr;
        insertPos = this->treeSize;
        parentPos = GET_PPOS(insertPos);
        this->treeSize++;

        memcpy(this->treeArr[insertPos], data, sizeof(MyAddr)); // 배열에 노드 그냥 추가 (아직 heap화 안됨)

        while ((insertPos > 0) && 
        (this->compare(treeArr[parentPos]->age, treeArr[insertPos]->age) == true))
        {
            // 현재노드와 부모노드의 내용을 교체
            tempNode = this->treeArr[parentPos];
            this->treeArr[parentPos] = this->treeArr[insertPos];
            this->treeArr[insertPos] = tempNode;

            // 재 heap 화를 위해 트리의 윗단계로 이동
            insertPos = parentPos;
            parentPos = GET_PPOS(insertPos);
        }

        result = true;
    }

    return result;
}

bool Heap::Heap_extract(MyAddr **data)
{
    MyAddr *saveNode = nullptr, **tempArr = nullptr, *tempNode = nullptr;
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
                this->treeSize--;
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

    // 최상위 노드의 내용때문에 재 heap 화
    LchildPos = GET_LCPOS(insertPos);
    RchildPos = GET_RCPOS(insertPos);

    while (true)
    {
        // 현재 노드와 바꿀 자식노드 선택
        LchildPos = GET_LCPOS(insertPos);
        RchildPos = GET_RCPOS(insertPos);
        
        // 왼쪽자식노드와 현재노드 비교
        if((LchildPos < this->treeSize) && 
        (this->compare(treeArr[LchildPos]->age, treeArr[insertPos]->age) == true))
        {
            selectedPos = LchildPos;
        }
        else
        {
            selectedPos = insertPos;
        }

        // 오른쪽자식노드와 현재노드 비교
        if((RchildPos < this->treeSize) && 
        (this->compare(treeArr[RchildPos]->age, treeArr[insertPos]->age) == true))
        {
            selectedPos = RchildPos;
        }
        else{
            // do nothing
        }

        // mPos = insertPos 일 때, 힙의 특성이 복구됨
        if(selectedPos == insertPos) 
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

exit:
    return result;
}

/*Utility*/

int Heap::Heap_getSize()
{
    return this->treeSize;
}