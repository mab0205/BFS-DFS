#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Grafo.h"
//#include "FilaEstatica.h"
#include "FilaDinamica.h"
//Função para imprimir o caminho das BFS e DFS                                                                              L                   X
void imprime_caminho(char matriz[MAX][MAX], int matrizInteiro[MAX][MAX], int* pai, int numBusca, int VerticeAtual, int* vetorHash, int M, int N) {
    int aux, aux2, i = 0, j, k, tamanhovetorpais = 0, linha, coluna;// variáveis auxiliares
    int vetorCaminho[MAX]; // vetor que armazena o caminho do vetor de pais 
    char matrizCopia[MAX][MAX]; // cópia da matriz de char que será alterada
    // se cria una matriz de copia do mapa para armazenar o caminho do local ao tesouro ¡
    for (linha = 0; linha < N; linha++)
        for (coluna = 0; coluna < M; coluna++)
            matrizCopia[linha][coluna] = matriz[linha][coluna];


    while (VerticeAtual != numBusca) {//tesouro!= do comeco 
        vetorCaminho[tamanhovetorpais] = VerticeAtual;//se armazena o caminho do vetor de pais 
        VerticeAtual = pai[VerticeAtual];
        tamanhovetorpais++; // variavel para armazenar o tamanho do caminho ouseja os passos
    }
    vetorCaminho[tamanhovetorpais] = VerticeAtual;

    for (k = 0; k < tamanhovetorpais; k++) {  // laço para percorrer o vetor de pais
        aux = vetorCaminho[k]; //índice do vetor hash 
        aux2 = vetorCaminho[k + 1]; //próxima posição do vetor hash

        for (i = 0; i < N; i++) { // laço para percorrer a matriz
            for (j = 0; j < M; j++) {
                //conteudo do vetor hash com a variavel aux  
                if (matrizInteiro[i][j] == vetorHash[aux]) { // caso seja a terra indicada pelo caminho
                    // substitui a direita 
                    if (matrizInteiro[i][j - 1] == vetorHash[aux2]) matrizCopia[i][j - 1] = '>';

                    // substitui a esquerda
                    if (matrizInteiro[i][j + 1] == vetorHash[aux2]) matrizCopia[i][j + 1] = '<';

                    // substitui abaixo
                    if (matrizInteiro[i - 1][j] == vetorHash[aux2]) matrizCopia[i - 1][j] = 'v';

                    // substitui acima
                    if (matrizInteiro[i + 1][j] == vetorHash[aux2]) matrizCopia[i + 1][j] = '^';
                }
            }
        }
    }

    //imprime a matriz copiada de char 
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%c", matrizCopia[i][j]);
        }
        printf("\n");
    }
    printf("%d Passo(s) \n", tamanhovetorpais); // o tamanho do vetor de pais é o número de passos do caminho
}

// Função de busca em Largura
//busca e fila ( BFS --> Busca em Largura -->caminho minimo)
void bfs(Grafo* grafo, int numBusca, int tesouro, int* visitados, int* pai) {
    int VerticeAtual, vizinho;

    fila* f = cria_fila(); //cria fila 
    nodo* aux;//cria nova extrutura auxiliar

    visitados[numBusca] = 1; //vetor visitados
    push_fila(f, numBusca); //push o primeiro numero 
    while (!vazia_fila(f)) { //Enquanto fila nao esta vazia
        VerticeAtual = pop_fila(f); //pop do ultimo elemnto da fila e armazena numa variavel aux -->v
        aux = grafo->listaAdj[VerticeAtual]; //aux é o conteudo da lista de adjacencia na posiçao do vertice atual
        while (aux) { //loop ate que seja Null
            vizinho = aux->caractere; //pega o vizinho do numero a ser buscado w-->

            if (visitados[vizinho] == 0) { //se o vizinho nao foi visitado
                visitados[vizinho] = 1; // marca como visitado o vizinho 
                push_fila(f, vizinho); // push na fila o vizinho visitado
                pai[vizinho] = VerticeAtual; //vetor de pais armazena o comteudo do VerticeAtual no indice do vizinho
                                            //Vizinho=1, VerticeAtual=3 --> pai{[],3,[],[],[]}
                                            //                                    ^indice=1
            }
            aux = aux->prox; //vai pro proximo vizinho 
        }
    }
    libera_f(f);
}

// Função de busca em Profundidade
//busca e fila ( DFS --> Busca em Profundidade --> caminho qualquer)
void dfs(Grafo* grafo, int numBusca, int tesouro, int* visitados, int* pai) { //dfs Recursiva
    nodo* aux = grafo->listaAdj[numBusca]; //cria nova extrutura auxiliar 
    visitados[numBusca] = 1; //vetor e igual a true ou sim 
    while (aux != NULL) {
        int vizinho = aux->caractere;//va pro vizinho do vertex 
        if (visitados[vizinho] == 0) { //se o vizinho nao foi visitado 
            pai[vizinho] = numBusca;
            dfs(grafo, vizinho, tesouro, visitados, pai);//recursivamente retorna o vizinho do vertice, vertex=connectedvertex
        }
        aux = aux->prox;//vai pro seguinte elemnto 
    }
}

