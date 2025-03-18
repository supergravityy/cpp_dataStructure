#pragma once

#include "Libs.h"
#include "Data.h"

typedef struct BitreeNode_
{
    MyAddr* data;
    struct BitreeNode_* left;
    struct BitreeNode_* right;
}BiTreeNode;