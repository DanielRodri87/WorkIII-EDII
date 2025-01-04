#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

void generateConfigurations(int **configurations, int totalSettings, int numDisks, int numPins);
void adjacentMatrix(int **configurations, int **matrix, int numSettings, int numDisks);
int avaliableMoviment(int *settings1, int *settings2, int numDisks);
void dijkstraAlgorithm(int **matrix, int numSettings, int startVerticies, int endVerticies);
void measureTime(int **matrix, int numSettings);

int main()
{
    int numDisks, numPins;

    printf("============================\n");
    printf("      Torres de Hanoi      \n");
    printf("============================\n");

    printf("Digite o número de discos: ");
    scanf("%d", &numDisks);

    printf("Digite o número de pinos: ");
    scanf("%d", &numPins);

    if (numDisks <= 0 || numPins <= 0)
        printf("Erro: Número de discos e pinos deve ser maior que 0.\n");
    else
    {

        int numSettings = 1;
        for (int i = 0; i < numDisks; i++)
            numSettings *= numPins;

        int **configurations = (int **)malloc(numSettings * sizeof(int *));
        for (int i = 0; i < numSettings; i++)
            configurations[i] = (int *)malloc(numDisks * sizeof(int));

        int **adjacenteMatrix = (int **)malloc(numSettings * sizeof(int *));
        for (int i = 0; i < numSettings; i++)
            adjacenteMatrix[i] = (int *)calloc(numSettings, sizeof(int));

        printf("\nGerando configurações e matrix de adjacência...\n");

        generateConfigurations(configurations, numSettings, numDisks, numPins);
        adjacentMatrix(configurations, adjacenteMatrix, numSettings, numDisks);

        int opcao;

        do
        {
            printf("\nMenu:\n");
            printf("1. Executar algoritmo Dijkstra\n");
            printf("2. Medir tempo de execução do algoritmo Dijkstra (1000 vezes)\n");
            printf("3. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
            {
                int startVerticies, endVerticies;
                printf("Digite o índice de início (0 a %d): ", numSettings - 1);
                scanf("%d", &startVerticies);

                printf("Digite o índice de destino (0 a %d): ", numSettings - 1);
                scanf("%d", &endVerticies);

                if (startVerticies >= 0 && startVerticies < numSettings &&
                    endVerticies >= 0 && endVerticies < numSettings)
                    dijkstraAlgorithm(adjacenteMatrix, numSettings, startVerticies, endVerticies);
                else
                    printf("Índices inválidos.\n");
                break;
            }
            case 2:
                measureTime(adjacenteMatrix, numSettings);
                break;
            case 3:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
            }

        } while (opcao != 3);

        for (int i = 0; i < numSettings; i++)
        {
            free(configurations[i]);
            free(adjacenteMatrix[i]);
        }
        free(configurations);
        free(adjacenteMatrix);
    }

    return 0;
}

void generateConfigurations(int **configurations, int totalSettings, int numDisks, int numPins)
{
    for (int i = 0; i < totalSettings; i++)
    {
        int temp = i;
        for (int j = 0; j < numDisks; j++)
        {
            configurations[i][j] = temp % numPins + 1;
            temp /= numPins;
        }
    }
}

int avaliableMoviment(int *settings1, int *settings2, int numDisks)
{
    int movementes = 0;
    int movedDisk = -1;
    int valid = 1;

    for (int i = 0; i < numDisks; i++)
    {
        if (settings1[i] != settings2[i])
        {
            movementes++;
            if (movementes > 1)
                valid = 0;
            movedDisk = i;
        }
    }

    if (movementes == 0 || movementes > 1)
        valid = 0;

    if (valid)
    {
        int originPin = settings1[movedDisk];
        int destinationPin = settings2[movedDisk];

        for (int i = 0; i < numDisks; i++)
        {
            if (i != movedDisk)
            {
                if (settings1[i] == originPin && i < movedDisk)
                    valid = 0;
                if (settings2[i] == destinationPin && i < movedDisk)
                    valid = 0;
            }
        }
    }

    return valid;
}

void adjacentMatrix(int **configurations, int **matrix, int numSettings, int numDisks)
{
    for (int li = 0; li < numSettings; li++)
    {
        for (int col = 0; col < numSettings; col++)
        {
            if (avaliableMoviment(configurations[li], configurations[col], numDisks))
                matrix[li][col] = 1;
            else
                matrix[li][col] = 0;
        }
    }
}

void dijkstraAlgorithm(int **matrix, int numSettings, int startVerticies, int endVerticies)
{
    int *distances = (int *)malloc(numSettings * sizeof(int));
    int *visited = (int *)calloc(numSettings, sizeof(int));

    for (int i = 0; i < numSettings; i++)
        distances[i] = INT_MAX;

    distances[startVerticies] = 0;

    for (int count = 0; count < numSettings - 1; count++)
    {
        int u = -1;

        for (int i = 0; i < numSettings; i++)
        {
            if (!visited[i] && (u == -1 || distances[i] < distances[u]))
                u = i;
        }

        visited[u] = 1;

        for (int v = 0; v < numSettings; v++)
        {
            if (!visited[v] && matrix[u][v] && distances[u] != INT_MAX &&
                distances[u] + matrix[u][v] < distances[v])
                distances[v] = distances[u] + matrix[u][v];
        }
    }

    printf("Menor caminho de %d para %d: %d\n", startVerticies, endVerticies, distances[endVerticies]);

    free(distances);
    free(visited);
}

void measureTime(int **matrix, int numSettings)
{
    int startVerticies = 0;
    int endVerticies = numSettings - 1;

    clock_t start_time, end_time;
    double time;

    start_time = clock();

    for (int i = 0; i < 1000; i++)
        dijkstraAlgorithm(matrix, numSettings, startVerticies, endVerticies);

    end_time = clock();

    time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Tempo gasto - executando 1000 vezes: %lf s\n", time);
}
