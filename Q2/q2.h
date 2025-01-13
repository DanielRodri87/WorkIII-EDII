#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define NUMBER_DISKS 4
#define NUMBER_PINS 3
#define NUMBER_CONFIGS 81

void generateConfigurations(int configurations[][NUMBER_DISKS], int totalConfigs);
void adjacencyMatrix(int configurations[NUMBER_CONFIGS][NUMBER_DISKS], int matrix[NUMBER_CONFIGS][NUMBER_CONFIGS]);
void bellmanFord(int matrix[][NUMBER_CONFIGS], int startVertex);

void measureExecutionTime(int matrix[][NUMBER_CONFIGS]);