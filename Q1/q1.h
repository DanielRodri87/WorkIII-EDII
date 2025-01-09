#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define N_DISCOS 4
#define N_PINOS 3
#define N_CONFIGS 81

void gerarConfiguracoes(int configuracoes[][N_DISCOS]);
void gerarMatrizAdjacente(int configuracoes[N_CONFIGS][N_DISCOS], int matriz[N_CONFIGS][N_CONFIGS]);
void executarDijkstra(int matriz[][N_CONFIGS], int inicio, int fim);
void metrificarTempo(int matriz[][N_CONFIGS]);
