#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Helper.h"

#ifndef __GRAPH_H__
#define __GRAPH_H__

/**
 * @brief 
 *  ! How to better implement the graph?
 *  ! Currently, graph has the following implementation:
 *  !
 *  ! Graph:
 *  ! Vertex 1: 2, 5, 10
 *  ! Vertex 2: 1, 20
 *  ! ...
 *  ! Vertex n: 
 *  * Each edge is included in both vertices - This is good for time complexity.
 *  * Insertion to list takes O(1) time
 *  ! Search takes O(k) time for size k - improve search
 *  * Each vertex contains the set number (the set they belong to)
 *  ? Should each vertex contain set index as well?
 *  ? Would doubly linked list help in any way?
 *  ? Would sorted list help in any way?
 */

struct ListNode
{
    int neighbour;
    struct ListNode* next;
};

struct List
{
    int set;
    struct ListNode* head;
};

struct Graph
{
    int numberOfVertices;
    struct List* listArray;
};

struct Graph* InitializeGraph(int numberOfVertices);

void AddEdgeToGraph(struct Graph* graph, int vertex1, int vertex2);

void AddNeighbor(struct Graph* graph, int index, int vertex);

// ! Inefficient Method - somehow make it O(1) time? I dont care about memory usage
bool EdgeExists(struct Graph* graph, int vertex1, int vertex2);

int CalculateCutSize(struct Graph* graph);

void PrintGraph(struct Graph* graph);

void DeallocateGraph(struct Graph* graph);

#endif