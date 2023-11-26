
#include "KLGenerator.h"
/**
 * @brief Complexity: O(c + e*g) e
 *  c: # of lines of comments
 *  e: # of edges
 *  g: # complexity of AddEdgeToGraph()
 * 
 * @param fileName 
 * @return true 
 * @return false 
 */


double RunKLAlgorithmA(struct Graph* graph) {

    printf("_____________________________________________KL Algorithm A_________________________________________________-\n");
    clock_t timer = clock();
    
    int iteration = 0;
    int gmax;
    do {
        struct Heap** heaps;
        heaps = BuildHeapSetsFromGraph(graph);
        
        iteration++;
        //PrintHeaps(heaps);
        double dValue;
        int vertex, myCount, yourCount;
        for (int setNo = 1 ; setNo < 3 ; setNo++) 
        {
            for (int index = 0 ; index < heaps[setNo - 1] -> numberOfElements ; index++) 
            {
                myCount = 0;
                yourCount = 0;
                vertex = heaps[setNo - 1] -> heapArray[index].vertex;
                struct ListNode* current = graph -> listArray[vertex - 1].head;
                
                while (current != NULL) 
                {
                    if (graph -> listArray[current -> neighbour - 1].set == setNo) 
                    {
                        myCount++;
                    } 
                    else
                    {
                        yourCount++;
                    }
                    current = current -> next;
                }
                dValue = yourCount - myCount;
                //printf("Set No: %d, Vertex: %d, D: %d\n", setNo, vertex, (int)dValue);
                heaps[setNo - 1] -> heapArray[index].dValue = dValue;
            }
        }
        BuildHeap(heaps[0]);
        BuildHeap(heaps[1]);
        
        //printf("\nBefore Extraction:\n");
        //PrintHeaps(heaps);
        struct HeapArrayElement* maxA;
        struct HeapArrayElement* maxB;
        int vertexA, vertexB, dValueA, dValueB, gain;
        int minimumNumberOfElements = (int) fmin((double) heaps[0] -> numberOfElements, (double) heaps[1] -> numberOfElements);

        int* verticesA = (int*) malloc(minimumNumberOfElements * sizeof(int));
        int* verticesB = (int*) malloc(minimumNumberOfElements * sizeof(int));
        int* gains = (int*) malloc(minimumNumberOfElements * sizeof(int));
        for (int index = 0 ; index < minimumNumberOfElements ; index++) 
        {
            maxA = ExtractMax(heaps[0]);
            vertexA = maxA -> vertex;
            dValueA = maxA -> dValue;
            
            maxB = ExtractMax(heaps[1]);
            vertexB = maxB -> vertex;
            dValueB = maxB -> dValue;

            free(maxA);
            free(maxB);
            maxA = NULL;
            maxB = NULL;

            gain = dValueA + dValueB;
            if (EdgeExists(graph, vertexA, vertexB)) 
            {
                gain -= 2;
                
            }
            //printf("\nAfter Extraction:\nVA:%d VB:%d DA:%d DB:%d G:%d\nUpdating D Values - Before:\n", vertexA, vertexB, dValueA, dValueB, gain);
            //PrintHeaps(heaps);
            verticesA[index] = vertexA;
            verticesB[index] = vertexB;
            gains[index] = gain;

            if (heaps[0] -> numberOfElements == 0 || heaps[1] -> numberOfElements == 0) {
                // DO NOT EXTRACT OR UPDATE FURTHER
                // printf("Heaps are empty\n");
                break;
            }

            // UPDATE D VALUES
            // for all neighbours of a and b, dvalue-= 1 or dvalue += 1
            struct ListNode* currentA = graph -> listArray[vertexA - 1].head;
            while (currentA != NULL) {
                int neighbourVertex = currentA -> neighbour;
                int neighbourIndex;
                if (graph -> listArray[neighbourVertex - 1].set == 1) {
                    // same set - neighbour is in heaps[0]
                    neighbourIndex = FindIndexOfVertex(heaps[0], neighbourVertex);
                    if (neighbourIndex != -1) {
                        //printf("**Index of vertex %d in heaps %d is %d\n", neighbourVertex, 0, neighbourIndex);
                        ChangeKeyByValue(heaps[0], neighbourIndex, 2);
                    }
                }
                else if (graph -> listArray[neighbourVertex - 1].set == 2)
                {
                    // neighbour is in heaps[1]
                    neighbourIndex = FindIndexOfVertex(heaps[1], neighbourVertex);
                    if (neighbourIndex != -1) {
                        //printf("**Index of vertex %d in heaps %d is %d\n", neighbourVertex, 1, neighbourIndex);
                        ChangeKeyByValue(heaps[1], neighbourIndex, -2);
                    }
                }
                currentA = currentA -> next;
            }

            struct ListNode* currentB = graph -> listArray[vertexB - 1].head;
            while (currentB != NULL) {
                int neighbourVertex = currentB -> neighbour;
                int neighbourIndex;
                if (graph -> listArray[neighbourVertex - 1].set == 1) {
                    // neighbour is in heaps[0]
                    neighbourIndex = FindIndexOfVertex(heaps[0], neighbourVertex);
                    if (neighbourIndex != -1) {
                        //printf("**Index of vertex %d in heaps %d is %d\n", neighbourVertex, 0, neighbourIndex);
                        ChangeKeyByValue(heaps[0], neighbourIndex, -2);
                    }
                    
                }
                else if (graph -> listArray[neighbourVertex - 1].set == 2)
                {
                    // same set - neighbour is in heaps[1]
                    neighbourIndex = FindIndexOfVertex(heaps[1], neighbourVertex);
                    if (neighbourIndex != -1) {
                        //printf("**Index of vertex %d in heaps %d is %d\n", neighbourVertex, 1, neighbourIndex);
                        ChangeKeyByValue(heaps[1], neighbourIndex, 2);
                    }
                }
                currentB = currentB -> next;
            }

            //printf("\nUpdating D Values - After:\n");
            //PrintHeaps(heaps);
        }
        // find gmax and k
        /*
        printf("\nVertices A: ");
        for (int i = 0 ; i < minimumNumberOfElements ; i ++) {
            printf("%d ",verticesA[i]);
        }
        printf("\n");
        printf("Vertices B: ");
        for (int i = 0 ; i < minimumNumberOfElements ; i ++) {
            printf("%d ",verticesB[i]);
        }
        printf("\n");
        printf("Gains: ");
        for (int i = 0 ; i < minimumNumberOfElements ; i ++) {
            printf("%d ",gains[i]);
        }
        printf("\n");*/
        int k = 0;
        gmax = gains[0];
        int gUntilNow = gmax;
        for (int i = 1 ; i < minimumNumberOfElements ; i++) 
        {
            gUntilNow += gains[i];
            if (gUntilNow > gmax) {
                k = i;
                gmax = gUntilNow;
            }
        }
        printf("Iteration %d- k: %d - gmax: %d\n", iteration, k, gmax);

        if (gmax > 0) {
            //printf("********************************EXCHANGE***********************************\n");
            
            // Switch the subsets (on graph)
            int changedA, changedB;
            for (int index = 0 ; index <= k ; index++) 
            {
                
                changedA = verticesA[index];
                changedB = verticesB[index];
                
                graph -> listArray[changedA - 1].set = 2;
                graph -> listArray[changedB - 1].set = 1;
                
            }
        }

        free(verticesA);
        free(verticesB);
        free(gains);
        verticesA = NULL;
        verticesB = NULL;
        gains = NULL;
        DeleteHeaps(heaps);
        heaps = NULL;
    }
    while (gmax > 0);
    timer = clock() - timer;
    double elapsedTime = ((double)timer) / CLOCKS_PER_SEC;
    printf("_____________________________________________KL Algorithm A_________________________________________________-\n");
    return elapsedTime;
}