int contaIlhas_bfs(Grafo* grafo, int numBusca, int* visitados, int* ilha) {
    int VerticeAtual;
    int tam = 0;
    fila* f = cria_fila(); //cria fila 
    nodo* aux;//cria nova extrutura auxiliar

    visitados[numBusca] = 1; //vetor visitados
    push_fila(f, numBusca); //push o primeiro numero 
    while (!vazia_fila(f)) { //Enquanto fila nao esta vazia
        VerticeAtual = pop_fila(f); //pop do ultimo elemnto da fila e armazena numa variavel aux -->v
        ilha[tam] = VerticeAtual; //pega o vertice atual e armazena num vetor de ilhas
        tam++;//vai para a seguinte posiçao
        aux = grafo->listaAdj[VerticeAtual]; //aux é o conteudo da lista de adjacencia na posiçao do vertice atual
        while (aux != NULL) { //loop ate que seja Null
            int vizinho = aux->caractere; //pega o vizinho do numero a ser buscado w-->
            //printf("visitados:%d ",visitados[vizinho]);
            if (visitados[vizinho] == 0) { //se o vizinho nao foi visitado
                visitados[vizinho] = 1; // marca como visitado o vizinho 
                push_fila(f, vizinho); // push na fila o vizinho visitado                                  
            }
            aux = aux->prox; //vai pro proximo vizinho 
        }
    }
    free(f);
    return tam; //retorna o tamanho da ilha
}

// Função que cria o vetor para o Gráfo
void vetorHashtag(int vetorhash[MAX], char matriz[MAX][MAX], int matrizVerdade[MAX][MAX], int linhas, int colunas, int* L, int* X, int* cont) {
    int i, j, k = 0; //variaveis auxiliares 
    char letra;

    for (i = 0; i < linhas; ++i) { // laço para percorrer a mtriz de caracteres
        for (j = 0; j < colunas; ++j) {
            letra = matriz[i][j]; // pega o char a ser comparado
            if ((letra == '#') || (letra == 'L') || (letra == 'X')) { // caso ache uma terra
                vetorhash[k] = matrizVerdade[i][j];
                if (letra == 'L') *L = k; // caso seja o L, é armazenado o valor
                if (letra == 'X') *X = k; // caso seja o X, é armazenado o valor
                k++;
            }
        }
    }
    *cont = k; //cont terá o número de terras
}

// Função para acrescentar arestas entre terras vizinhas
void deslocamentoLinha_Coluna(Grafo* grafo, char matriz[MAX][MAX], int matrizVerdade[MAX][MAX], int vetorhash[MAX], int countvetor, int M, int N, int i, int j, int deslocamentoI, int deslocamentoJ) {
    int num = 0, num2 = 0, num3 = 0;

    // compara o lado para que quando seja uma terra vizinha faça ligação no Gráfo
    if ((matriz[i + deslocamentoI][j + deslocamentoJ] == '#') || (matriz[i + deslocamentoI][j + deslocamentoJ] == 'L') || (matriz[i + deslocamentoI][j + deslocamentoJ] == 'X')) {
        for (num = 0; num < countvetor; num++) { // laço para encontrar a posição da terra no vetorhash
            if (matrizVerdade[i][j] == vetorhash[num]) num2 = num; // Pega o vertice
        }
        for (num = 0; num < countvetor; num++) { // laço para encontrar a posição da terra no vetorhash
            if (matrizVerdade[i + deslocamentoI][j + deslocamentoJ] == vetorhash[num]) num3 = num; // Pega o vertice ao lado que será adicionado
        }
        adicionaAresta(grafo, num2, num3); // adiciona no grafo, uma aresta entre dois vertices 
    }
}

