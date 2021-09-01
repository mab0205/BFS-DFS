#ifndef GRAFO
#define GRAFO

#define MAX 100

// Struct do gráfo.
typedef struct nodo { // estrutrua de nodos com um int apontado para o primeiro int e uma struct para o prox
    int caractere;
    struct nodo* prox;
}nodo;

typedef struct Grafo { // estrutrua Grafo com um int apontado para o primeiro int e uma struct para a proxima lista de adjacencia
    int numVertices;
    struct nodo** listaAdj;
} Grafo;

// Protótipos das funções da biblioteca.

nodo* criaNodo(int v);

Grafo* criaGrafo(int vertices);

void adicionaAresta(Grafo* grafo, int s, int d);

void imprimeGrafo(Grafo* grafo);

void liberaGrafo(Grafo* grafo);

void liberaLista(nodo*lista);

#endif  //!GRAFO
