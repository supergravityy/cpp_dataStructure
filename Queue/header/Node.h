#pragma once

#include "Libs.h"
#include "Node.h"
#include "Data.h"

typedef struct Node_
{
    MyAddr* data;
    Node_* nextNode;
}Node;

