#include "q1.h"


/**
 * @brief Função principal do programa, apresenta um menu interativo com três opções:
 * execução do algoritmo Dijkstra, medição do tempo de execução ou saída do programa.
 *
 * @return Retorna 0 ao encerrar o programa.
 */

int main()
{
    int configurations[N_CONFIGS][N_DISCOS];
    int matrixAdj[N_CONFIGS][N_CONFIGS];

    generateConfigurations(configurations);

    generateAdjacentMatrix(configurations, matrixAdj);

    int opcao;
    do
    {
        printf("============================\n");
        printf("      Torres de Hanoi      \n");
        printf("============================\n");

        printf("Escolha uma opção:\n");
        printf("1. Executar Dijkstra\n");
        printf("2. Exibir tempo de execução (100 execuções de Dijkstra)\n");
        printf("3. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            runDijkstra(matrixAdj, 0, N_CONFIGS - 1);
            break;
        case 2:
            measureTime(matrixAdj);
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

/**
 * @brief Gera todas as configurações possíveis das torres de Hanoi, armazenando-as na matriz.
 *
 * @param configurations Matriz onde as configurações serão armazenadas.
 */

void generateConfigurations(int configurations[][N_DISCOS])
{
    for (int i = 0; i < N_CONFIGS; i++)
    {
        int temp = i;
        for (int j = 0; j < N_DISCOS; j++)
        {
            configurations[i][j] = temp % N_PINOS + 1;
            temp /= N_PINOS;
        }
    }
}

/**
 * @brief Avalia se é possível realizar um movimento válido entre duas configurações.
 *
 * @param settings1 Configuração inicial.
 * @param settings2 Configuração final.
 * @return int Retorna 1 se o movimento for válido, 0 caso contrário.
 */

int avaliableMoviment(int settings1[], int settings2[])
{
    int moviments = 0;
    int movedDisk = -1;
    int check = 1;

    for (int i = 0; i < N_DISCOS; i++)
    {
        if (settings1[i] != settings2[i])
        {
            moviments++;
            if (moviments > 1)
                check = 0;

            movedDisk = i;
        }
    }

    if (moviments == 0 || moviments > 1)
        check = 0;

    if (check)
    {
        int originPin = settings1[movedDisk];
        int destinacionPin = settings2[movedDisk];

        for (int i = 0; i < N_DISCOS; i++)
        {
            if (i != movedDisk)
            {
                if (settings1[i] == originPin && i < movedDisk)
                    check = 0;

                if (settings2[i] == destinacionPin && i < movedDisk)
                    check = 0;
            }
        }
    }

    return (check);
}

/**
 * @brief Gera a matriz de adjacência representando os movimentos válidos entre configurações.
 *
 * @param configurations Matriz com as configurações possíveis das torres de Hanoi.
 * @param matrix Matriz de adjacência a ser preenchida.
 */

void generateAdjacentMatrix(int configurations[N_CONFIGS][N_DISCOS], int matrix[N_CONFIGS][N_CONFIGS])
{
    for (int i = 0; i < N_CONFIGS; i++)
    {
        for (int j = 0; j < N_CONFIGS; j++)
        {
            if (avaliableMoviment(configurations[i], configurations[j]))
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }
}

/**
 * @brief Executa o algoritmo de Dijkstra para encontrar o menor caminho entre dois vértices.
 *
 * @param matrix Matriz de adjacência representando o grafo.
 * @param start Índice do vértice inicial.
 * @param end Índice do vértice final.
 */

void runDijkstra(int matrix[][N_CONFIGS], int start, int end)
{
    int distance[N_CONFIGS];
    int visited[N_CONFIGS];

    for (int i = 0; i < N_CONFIGS; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[start] = 0;

    for (int count = 0; count < N_CONFIGS - 1; count++)
    {
        int aux = -1;

        for (int i = 0; i < N_CONFIGS; i++)
        {
            if (!visited[i] && (aux == -1 || distance[i] < distance[aux]))
                aux = i;
        }

        visited[aux] = 1;

        for (int v = 0; v < N_CONFIGS; v++)
        {
            if (!visited[v] && matrix[aux][v] && distance[aux] != INT_MAX &&
                distance[aux] + matrix[aux][v] < distance[v])
                distance[v] = distance[aux] + matrix[aux][v];
        }
    }

    printf("Menor caminho de %d para %d: %d\n", start, end, distance[end]);
}

/**
 * @brief Mede o tempo de execução do algoritmo de Dijkstra para 100 execuções consecutivas.
 *
 * @param matrix Matriz de adjacência representando o grafo.
 */

void measureTime(int matrix[][N_CONFIGS])
{
    clock_t start, end;
    double tempo;

    start = clock();

    for (int i = 0; i < 100; i++)
        runDijkstra(matrix, 0, N_CONFIGS - 1);

    end = clock();

    tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo de 100 execuções: %lf ms\n", tempo);
}
