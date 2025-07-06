#pragma once

#include "../header/bitreeNode.h"

#define DEBUG

#define INSERT_SUCCESS          0
#define INSERT_FAILED           1
#define INSERT_CHILD_EXISTS     2
#define INSERT_MEMORY_ERR       3

typedef enum ErrCode
{
    NORMAL = 0,
    MEMORY_ERR,
    SYS_FAULT
}typErrcode;

typedef enum compareResult
{
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
}typCmpResult;

class BiTree
{
public:
    /*Manangement*/
    int insert_leftChild(void* node, const void* data);
	int insert_rightChild(void* node, const void* data);
	bool remove_leftChild(void* node);
	bool remove_rightChild(void* node);
    bool mergeTree(void* leftTree, void* rightTree, void* data);
    virtual void printAll();
    virtual bool lookup(void** node);

    /*Utility*/
    BiTree();
    virtual ~BiTree();

    virtual bool init(typCmpResult (*compareFunc)(const void* key1, const void* key2)
        , void (*printFunc)(void* node)
        , void (*destroyDataFunc)(void* data)
        , void* (*traverseFunc)(void* node, void** saveData));
    int get_Size();
    int get_maxHeight();
	typErrcode get_ErrCode();

#ifdef DEBUG
    typBiTreeNode* get_bitreeRoot_Addr();
    typBiTreeNode* get_leftAddr(void* node);
    typBiTreeNode* get_rightAddr(void* node);
#endif // DEBUG

protected:
	/*Utility-1*/
    virtual void initNode(void* node, void* data);
    virtual bool makeNode(void** node);
    virtual bool deleteNode(void** node);
    virtual void destroyTree();
    virtual int insert_left(void* node, const void* data);
    virtual int insert_right(void* node, const void* data);
    virtual bool remove_left(void* node);
    virtual bool remove_right(void* node);
    virtual bool merge(void* leftTree, void* rightTree, void* data);
    int cal_maxHeight(void* node);

    /*Accessors*/
    typBiTreeNode* get_BiTreeRoot();
    bool is_emptyNode(void* node);
    virtual bool is_leafNode(void* node);
    virtual void set_leftPtr(void* tgtNode, void* tgtAddr);
	virtual void set_rightPtr(void* tgtNode, void* tgtAddr);
	virtual void* get_leftPtr(void* node);
	virtual void* get_rightPtr(void* node);
	virtual void set_data(void* node, void* data);
    virtual void* get_data(void* node);

    /*Variance*/
    int treeSize = 0;
    typCmpResult (*compareFunc)(const void* key1, const void* key2) = nullptr;
    void (*printTreeFunc)(void* node) = nullptr;
    void (*destroyDataFunc)(void* data) = nullptr;
    void* (*traverseFunc)(void* node, void** saveData) = nullptr;
    typErrcode errCode = NORMAL;

private:
    /*Private*/
    typBiTreeNode* BiTreeRoot = nullptr;
};

// 리팩토링 문서

// 1. 내부 함수포인터 변수 traverse 추가 -> 어떤 방식으로 traverse가 되는지를 선택가능
// 2. 메서드 traverse 모두 삭제 -> 따로 네임스페이스를 만들어서 거기서 정의
// 3. init 메서드에서 traverse 함수주소도 가져가게끔 추가
// 4. traverse를 이용한 lookup 메서드 작성 필요
// 5. printAll에서 내부 traverse 부분도 재작성 필요