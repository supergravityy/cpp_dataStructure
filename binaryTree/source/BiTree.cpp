#include "../header/BiTree.h"

BiTree::BiTree()
{
    this->treeSize = 0;
    this->root = nullptr;
}

BiTree::~BiTree()
{
    this->BiTree_init();
}

/*Management*/

void BiTree::BiTree_init()
{
    this->BiTree_rem_left(nullptr);
}

int BiTree::BiTree_ins_left(BiTreeNode *node, MyAddr *data)
// 0 : normal, 1 : cannot insert to root, 2 : leftptr is not null, 3 : memErr
{
    BiTreeNode *newNode = nullptr, **position = nullptr;

    if (node == nullptr) // decision for insertion pos
    {
        if (this->treeSize == 0)
            position = &(this->root); // 루트포인터가 가리키는 주소도 변경필요
        else
            return 1; // access insertion to root at empty situ
    }
    else
    {
        if (node->left != nullptr)
            return 2; // access insertion to leftNode in leftnode is not null
        else
            position = &(node->left);
    }

    newNode = this->BiTree_makeNode();
    if (newNode == nullptr)
    {
        this->errCode = MEMORY_ERR;
        return 3;
    }
    else
    {
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;

        *position = newNode; // write newNode's memAddr to tgtNode

        this->treeSize++;

        return 0;
    }
}

int BiTree::BiTree_ins_right(BiTreeNode *node, MyAddr *data)
// 0 : normal, 1 : cannot insert to root, 2 : leftptr is not null, 3 : memErr
{
    BiTreeNode *newNode = nullptr, **position = nullptr;

    if (node == nullptr)
    {
        if (this->treeSize == 0)
            position = &(this->root);
        else
            return 1;
    }
    else
    {
        if (node->right != nullptr)
            return 2;
        else
            position = &(node->right);
    }

    newNode = this->BiTree_makeNode();
    if (newNode == nullptr)
    {
        this->errCode = MEMORY_ERR;
        return 3;
    }
    else
    {
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;

        *position = newNode;

        this->treeSize++;

        return 0;
    }
}

bool BiTree::BiTree_rem_left(BiTreeNode *node)
{
    BiTreeNode **position = nullptr;
    bool result = false;

    if (this->treeSize == 0)
        return result;
    else
    {
        if (node == nullptr)
            position = &(this->root);
        else
            position = &(node->left);
    }

    if (*position != nullptr)
    {
        this->BiTree_rem_left(*position);
        this->BiTree_rem_right(*position);

        delete (*position)->data;
        delete *position;
        *position = nullptr;

        this->treeSize--;
        result = true;
    }

    return result;
}

bool BiTree::BiTree_rem_right(BiTreeNode *node)
{
    BiTreeNode **position = nullptr;
    bool result = false;

    if (this->treeSize == 0)
        return result;
    else
    {
        if (node == nullptr)
            position = &(this->root);
        else
            position = &(node->right);
    }

    if (*position != nullptr)
    {
        this->BiTree_rem_left(*position);
        this->BiTree_rem_right(*position);

        delete (*position)->data;
        delete *position;
        *position = nullptr;

        this->treeSize--;
        result = true;
    }

    return result;
}

bool BiTree::BiTree_merge(BiTree *leftTree, BiTree *rightTree, MyAddr *data)
{
    BiTreeNode *temp = nullptr;

    // 1. insert data in
    if (this->BiTree_ins_left(nullptr, data) != 0)
    {
        this->BiTree_init();
        return false;
    }

    // 2. merge Trees by single Tree
    temp = this->root;
    temp->left = leftTree->root;
    temp->right = rightTree->root;

    // 3. modify mergeTree's size
    this->treeSize += leftTree->treeSize + rightTree->treeSize;

    // 4. inhibit access of original Trees to newMerge Tree
    leftTree->root = nullptr;
    leftTree->treeSize = 0;

    rightTree->root = nullptr;
    rightTree->treeSize = 0;

    return true;
}

void BiTree::preOrderPrint(BiTreeNode* node)
{
    if (node == nullptr)
        return;

    // 현재 노드 출력
    cout << "[PreOrder] "
         << "ID: "    << node->data->id   << ", "
         << "Name: "  << node->data->name << ", "
         << "Phone: " << node->data->phone << endl;

    preOrderPrint(node->left);
    preOrderPrint(node->right);
}


void BiTree::BiTree_printAll()
{
    if (this->treeSize == 0 || this->root == nullptr)
        return;

    // 재귀 함수 호출
    preOrderPrint(this->root);
}

/*Utility*/
int BiTree::BiTree_getSize()
{
    return this->treeSize;
}
void BiTree::BiTree_setSize(int size)
{
    this->treeSize = size;
}
ErrCode BiTree::BiTree_getErrCode()
{
    return this->errCode;
}
bool BiTree::BiTree_cmpData(const char *key1, const char *key2)
{
    return !(strcmp(key1, key2));
}
BiTreeNode *BiTree::BiTree_makeNode()
{
    BiTreeNode *newNode = nullptr;

    newNode = new BiTreeNode;

    return newNode;
}