#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define N_DISCS 4
#define N_PEGS 3
#define N_CONFIGS 81

void generateConfigurations(int configurations[][N_DISCS], int totalConfigs);
void adjacencyMatrix(int configurations[N_CONFIGS][N_DISCS], int matrix[N_CONFIGS][N_CONFIGS]);
void bellmanFord(int matrix[][N_CONFIGS], int startVertex, int endVertex);
void measureExecutionTime(int matrix[][N_CONFIGS]);