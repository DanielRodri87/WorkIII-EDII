#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_VERTICES 10
#define RAND_PATH 201

typedef struct graph
{
    int vertices[NUM_VERTICES];
    float edges[NUM_VERTICES][NUM_VERTICES];
} Graph;

typedef struct
{
    int id;
    float probability;
    int predecessor;
} Distance;

void displayGraph(Graph graph);
void initializeGraph(Graph *graph);
void generateGraph(Graph *graph);
Distance *runDijkstra(int start, Graph graph);
void findShortestPath(int start, int end, Distance *distances);