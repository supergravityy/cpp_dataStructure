#pragma once

#include "bitreeNode.h"

typedef enum eBalFactor
{
	AVL_LEFT_HEAVY = 1,
	AVL_BALANCED = 0,
	AVL_RIGHT_HEAVY = -1
}typBalFactor;

typedef enum eHiddenFlag
{
	NODE_AVAILABLE = 0,
	NODE_HIDDEN = 1
}typHiddenFlag;

typedef enum eNodeBalancedFlag
{
	AVLNODE_UNBALANCED = 0,
	AVLNODE_BALANCED = 1
}typBalancedFlag;

typedef struct AvlTreeNode : public typBiTreeNode
{
	typBalFactor balFactor;
	typHiddenFlag hiddenFlag;
} typAvlTreeNode;