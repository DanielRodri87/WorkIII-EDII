#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define N_DISCOS 4
#define N_PINOS 3
#define N_CONFIGS 81

void generateConfigurations(int configurations[][N_DISCOS]);
void generateAdjacentMatrix(int configurations[N_CONFIGS][N_DISCOS], int matrix[N_CONFIGS][N_CONFIGS]);
void runDijkstra(int matrix[][N_CONFIGS], int start, int end);
void measureTime(int matrix[][N_CONFIGS]);
