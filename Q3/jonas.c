#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QTD_VERTICE 8
#define RAND_CAMINHO 101

typedef struct grafo{
	int vertice[QTD_VERTICE];
	float arestas[QTD_VERTICE][QTD_VERTICE];
}Grafo;

typedef struct {
    int id;
    float distancia;
    int predecessor;
} Distancia;

void exibirVertice(int id,Grafo grafo){
	for(int i=0;i<QTD_VERTICE;i++){
		printf("[%d] - [%d] = %f\n",id,i,grafo.arestas[id][i]);
	}
}

void exibirGrafo(Grafo grafo){
	for(int i=0;i<QTD_VERTICE;i++){
		printf("Caminho %d\n", i);
		exibirVertice(i,grafo);
	}
}

void exibeInfoDistancia(Distancia distancia){
	printf("Vertice atual: %d\n", distancia.id);
	printf("Distancia: %f\n", distancia.distancia);
	printf("Predecessor: %d\n", distancia.predecessor);
}

void exibeDistancia(Distancia *distancia){
	for(int i=0;i<QTD_VERTICE;i++){
		printf("Vertice: %d\n",i);
		exibeInfoDistancia(distancia[i]);
	}
}

void iniciarGrafo(Grafo *grafo){
	for(int id=0;id<QTD_VERTICE;id++){
		grafo->vertice[id] = id;
		for(int aresta =0;aresta < QTD_VERTICE;aresta++)
			grafo->arestas[id][aresta] = 0.0;
	}
}

void criandoGrafo(Grafo *grafo) {
    float valores[QTD_VERTICE][QTD_VERTICE] = {
        {0.000000, 0.700976, 0.809676, 0.088795, 0.121479, 0.348307, 0.421962, 0.699805},
        {0.700976, 0.000000, 0.066384, 0.587482, 0.642966, 0.990603, 0.295718, 0.271337},
        {0.809676, 0.066384, 0.000000, 0.069656, 0.949639, 0.382175, 0.322710, 0.988366},
        {0.088795, 0.587482, 0.069656, 0.000000, 0.842522, 0.275314, 0.596627, 0.556420},
        {0.121479, 0.642966, 0.949639, 0.842522, 0.000000, 0.847908, 0.184624, 0.397470},
        {0.348307, 0.990603, 0.382175, 0.275314, 0.847908, 0.000000, 0.889763, 0.850481},
        {0.421962, 0.295718, 0.322710, 0.596627, 0.184624, 0.889763, 0.000000, 0.317730},
        {0.699805, 0.271337, 0.988366, 0.556420, 0.397470, 0.850481, 0.317730, 0.000000}
    };

    // Preenchendo a matriz do grafo com os valores fornecidos
    for (int i = 0; i < QTD_VERTICE; i++) {
        for (int j = 0; j < QTD_VERTICE; j++) {
            grafo->arestas[i][j] = valores[i][j];
        }
    }
}


void atualizaDistancia(Distancia *distancia, Grafo grafo, int destino_atual, int destino_pos) {
    distancia[destino_pos].id = destino_pos;
    distancia[destino_pos].predecessor = destino_atual;

    if ((int)distancia[destino_pos].distancia == -2) {
        distancia[destino_pos].distancia = grafo.arestas[destino_atual][destino_pos];
    } else {
        distancia[destino_pos].distancia = distancia[destino_atual].distancia * grafo.arestas[destino_atual][destino_pos];
	}
}

Distancia *dijkstra(int ini, Grafo grafo){
	Distancia *distancia;
	distancia = (Distancia*)malloc(QTD_VERTICE * sizeof(Distancia));

	for (int i = 0; i < QTD_VERTICE; i++){
		distancia[i].id = i;
		distancia[i].distancia = -2;
	}
	distancia[ini].distancia = 1;

	for(int destino_atual = 0; destino_atual < QTD_VERTICE;destino_atual++){
		for(int destino_pos = 0;destino_pos < QTD_VERTICE;destino_pos++){

			if(destino_atual != destino_pos){
				float comp1 = distancia[destino_atual].distancia;
				float comp2 = grafo.arestas[destino_atual][destino_pos];
				float comp3 = distancia[destino_pos].distancia;

				if(comp1 * comp2 > comp3){
					atualizaDistancia(distancia,grafo,destino_atual,destino_pos);
				}

			}

		}
	}

	return distancia;
}

void menorCaminho(int ini, int fim, Distancia *distancia) {
	if((ini < QTD_VERTICE && fim < QTD_VERTICE)){
		int caminho[QTD_VERTICE];
		int pos = 0;
		int atual = fim;

		while (atual != ini && atual != -1) {
			caminho[pos++] = atual;
			atual = distancia[atual].predecessor;
		}

		if (atual == ini) {
			caminho[pos++] = ini;
		}

		printf("Menor caminho de %d para %d: ", ini, fim);
		for (int i = pos - 1; i >= 0; i--) {
			printf("%d", caminho[i]);
			if (i > 0) {
				printf(" -> ");
			}
		}
		printf("\n");
	}else{
		printf("Impossivel formar caminho\n");
	}
}

int main(){
	srand((unsigned int)2);

	Grafo grafo;
	Distancia *distancia;
	int ini=1,fim=7;

	iniciarGrafo(&grafo);
	criandoGrafo(&grafo);



	exibirGrafo(grafo);


	distancia = dijkstra(ini,grafo);
	
	menorCaminho(ini,fim,distancia);
	
	free(distancia);
	return 0;
}