double RunKLAlgorithmB(struct Graph* graph) {

    // ! Treat heaps as basic sets
    printf("_____________________________________________KL Algorithm B_________________________________________________-\n");
    clock_t timer = clock();

    int iteration = 0;
    int gmax;
    do {
        struct Heap** heaps;
        heaps = BuildHeapSetsFromGraph(graph);
        iteration++;
        double dValue;
        int vertex, myCount, yourCount;
        for (int setNo = 1 ; setNo < 3 ; setNo++) 
        {
            for (int index = 0 ; index < heaps[setNo - 1] -> numberOfElements ; index++) 
            {
                myCount = 0;
                yourCount = 0;
                vertex = heaps[setNo - 1] -> heapArray[index].vertex;
                struct ListNode* current = graph -> listArray[vertex - 1].head;
                
                while (current != NULL) 
                {
                    if (graph -> listArray[current -> neighbour - 1].set == setNo) 
                    {
                        myCount++;
                    } 
                    else
                    {
                        yourCount++;
                    }
                    current = current -> next;
                }
                dValue = yourCount - myCount;
                heaps[setNo - 1] -> heapArray[index].dValue = dValue;
            }
        }
        struct HeapArrayElement* maxA;
        struct HeapArrayElement* maxB;
        int vertexA, vertexB, dValueA, dValueB, gain;
        int minimumNumberOfElements = (int) fmin((double) heaps[0] -> numberOfElements, (double) heaps[1] -> numberOfElements);

        int* verticesA = (int*) malloc(minimumNumberOfElements * sizeof(int));
        int* verticesB = (int*) malloc(minimumNumberOfElements * sizeof(int));
        int* gains = (int*) malloc(minimumNumberOfElements * sizeof(int));
        for (int index = 0 ; index < minimumNumberOfElements ; index++) 
        {
            // ! Do not use ExtractMax
            maxA = ExtractMax2(heaps[0]);
            vertexA = maxA -> vertex;
            dValueA = maxA -> dValue;
            
            maxB = ExtractMax2(heaps[1]);
            vertexB = maxB -> vertex;
            dValueB = maxB -> dValue;

            free(maxA);
            free(maxB);
            maxA = NULL;
            maxB = NULL;

            gain = dValueA + dValueB;
            if (EdgeExists(graph, vertexA, vertexB)) 
            {
                gain -= 2;
                
            }
            verticesA[index] = vertexA;
            verticesB[index] = vertexB;
            gains[index] = gain;

            if (heaps[0] -> numberOfElements == 0 || heaps[1] -> numberOfElements == 0) {
                break;
            }

            // UPDATE D VALUES
            // for all neighbours of a and b, dvalue-= 1 or dvalue += 1
            struct ListNode* currentA = graph -> listArray[vertexA - 1].head;
            while (currentA != NULL) {
                int neighbourVertex = currentA -> neighbour;
                int neighbourIndex;
                if (graph -> listArray[neighbourVertex - 1].set == 1) {
                    // same set - neighbour is in heaps[0]
                    neighbourIndex = FindIndexOfVertex(heaps[0], neighbourVertex);
                    if (neighbourIndex != -1) {
                        //printf("**Index of vertex %d in heaps %d is %d\n", neighbourVertex, 0, neighbourIndex);
                        // ! Simply update dValue
                        ChangeKeyByValue2(heaps[0], neighbourIndex, 2);
                        //ChangeKeyByValue(heaps[0], neighbourIndex, 2);
                    }
                }
                else if (graph -> listArray[neighbourVertex - 1].set == 2)
                {
                    // neighbour is in heaps[1]
                    neighbourIndex = FindIndexOfVertex(heaps[1], neighbourVertex);
                    if (neighbourIndex != -1) {
                        //printf("**Index of vertex %d in heaps %d is %d\n", neighbourVertex, 1, neighbourIndex);
                        ChangeKeyByValue2(heaps[1], neighbourIndex, -2);
                        //ChangeKeyByValue(heaps[1], neighbourIndex, -2);
                    }
                }
                currentA = currentA -> next;
            }

            struct ListNode* currentB = graph -> listArray[vertexB - 1].head;
            while (currentB != NULL) {
                int neighbourVertex = currentB -> neighbour;
                int neighbourIndex;
                if (graph -> listArray[neighbourVertex - 1].set == 1) {
                    // neighbour is in heaps[0]
                    neighbourIndex = FindIndexOfVertex(heaps[0], neighbourVertex);
                    if (neighbourIndex != -1) {
                        ChangeKeyByValue2(heaps[0], neighbourIndex, -2);
                    }
                    
                }
                else if (graph -> listArray[neighbourVertex - 1].set == 2)
                {
                    // same set - neighbour is in heaps[1]
                    neighbourIndex = FindIndexOfVertex(heaps[1], neighbourVertex);
                    if (neighbourIndex != -1) {
                        ChangeKeyByValue2(heaps[1], neighbourIndex, 2);
                    }
                }
                currentB = currentB -> next;
            }
        }

        int k = 0;
        gmax = gains[0];
        int gUntilNow = gmax;
        for (int i = 1 ; i < minimumNumberOfElements ; i++) 
        {
            gUntilNow += gains[i];
            if (gUntilNow > gmax) {
                k = i;
                gmax = gUntilNow;
            }
        }
        printf("Iteration %d- k: %d - gmax: %d\n", iteration, k, gmax);

        if (gmax > 0) {
            // Switch the subsets (on graph)
            int changedA, changedB;
            for (int index = 0 ; index <= k ; index++) 
            {
                changedA = verticesA[index];
                changedB = verticesB[index];
                
                graph -> listArray[changedA - 1].set = 2;
                graph -> listArray[changedB - 1].set = 1;
            }
        }
        
        free(verticesA);
        free(verticesB);
        free(gains);
        verticesA = NULL;
        verticesB = NULL;
        gains = NULL;
        DeleteHeaps(heaps);
        heaps = NULL;
    }
    while (gmax > 0);
    timer = clock() - timer;
    double elapsedTime = ((double)timer) / CLOCKS_PER_SEC;
    printf("_____________________________________________KL Algorithm B_________________________________________________-\n");
    return elapsedTime;
}

