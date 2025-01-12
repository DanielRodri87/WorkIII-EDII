#include "q2.h"

/**
 * @brief Exibe o menu de opções para o usuário.
 * 
 * O menu apresenta três opções: execução do algoritmo Bellman-Ford, metrificação do tempo de execução 
 * ou saída do programa.
 */

void displayMenu()
{
    printf("============================\n");
    printf("      Torres de Hanoi      \n");
    printf("============================\n");

    printf("1. Executar o Algoritmo Bellman-Ford\n");
    printf("2. Metrificar o tempo de execução\n");
    printf("3. Sair\n");
    printf("Digite a opção desejada: ");
}

/**
 * @brief Função principal do programa.
 * 
 * Esta função inicializa as configurações das Torres de Hanoi, cria a matriz de adjacência
 * e permite ao usuário interagir com o programa por meio de um menu.
 * 
 * @return Retorna 0 ao finalizar o programa.
 */

int main()
{
    int configurations[N_CONFIGS][N_DISCS];
    int matrix[N_CONFIGS][N_CONFIGS];
    int choice;

    generateConfigurations(configurations, N_CONFIGS);
    adjacencyMatrix(configurations, matrix);

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            bellmanFord(matrix, 0);
            break;
        case 2:
            measureExecutionTime(matrix);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida, tente novamente\n");
        }
    } while (choice != 3);

    return 0;
}

/**
 * @brief Gera todas as configurações possíveis para as Torres de Hanoi.
 * 
 * @param configurations Matriz onde as configurações serão armazenadas.
 * @param totalConfigs Número total de configurações possíveis.
 */

void generateConfigurations(int configurations[][N_DISCS], int totalConfigs)
{
    for (int i = 0; i < totalConfigs; i++)
    {
        int temp = i;
        for (int j = 0; j < N_DISCS; j++)
        {
            configurations[i][j] = temp % N_PEGS + 1; 
            temp /= N_PEGS;
        }
    }
}

/**
 * @brief Verifica se uma jogada entre duas configurações é válida.
 * 
 * @param config1 Configuração inicial.
 * @param config2 Configuração final.
 * @return Retorna 1 se a jogada for válida; caso contrário, retorna 0.
 */

int isValidMove(int config1[], int config2[])
{
    int moves = 0;
    int movedDisc = -1;
    int isValid = 1; 

    for (int i = 0; i < N_DISCS; i++)
    {
        if (config1[i] != config2[i])
        {
            moves++;
            if (moves > 1)
                isValid = 0; 
            movedDisc = i;
        }
    }

    if (moves == 0 || moves > 1)
        isValid = 0; 

    if (isValid)
    {
        int sourcePeg = config1[movedDisc];
        int targetPeg = config2[movedDisc];

        for (int i = 0; i < N_DISCS; i++)
        {
            if (i != movedDisc)
            {
                if (config1[i] == sourcePeg && i < movedDisc)
                    isValid = 0; 
                if (config2[i] == targetPeg && i < movedDisc)
                    isValid = 0; 
            }
        }
    }

    return (isValid); 
}

/**
 * @brief Gera a matriz de adjacência baseada nas configurações das Torres de Hanoi.
 * 
 * @param configurations Matriz com as configurações das Torres de Hanoi.
 * @param matrix Matriz de adjacência resultante.
 */

void adjacencyMatrix(int configurations[N_CONFIGS][N_DISCS], int matrix[N_CONFIGS][N_CONFIGS])
{
    for (int i = 0; i < N_CONFIGS; i++)
    {
        for (int j = 0; j < N_CONFIGS; j++)
        {
            if (isValidMove(configurations[i], configurations[j]))
                matrix[i][j] = 1; 
            else
                matrix[i][j] = 0; 
        }
    }
}

/**
 * @brief Executa o algoritmo Bellman-Ford para encontrar os menores caminhos.
 * 
 * @param matrix Matriz de adjacência representando o grafo.
 * @param startVertex Vértice de início.
 */

void bellmanFord(int matrix[][N_CONFIGS], int startVertex)
{
    int distances[N_CONFIGS];

    for (int i = 0; i < N_CONFIGS; i++)
        distances[i] = INT_MAX;

    distances[startVertex] = 0;

    for (int step = 0; step < N_CONFIGS - 1; step++)
    {
        for (int u = 0; u < N_CONFIGS; u++)
        {
            for (int v = 0; v < N_CONFIGS; v++)
            {
                if (matrix[u][v] && distances[u] != INT_MAX &&
                    distances[u] + matrix[u][v] < distances[v])
                    distances[v] = distances[u] + matrix[u][v];
            }
        }
    }
}

/**
 * @brief Mede o tempo de execução do algoritmo Bellman-Ford para 100 execuções.
 * 
 * @param matrix Matriz de adjacência representando o grafo.
 */

void measureExecutionTime(int matrix[][N_CONFIGS])
{
    int startVertex = 0;

    clock_t startTime, endTime;
    double elapsedTime;

    startTime = clock();

    for (int i = 0; i < 100; i++)
        bellmanFord(matrix, startVertex);

    endTime = clock();

    elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("Tempo de 100 execuções: %lf s\n", elapsedTime);
}
