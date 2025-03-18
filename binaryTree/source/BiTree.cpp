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

int BiTree::BiTree_ins_left(BiTreeNode* node, MyAddr* data)
{
    BiTreeNode* newNode = nullptr, **position = nullptr;

    if(node == nullptr)     // decision for insertion pos 
    {
        if(this->treeSize == 0)
            position = &(this->root); // 루트포인터가 가리키는 주소도 변경필요
        else
            return 1;       // access insertion to root at empty situ
    }
    else
    {
        if(node->left != nullptr)
            return 2;       // access insertion to leftNode in leftnode is null
        else
            position = &(node->left);
    }

    newNode = this->BiTree_makeNode();
    if(newNode == nullptr)
        return 3;
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