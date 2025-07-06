#pragma once

#include "../header/Libs.h"

typedef struct BitreeNode_
{
    void* data;
    struct BitreeNode_* left;
    struct BitreeNode_* right;
}typBiTreeNode;