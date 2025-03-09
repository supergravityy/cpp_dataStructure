#pragma once

#include "Libs.h"
#include "Data.h"

typedef struct rNode_
{
    MyAddr* data;
    rNode_* nextNode; 
}rNode;

