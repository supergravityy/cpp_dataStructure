#pragma once

#include "Libs.h"
#include "Data.h"

typedef struct dNode_
{
    MyAddr* data;
    dNode_* nextNode;
    dNode_* prevNode; 
}dNode;

