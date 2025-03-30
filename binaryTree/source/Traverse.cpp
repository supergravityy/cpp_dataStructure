#include "../header/BiTree.h"

bool BiTree::BiTree_preOrder_find(BiTreeNode *node, MyAddr* tgt)
{
    if(node == nullptr || tgt == nullptr)
        return false;

    else
    {
        // 전위순회 : root -> left -> right
        if(!strcmp(node->data->id, tgt->id)) 
            return true;
        
        if(BiTree_preOrder_find(node->left, tgt))
            return true;
        
        return BiTree_preOrder_find(node->right, tgt);
    }
}

bool BiTree::BiTree_inOrder_find(BiTreeNode *node, MyAddr* tgt)
{
    if(node == nullptr || tgt == nullptr)
        return false;
        
    else
    {
        // 중위순회 : left -> root -> right
        if(BiTree_inOrder_find(node->left, tgt))
            return true;

        if(!strcmp(node->data->id, tgt->id)) 
            return true;
        
        return BiTree_inOrder_find(node->right, tgt);
    }
}

bool BiTree::BiTree_postOrder_find(BiTreeNode *node, MyAddr* tgt)
{
    if(node == nullptr || tgt == nullptr)
        return false;
        
    else
    {
        // 중위순회 : left -> right -> root
        if(BiTree_postOrder_find(node->left, tgt))
            return true;

        if(BiTree_postOrder_find(node->right, tgt)) 
            return true;
        
        return !strcmp(node->data->id, tgt->id);
    }
}