#include "Q3.h"

/**
 * @brief Função principal que inicializa o grafo, gera um grafo com valores aleatórios,
 * executa o algoritmo de Dijkstra e exibe o menor caminho entre dois vértices.
 * 
 * @return Retorna 0 ao encerrar o programa.
 */

int main()
{
    srand((unsigned int)time(NULL));

    Graph graph;
    Distance *distances;
    int start = 0, end = 9;

    initializeGraph(&graph);
    generateGraph(&graph);

    printf("Grafo:\n");
    displayGraph(graph);

    distances = runDijkstra(start, graph);

    printf("Caminho curto:\n");
    findShortestPath(start, end, distances);

    free(distances);
    return 0;
}

/**
 * @brief Exibe as arestas de um vértice no grafo.
 * 
 * @param id Índice do vértice a ser exibido.
 * @param graph Grafo contendo as arestas.
 */

void displayVertex(int id, Graph graph)
{
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        printf("_____________________\n");
        printf("|%d| até |%d| = %.2f%%\n", id + 1, i + 1, graph.edges[id][i] * 100);
    }
}

/**
 * @brief Exibe o grafo completo, mostrando todas as arestas entre os vértices.
 * 
 * @param graph Grafo a ser exibido.
 */

void displayGraph(Graph graph)
{
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        printf("\nCaminhos do Vértice %d:\n", i + 1);
        displayVertex(i, graph);
    }
}

/**
 * @brief Inicializa o grafo, configurando todos os vértices e arestas com valores padrão.
 * 
 * @param graph Ponteiro para o grafo que será inicializado.
 */

void initializeGraph(Graph *graph)
{
    for (int id = 0; id < NUM_VERTICES; id++)
    {
        graph->vertices[id] = id;
        for (int edge = 0; edge < NUM_VERTICES; edge++)
            graph->edges[id][edge] = 0.0;
    }
}

/**
 * @brief Gera valores aleatórios para as arestas do grafo, com valores entre 0.10 e 1.00.
 * 
 * @param graph Ponteiro para o grafo que será preenchido.
 */

void generateGraph(Graph *graph)
{
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        for (int j = 0; j < NUM_VERTICES; j++)
        {
            if (i != j)
                graph->edges[i][j] = (rand() % 91 + 10) / 100.0;
            else
                graph->edges[i][j] = 0.0;
        }
    }
}

/**
 * @brief Atualiza as distâncias no algoritmo de Dijkstra.
 * 
 * @param distances Ponteiro para as distâncias calculadas até o momento.
 * @param graph Grafo contendo as arestas.
 * @param currentDest Índice do vértice de origem.
 * @param nextDest Índice do vértice de destino.
 */

void updateDistance(Distance *distances, Graph graph, int currentDest, int nextDest)
{
    distances[nextDest].id = nextDest;
    distances[nextDest].predecessor = currentDest;

    if ((int)distances[nextDest].probability == -2)
        distances[nextDest].probability = graph.edges[currentDest][nextDest];
    else
        distances[nextDest].probability = distances[currentDest].probability * graph.edges[currentDest][nextDest];
}

/**
 * @brief Executa o algoritmo de Dijkstra para encontrar os menores caminhos em um grafo.
 * 
 * @param start Índice do vértice inicial.
 * @param graph Grafo sobre o qual o algoritmo será executado.
 * @return Distance* Ponteiro para o array de distâncias calculadas.
 */

Distance *runDijkstra(int start, Graph graph)
{
    Distance *distances;
    distances = (Distance *)malloc(NUM_VERTICES * sizeof(Distance));

    for (int i = 0; i < NUM_VERTICES; i++)
    {
        distances[i].id = i;
        distances[i].probability = -2;
    }
    distances[start].probability = 1;

    for (int currentDest = 0; currentDest < NUM_VERTICES; currentDest++)
    {
        for (int nextDest = 0; nextDest < NUM_VERTICES; nextDest++)
        {
            if (currentDest != nextDest)
            {
                float comp1 = distances[currentDest].probability;
                float comp2 = graph.edges[currentDest][nextDest];
                float comp3 = distances[nextDest].probability;

                if (comp1 * comp2 > comp3)
                    updateDistance(distances, graph, currentDest, nextDest);
            }
        }
    }

    return (distances);
}

/**
 * @brief Encontra e exibe o menor caminho entre dois vértices.
 * 
 * @param start Índice do vértice inicial.
 * @param end Índice do vértice final.
 * @param distances Ponteiro para o array de distâncias calculadas.
 */

void findShortestPath(int start, int end, Distance *distances)
{
    if (start < 0 || start >= NUM_VERTICES || end < 0 || end >= NUM_VERTICES)
        printf("Indices fora do limite permitido.\n");
    else
    {
        int path[NUM_VERTICES];
        int pos = 0;
        int current = end;

        while (current != start)
        {
            if (current == -1 || current < 0 || current >= NUM_VERTICES)
                printf("Não foi possível encontrar o caminho.\n");
            else
            {
                path[pos++] = current;
                current = distances[current].predecessor;
            }
        }

        path[pos++] = start;

        printf("Caminho curto entre %d e %d: ", start+1, end+1);
        for (int i = pos - 1; i >= 0; i--)
        {
            printf("%d", path[i]+1);
            if (i > 0)
                printf(" -> ");
        }
        printf("\n");
    }
}
