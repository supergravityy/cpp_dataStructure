#pragma once

#include "Libs.h"

typedef struct BitreeNode_
{
    void* data;
    struct BitreeNode_* left;
    struct BitreeNode_* right;
}typBiTreeNode;