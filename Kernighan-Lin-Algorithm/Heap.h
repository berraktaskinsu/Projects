#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Helper.h"

#ifndef __HEAP_H__
#define __HEAP_H__

struct HeapArrayElement {
    bool isValid;
    int vertex;
    double dValue;
};

struct Heap {
    int numberOfElements;
    int capacity;
    struct HeapArrayElement* heapArray;
};

struct Heap* InitializeHeap(int capacity);

void AddElementToHeapSet(struct Heap* heap, int vertex);

void Heapify(struct Heap* heap, int index);

void BuildHeap(struct Heap* heap);

struct HeapArrayElement* ExtractMax(struct Heap* heap);

struct HeapArrayElement* ExtractMax2(struct Heap* heap);

int FindIndexOfVertex(struct Heap* heap, int vertex);

void ChangeKeyByValue(struct Heap* heap, int index, int increment);

void ChangeKeyByValue2(struct Heap* heap, int index, int increment);

void HeapIncreaseKey(struct Heap* heap, int index, int key);

void HeapDecreaseKey(struct Heap* heap, int index, int key);

void PrintHeap(struct Heap* heap);

void DeallocateHeap(struct Heap* heap);

#endif