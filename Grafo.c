#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Grafo.h"

// Função para criar um nodo.
nodo* criaNodo(int v) {
    nodo* novo = malloc(sizeof(nodo));
    novo->caractere = v;
    novo->prox = NULL;
    return novo;
}

// Função para criar um grafo
Grafo* criaGrafo(int vertices) {
    int i;
    Grafo* grafo = malloc(sizeof(Grafo));
    grafo->numVertices = vertices; // total de vertices del grafo 

    grafo->listaAdj = malloc(vertices * sizeof( nodo*)); //se crea dinamicamente lista de adjacencia

    for (i = 0; i < vertices; i++) {
      grafo->listaAdj[i] = NULL; //crea la lista de adjacencia apuntando a null al siguiente elemento
    }
    return grafo; //se retorna el grafo creado 
}

// Função para criar uma aresta   VERTICE    NUMERO OU ARESTA
void adicionaAresta(Grafo* grafo, int s, int d) {
    // Cria uma aresta de s até d
    nodo* novo = criaNodo(d); //se crea nuevo nodo 
    novo->prox = grafo->listaAdj[s]; //el proximo nodo recibe el valor del vertice 
    grafo->listaAdj[s] = novo; //se conecta la nueva aresta con el vertice  
}

// Print  grafo, se envia como parametro o grafo 
void imprimeGrafo(Grafo* grafo) {
    int v; //variavel aux
    for (v = 0; v < grafo->numVertices; v++) { //mientras que v sea menor al numero del vertices del grafo 
        nodo* aux = grafo->listaAdj[v]; //se crea un nodo con la informacion de del vertice y la lista ligada
        printf("\n Vertice ListaAdj %d\n Nodo ", v);
        while (aux) { //mientras que aux apunte algun elemento que este ligado con el vertice 
            printf("->%d ", aux->caractere); //se imprime el valor del primer nodo 
            aux = aux->prox; //se avanza para el proximo nodo ligado al grafo 
        }
        printf("\n");
    }
}

void liberaGrafo(Grafo* grafo){ //libera a memoria do grafo para cada vertice da lista de Adjacencia
    for (int i = 0; i < grafo->numVertices; i++) liberaLista(grafo->listaAdj[i]);

    free(grafo->listaAdj);
    free(grafo);
}

void liberaLista(nodo*lista){ //libera cada posicao da lista de adjacencia recursivamente
    if (lista == NULL) return;

    liberaLista(lista->prox);
    free(lista);
}
