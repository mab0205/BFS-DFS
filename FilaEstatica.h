#ifndef  FILAESTATICA
#define  FILAESTATICA
#define MAX 100

typedef struct{
    int v[MAX];
    int inicio, fim;
}fila;

fila *cria_fila();

int vazia_fila (fila *f);

void push_fila(fila *f, int x);

int pop_fila (fila *f);

void libera_f(fila* f);

void printFila(fila* f);

#endif  //FILAESTATICA
