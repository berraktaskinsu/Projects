
#include "Heap.h"

struct Heap* InitializeHeap(int capacity) {
    struct Heap* heap = (struct Heap*) malloc(sizeof(struct Heap));
    heap -> numberOfElements = 0;
    heap -> capacity = capacity;
    heap -> heapArray = (struct HeapArrayElement*) malloc(capacity * sizeof(struct HeapArrayElement));
    for (int index = 0 ; index < capacity ; index++) 
    {
        (heap -> heapArray)[index].isValid = false;
        (heap -> heapArray)[index].vertex = -1;
        (heap -> heapArray)[index].dValue = -1;
    }
    return heap;
}

void AddElementToHeapSet(struct Heap* heap, int vertex) {
    heap -> heapArray[heap -> numberOfElements].isValid = true;
    heap -> heapArray[heap -> numberOfElements].dValue = 0;
    heap -> heapArray[heap -> numberOfElements].vertex = vertex;
    heap -> numberOfElements ++;
}

void Heapify(struct Heap* heap, int index) {
    int n = heap -> numberOfElements;
    int indexOfLargest = index;
    int indexOfLeftChild = 2 * (index + 1) - 1;
    int indexOfRightChild = 2 * (index + 1);
    if (indexOfLeftChild < n && heap -> heapArray[indexOfLeftChild].dValue > heap -> heapArray[index].dValue) {
        indexOfLargest = indexOfLeftChild;
    }
    if (indexOfRightChild < n && heap -> heapArray[indexOfRightChild].dValue > heap -> heapArray[indexOfLargest].dValue) {
        indexOfLargest = indexOfRightChild;
    }
    if (indexOfLargest != index) {
        int tempDValue = heap -> heapArray[index].dValue;
        int tempVertex = heap -> heapArray[index].vertex;
        heap -> heapArray[index].dValue = heap -> heapArray[indexOfLargest].dValue;
        heap -> heapArray[index].vertex = heap -> heapArray[indexOfLargest].vertex;
        heap -> heapArray[indexOfLargest].dValue = tempDValue;
        heap -> heapArray[indexOfLargest].vertex = tempVertex;
        Heapify(heap, indexOfLargest);
    }
}

void BuildHeap(struct Heap* heap) {
    int n = heap -> numberOfElements;
    for (int index = floor((double) n / 2.0) - 1 ; index >= 0 ; index--) {
        Heapify(heap, index);
    }
}

struct HeapArrayElement* ExtractMax(struct Heap* heap) {
    struct HeapArrayElement* maxElement = (struct HeapArrayElement*) malloc(sizeof(struct HeapArrayElement));
    maxElement -> dValue = heap -> heapArray[0].dValue;
    maxElement -> vertex = heap -> heapArray[0].vertex;
    heap -> heapArray[0].dValue = heap -> heapArray[heap -> numberOfElements - 1].dValue;
    heap -> heapArray[0].vertex = heap -> heapArray[heap -> numberOfElements - 1].vertex;
    heap -> heapArray[heap -> numberOfElements - 1].isValid = false;
    heap -> numberOfElements --;
    Heapify(heap, 0);
    return maxElement;
}

struct HeapArrayElement* ExtractMax2(struct Heap* heap) {
    struct HeapArrayElement* maxElement = &heap -> heapArray[0];
    struct HeapArrayElement* current;
    for (int index = 1 ; index < heap -> numberOfElements ; index++) {
        current = &heap -> heapArray[index];
        if (current -> dValue > maxElement -> dValue) {
            maxElement = current;
        }
    }
    current = NULL;
    struct HeapArrayElement* maxReturned = (struct HeapArrayElement*) malloc(sizeof(struct HeapArrayElement));
    maxReturned -> dValue = maxElement -> dValue;
    maxReturned -> vertex = maxElement -> vertex;
    maxElement -> dValue = heap -> heapArray[heap -> numberOfElements - 1].dValue;
    maxElement -> vertex = heap -> heapArray[heap -> numberOfElements - 1].vertex;
    heap -> heapArray[heap -> numberOfElements - 1].isValid = false;
    heap -> numberOfElements--;
    return maxReturned;
}

int FindIndexOfVertex(struct Heap* heap, int vertex) {
    
    for (int index = 0 ; index < heap -> numberOfElements ; index++) {
        if (heap -> heapArray[index].vertex == vertex) {
            return index;
        }
    }
    return -1;
}

void ChangeKeyByValue(struct Heap* heap, int index, int increment) {
    if (increment == 0)
        return;
    if (increment < 0) 
    {
        HeapDecreaseKey(heap, index, heap -> heapArray[index].dValue + increment);
    }
    if (increment > 0) 
    {
        HeapIncreaseKey(heap, index, heap -> heapArray[index].dValue + increment);
    }
    
}

void ChangeKeyByValue2(struct Heap* heap, int index, int increment) {
    int key = heap -> heapArray[index].dValue + increment;
    heap -> heapArray[index].dValue = key;
}

void HeapIncreaseKey(struct Heap* heap, int index, int key) {
    int vertex = heap -> heapArray[index].vertex;
    while (index > 0 && heap -> heapArray[(int) floor(((double)(index - 1)) / 2.0)].dValue < key) {
        heap -> heapArray[index].dValue = heap -> heapArray[(int) floor(((double) index - 1) / 2.0)].dValue;
        heap -> heapArray[index].vertex = heap -> heapArray[(int) floor(((double) index - 1) / 2.0)].vertex;
        index = (int) floor(((double) index - 1) / 2.0);
    }
    heap -> heapArray[index].dValue = key;
    heap -> heapArray[index].vertex = vertex;
}

void HeapDecreaseKey(struct Heap* heap, int index, int key) {
    heap -> heapArray[index].dValue = key;
    Heapify(heap, index);
}

void PrintHeap(struct Heap* heap) {
    for (int index = 0 ; index < heap -> capacity ; index++) 
    {
        printf("Index: %d, Vertex: %d, D: %d, isValid: %s\n", index, (heap -> heapArray)[index].vertex, (int) heap ->heapArray[index].dValue, (heap -> heapArray)[index].isValid ? "true" : "false");
    }
}

void DeallocateHeap(struct Heap* heap) {
    free(heap -> heapArray);
    heap -> heapArray = NULL;
    free(heap);
}