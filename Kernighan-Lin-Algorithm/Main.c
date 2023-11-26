#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "KLGenerator.h"

#define FILE0_NAME "test.mtx"
#define FILE1_NAME "input_graph.mtx"
#define FILE2_NAME "Erdos02.mtx"
#define FILE3_NAME "com-DBLP.mtx"
#define FILE4_NAME "rgg_n_2_20_s0.mtx"

int initialCutSize;
int finalCutSize;

int main(int argc, char **argv) {
    
    if (argc != 3)
    {
        perror("Invalid arguments");
        exit(EXIT_FAILURE);
    }
    char* fileName = argv[1];
    char* option = argv[2];
    struct Graph* graph = GenerateGraphFromFile(fileName);
    if (graph == NULL) 
    {
        perror("Failed to generate graph.");
        exit(EXIT_FAILURE);
    }
    
    //PrintGraph(graph);
    initialCutSize = CalculateCutSize(graph);
    double elapsedTime;
    if (strcmp(option, "a") == 0)
        elapsedTime = RunKLAlgorithmA(graph);
    else if (strcmp(option, "b") == 0)
        elapsedTime = RunKLAlgorithmB(graph);
    else 
    {
        perror("Option is invalid. Expected 'a' or 'b'.");
        exit(EXIT_FAILURE);
    }
    finalCutSize = CalculateCutSize(graph);
    printf("\nInitial Cut Size: %d, Final Cut Size: %d, Elapsed Time %f seconds\n", initialCutSize, finalCutSize, elapsedTime);
    
    DeleteGraph(graph);
    return 0;
}