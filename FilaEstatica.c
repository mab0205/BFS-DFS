#include <stdio.h>
#include <stdlib.h>
#include"FilaEstatica.h"

fila* cria_fila() {
    fila* f = (fila*)malloc(sizeof(fila));
    f->inicio = f->fim = 0;

    return f;
}

int vazia_fila(fila* f) {
    if (f->inicio == f->fim) return 1;
  else  
    return 0;
}

void push_fila(fila* f, int x) {
    f->v[f->fim] = x;
    f->fim = (f->fim + 1) % MAX; //aritmetica modular reinicie el posicionamiento de cada numero en el mismo tamaño del vector
}

int pop_fila(fila* f) {
    int x = f->v[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;

    return x;
}
void libera_f(fila* f) {
    while (vazia_fila(f) != 1) {
        pop_fila(f);
    }
}

void printFila(fila* f) {
  int i = f->inicio;
  if (vazia_fila(f)) {
  printf("Fila Vazia");
  }else{
  printf("\nVizinhos->");
    for (i = f->inicio; i < f->fim ; i++) {
      printf("%d ", f->v[i]);
    }
  }
}


