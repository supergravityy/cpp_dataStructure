#pragma once

#include "Set.h"

typedef struct AdjList
{
	void* vertex;
	Set Adjacents;
}typAdjList;

typedef enum
{
	WHITE,	// Not visited
	GRAY,	// Visited but not fully explored
	BLACK	// Fully explored
}typVertexClr;

typedef enum graphType
{
	DIRECTED,
	UNDIRECTED
}typGraphType;