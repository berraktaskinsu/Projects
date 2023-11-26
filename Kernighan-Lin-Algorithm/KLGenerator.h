#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "Graph.h"
#include "Heap.h"

#ifndef __KLGENERATOR_H__
#define __KLGENERATOR_H__

double RunKLAlgorithmA(struct Graph* graph);

double RunKLAlgorithmB(struct Graph* graph);

struct Graph* GenerateGraphFromFile(const char* fileName);

struct Heap** BuildHeapSetsFromGraph(struct Graph* graph);

//struct Heap** ReBuildHeapSetsFromGraph(struct Graph* graph);

void PrintHeaps(struct Heap** heaps);

void DeleteGraph(struct Graph* graph);

void DeleteHeaps(struct Heap** heaps);

void DeleteHeap(struct Heap* heap);

#endif