struct Graph* GenerateGraphFromFile(const char* fileName) {
    
    // Open file
    FILE* file; 
    file = fopen(fileName, "r");
    if (file == NULL) 
    {
        perror("Can not open file");
        exit(EXIT_FAILURE);
    }

    struct Graph* graph = NULL;

    // Skip Until First Line
    char* line = NULL;
    long unsigned int size = 0;
    int bytesRead;

    while (true)
    {
        bytesRead = getline(&line, &size, file);
        if (bytesRead == -1) 
        {
            perror("Input file has no data");
            exit(EXIT_FAILURE);
        }
        if (isdigit(line[0])) 
        {
            // Process First Line
            int numberOfVertices, numberOfEdges;
            sscanf(line, "%d %d %d", &numberOfVertices, &numberOfVertices, &numberOfEdges);
            
            graph = InitializeGraph(numberOfVertices);
            // Process Rest of File
            int vertex1, vertex2;
            while (getline(&line, &size, file) != -1) 
            {
                sscanf(line, "%d %d", &vertex1, &vertex2);
                //printf("(%d, %d) ", vertex1, vertex2);
                // Add Edge to Graph
                AddEdgeToGraph(graph, vertex1, vertex2);
            }
            break;
        }
    } 

    // Finish Up
    free(line);
    fclose(file);
    return graph;
}