int main() {
    Grafo* grafo;
    int N, M, L, X, i, j, k = 0, countvetor; //X=tesouro. L=inicio countvetor=tamanho do vetorhash
    char matriz[MAX][MAX], letra[MAX];
    int matrizVerdade[MAX][MAX], vetorhash[MAX]; //vetor auxiliar para armazenar as posicoes dos #


    int numilhas = 0;// variavel conta a quantidade de ilhas
    int tamanho_ilha, maior = 0, menor = 0;//variaveis para o tamanho maior e menor das ilhas 

    scanf("%d %d", &N, &M); //N numero de linhas/filas e M numero de colunas

    for (i = 0; i < N; ++i) scanf("%s", matriz[i]); //Recebemos a matriz de caracteres

    for (i = 0; i < N; i++)  // atribui um valor inteiro a cada posição da matriz 
        for (j = 0; j < M; j++, k++)
            matrizVerdade[i][j] = k;

    //funcao encontrar o local de inicio, a posição do tesouro e o total de terras e suas posições no mapa 
    vetorHashtag(vetorhash, matriz, matrizVerdade, N, M, &L, &X, &countvetor);

    //funcao para armazenar no gráfo o indice de cada terra do vetor de terras 
    grafo = criaGrafo(countvetor);

    for (i = 0; i < N; ++i) { // percorre a matriz para criar as arestas do gráfo
        for (j = 0; j < M; ++j) {
            if ((matriz[i][j] == '#') || (matriz[i][j] == 'L') || (matriz[i][j] == 'X')) {
                //olha pra esquerda
                if (j != 0) deslocamentoLinha_Coluna(grafo, matriz, matrizVerdade, vetorhash, countvetor, M, N, i, j, 0, -1);
                //olha pra direita
                if (j != M) deslocamentoLinha_Coluna(grafo, matriz, matrizVerdade, vetorhash, countvetor, M, N, i, j, 0, 1);
                //olha pra baixo 
                if (i != 0) deslocamentoLinha_Coluna(grafo, matriz, matrizVerdade, vetorhash, countvetor, M, N, i, j, -1, 0);
                //olha pra cima 
                if (i != N) deslocamentoLinha_Coluna(grafo, matriz, matrizVerdade, vetorhash, countvetor, M, N, i, j, 1, 0);
            }
        }
    }

    /*-------------------------------------*/

    int* visitadostam = (int*)malloc(countvetor * sizeof(int));//vetor vertices visitados
    int* ilha = (int*)malloc(countvetor * sizeof(int)); //vetor de pais
    int* vetorhashaux = (int*)malloc(countvetor * sizeof(int)); //Copia do vetor de terras 

    for (i = 0; i < countvetor; i++)visitadostam[i] = 0;
    for (i = 0; i < countvetor; i++)vetorhashaux[i] = i;//Copia do vetor de terras para cada terra coloca um numero i na posicao i 

    for (i = 0; i < countvetor; i++) {
        if (vetorhashaux[i] != -1) {//se a terra nao estiver visitada entra numa nova busca
            tamanho_ilha = contaIlhas_bfs(grafo, vetorhashaux[i], visitadostam, ilha);
            numilhas++; //soma mais um o numero de ilhas no programa
            //condiçoes para achar a ilha maior menor 
            if (numilhas == 1)maior = menor = tamanho_ilha;
            if (tamanho_ilha > maior)maior = tamanho_ilha;
            if (tamanho_ilha < menor)menor = tamanho_ilha;

            for (j = 0; j < tamanho_ilha; j++) {
                for (int p = 0; p < countvetor; p++) {
                    if (vetorhashaux[p] == ilha[j]) { //percorre cada terra da copia do vetor aux e se por igual ao vetor de ilhas sai do programa
                        vetorhashaux[p] = -1; //se a terra estiver visitada coloca -1 nessa posiçao
                    }
                }
            }
        }
    }
    printf("Ha %d ilha(s)\n", numilhas);
    printf("A maior tem tamanho %d\n", maior);
    printf("A menor tem tamanho %d\n", menor);

    free(visitadostam);
    free(ilha);
    free(vetorhashaux);

    /*------------DFS------------------------*/

    int* visitados_dfs = (int*)malloc(countvetor * sizeof(int));//vetor vertices visitados
    int* paidfs = (int*)malloc(countvetor * sizeof(int)); //vetor de pais
    for (i = 0; i < countvetor; i++) paidfs[i] = -1; // coloca -1 em cada posiçao do vetor de pais

    for (i = 0; i < countvetor; i++) visitados_dfs[i] = 0; //zera o vetor de visitados para ser utilizado na busca
    dfs(grafo, L, X, visitados_dfs, paidfs);

    if (paidfs[X] == -1) { //tratamento de erro 
        printf("Nao ha caminho para o tesouro\n");
        free(visitados_dfs);
        free(paidfs);
        liberaGrafo(grafo);
        exit(0);
    }

    printf("\nBusca em Profundidade:\n");
    imprime_caminho(matriz, matrizVerdade, paidfs, L, X, vetorhash, M, N);

    free(visitados_dfs);
    free(paidfs);

    /*------------------BFS-------------------*/

    int* visitados_bfs = (int*)malloc(countvetor * sizeof(int));//vetor vertices visitados
    int* paibfs = (int*)malloc(countvetor * sizeof(int)); //vetor de pais

    for (i = 0; i < countvetor; i++) visitados_bfs[i] = 0;//zera o vetor de visitados para ser utilizado na busca
    bfs(grafo, L, X, visitados_bfs, paibfs);


    printf("\nBusca em Largura:\n");
    imprime_caminho(matriz, matrizVerdade, paibfs, L, X, vetorhash, M, N);

    free(visitados_bfs);
    free(paibfs);
    liberaGrafo(grafo);
    return 0;
}
