#include "q1.h"

int main() {
    int configuracoes[N_CONFIGS][N_DISCOS];
    int matrizAdj[N_CONFIGS][N_CONFIGS];

    gerarConfiguracoes(configuracoes);
    gerarMatrizAdjacente(configuracoes, matrizAdj);

    int opcao;
    do {
        printf("Escolha uma opção:\n");
        printf("1. Executar Dijkstra\n");
        printf("2. Exibir tempo de execução (100 execuções de Dijkstra)\n");
        printf("3. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                executarDijkstra(matrizAdj, 0, N_CONFIGS - 1);
                break;
            case 2:
                metrificarTempo(matrizAdj);
                break;
            case 3:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}

void gerarConfiguracoes(int configuracoes[][N_DISCOS]) {
    for (int i = 0; i < N_CONFIGS; i++) {
        int temp = i;
        for (int j = 0; j < N_DISCOS; j++) {
            configuracoes[i][j] = temp % N_PINOS + 1; // Cada disco pode estar em 1, 2 ou 3
            temp /= N_PINOS;
        }
    }
}

int movimentoValido(int config1[], int config2[]) {
    int movimentos = 0;
    int discoMovido = -1;
    int valido = 1;

    for (int i = 0; i < N_DISCOS; i++) {
        if (config1[i] != config2[i]) {
            movimentos++;
            if (movimentos > 1) {
                valido = 0;
            }
            discoMovido = i;
        }
    }

    if (movimentos == 0 || movimentos > 1) {
        valido = 0;
    }

    if (valido) {
        int pinoOrigem = config1[discoMovido];
        int pinoDestino = config2[discoMovido];

        for (int i = 0; i < N_DISCOS; i++) {
            if (i != discoMovido) {
                if (config1[i] == pinoOrigem && i < discoMovido) {
                    valido = 0;
                }
                if (config2[i] == pinoDestino && i < discoMovido) {
                    valido = 0;
                }
            }
        }
    }

    return valido;
}

void gerarMatrizAdjacente(int configuracoes[N_CONFIGS][N_DISCOS], int matriz[N_CONFIGS][N_CONFIGS]) {
    for (int i = 0; i < N_CONFIGS; i++) {
        for (int j = 0; j < N_CONFIGS; j++) {
            if (movimentoValido(configuracoes[i], configuracoes[j])) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

void executarDijkstra(int matriz[][N_CONFIGS], int inicio, int fim) {
    int distancias[N_CONFIGS];
    int visitados[N_CONFIGS];

    for (int i = 0; i < N_CONFIGS; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    distancias[inicio] = 0;

    for (int count = 0; count < N_CONFIGS - 1; count++) {
        int u = -1;

        for (int i = 0; i < N_CONFIGS; i++) {
            if (!visitados[i] && (u == -1 || distancias[i] < distancias[u])) {
                u = i;
            }
        }

        visitados[u] = 1;

        for (int v = 0; v < N_CONFIGS; v++) {
            if (!visitados[v] && matriz[u][v] && distancias[u] != INT_MAX &&
                distancias[u] + matriz[u][v] < distancias[v]) {
                distancias[v] = distancias[u] + matriz[u][v];
            }
        }
    }

    printf("Menor caminho de %d para %d: %d\n", inicio, fim, distancias[fim]);
}

void metrificarTempo(int matriz[][N_CONFIGS]) {
    clock_t inicio, fim;
    double tempo;

    inicio = clock();

    for (int i = 0; i < 100; i++) {
        executarDijkstra(matriz, 0, N_CONFIGS - 1);
    }

    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de 100 execuções: %lf ms\n", tempo);
}
