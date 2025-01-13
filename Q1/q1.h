#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define NUMBER_DISKS 4
#define NUMBER_PINS 3
#define NUMBER_CONFIGS 81

void generateConfigurations(int configurations[][NUMBER_DISKS]);
void generateAdjacentMatrix(int configurations[NUMBER_CONFIGS][NUMBER_DISKS], int matrix[NUMBER_CONFIGS][NUMBER_CONFIGS]);
void runDijkstra(int matrix[][NUMBER_CONFIGS], int start, int end);
void measureTime(int matrix[][NUMBER_CONFIGS]);