/*struct Heap** BuildHeapSetsFromGraph(struct Graph* graph) {
    int numberOfVertices1 = ceil(((double) (graph -> numberOfVertices)) / 2.0);
    int numberOfVertices2 = floor(((double) (graph -> numberOfVertices)) / 2.0);
    //int capacity1 = FindNearestPowerOfTwo(numberOfVertices1);
    //int capacity2 = FindNearestPowerOfTwo(numberOfVertices2);
    struct Heap** heapSets = malloc(2 * sizeof(struct Heap*));
    heapSets[0] = InitializeHeap(numberOfVertices1);
    heapSets[1] = InitializeHeap(numberOfVertices2);

    int index;
    for (index = 0 ; index < numberOfVertices1 ; index++) {
        AddElementToHeapSet(heapSets[0], index + 1);
        graph -> listArray[index].set = 1;
    }
    for ( ; index < numberOfVertices1 + numberOfVertices2 ; index++) {
        AddElementToHeapSet(heapSets[1], index + 1);
        graph -> listArray[index].set = 2;
    }
    return heapSets;
}*/


struct Heap** BuildHeapSetsFromGraph(struct Graph* graph) {
    int numberOfVertices1 = ceil(((double) (graph -> numberOfVertices)) / 2.0);
    int numberOfVertices2 = floor(((double) (graph -> numberOfVertices)) / 2.0);
    //int capacity1 = FindNearestPowerOfTwo(numberOfVertices1);
    //int capacity2 = FindNearestPowerOfTwo(numberOfVertices2);
    struct Heap** heapSets = malloc(2 * sizeof(struct Heap*));
    heapSets[0] = InitializeHeap(numberOfVertices1);
    heapSets[1] = InitializeHeap(numberOfVertices2);

    for (int index = 0 ; index < graph -> numberOfVertices ; index++) 
    {
        int set = graph -> listArray[index].set; // 1 or 2
        //printf("Set: %d\n", set);
        AddElementToHeapSet(heapSets[set - 1], index + 1);
    }
    
    return heapSets;
}

void PrintHeaps(struct Heap** heaps) {
    printf("Heap 1:\n");
    PrintHeap(heaps[0]);
    printf("Heap 2:\n");
    PrintHeap(heaps[1]);
}

void DeleteGraph(struct Graph* graph) {
    DeallocateGraph(graph);
}

void DeleteHeaps(struct Heap** heaps) {
    DeleteHeap(heaps[0]);
    DeleteHeap(heaps[1]);
    heaps[0] = NULL;
    heaps[1] = NULL;
    free(heaps);
}

void DeleteHeap(struct Heap* heap) {
    DeallocateHeap(heap);
}