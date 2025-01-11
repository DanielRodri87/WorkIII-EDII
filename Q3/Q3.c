#include "Q3.h"

int main()
{
    srand((unsigned int)time(NULL));

    Graph graph;
    Distance *distances;
    int start = 1, end = 7;

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


void displayVertex(int id, Graph graph)
{
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        printf("_____________________\n");
        printf("|%d| até |%d| = %.2f%%\n", id+1, i+1, graph.edges[id][i] * 100);

    }
}

void displayGraph(Graph graph)
{
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        printf("\nCaminhos do Vértice %d:\n", i + 1);
        displayVertex(i, graph);
    }
}

void initializeGraph(Graph *graph)
{
    for (int id = 0; id < NUM_VERTICES; id++)
    {
        graph->vertices[id] = id;
        for (int edge = 0; edge < NUM_VERTICES; edge++)
            graph->edges[id][edge] = 0.0;
    }
}

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

void updateDistance(Distance *distances, Graph graph, int currentDest, int nextDest)
{
    distances[nextDest].id = nextDest;
    distances[nextDest].predecessor = currentDest;

    if ((int)distances[nextDest].probability == -2)
        distances[nextDest].probability = graph.edges[currentDest][nextDest];
    else
        distances[nextDest].probability = distances[currentDest].probability * graph.edges[currentDest][nextDest];
}

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

void findShortestPath(int start, int end, Distance *distances)
{
    if ((start < NUM_VERTICES && end < NUM_VERTICES))
    {
        int path[NUM_VERTICES];
        int pos = 0;
        int current = end;

        while (current != start && current != -1)
        {
            path[pos++] = current;
            current = distances[current].predecessor;
        }

        if (current == start)
            path[pos++] = start;

        printf("Caminho curto entre %d a %d: ", start, end);
        for (int i = pos - 1; i >= 0; i--)
        {
            printf("%d", path[i]);
            if (i > 0)
                printf(" -> ");
        }
        printf("\n");
    }
    else
        printf("Foi impossível encontrar o caminho\n");
}