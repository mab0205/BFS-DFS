#ifndef  FILADINAMICA
#define  FILADINAMICA

typedef struct nodo_fila {
    int info;
    struct nodo_fila* prox;
} nodo_fila;

typedef struct fila{
    nodo_fila* inicio;
    nodo_fila* fim;
}fila;

fila *cria_fila();

int vazia_fila (fila *f);

void push_fila(fila *f, int x);

int pop_fila (fila *f);

void libera_f(fila* f);

void printFila(fila* f);

#endif  //FILADINAMICA
