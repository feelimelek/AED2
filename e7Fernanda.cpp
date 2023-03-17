#include <iostream>
#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
using namespace std;

#define MAX 50 //pode ser alterado, dependendo do tamanho das palavras

/*
Suponha um arquivo de registros de tamanho fixo (binário) em que cada registro é um par de arestas (v1,v2) e um custo, ou seja:

typedef struc {
    int v1;
    int v2;
    int custo;
} REGISTRO;
/
Escreva um algoritmo para ler um arquivo
deste tipo e construir o grafo
correspondente, retornando a respectiva ED
de listas de adjacências. Por simplicidade,
considere que os vértices possíveis são
numerados de 0 a 9.

*/


/*------------- Funções arquivo binário -------------- */

typedef struct registro {
    int v1;
    int v2;
    int custo;
} REGISTRO;

/*------------- Funções grafos -------------- */

//Grafo
typedef struct adjacencia{
    int vertice; //vertice onde chega
    int peso; //da aresta
    struct adjacencia *prox; //prox na lista, tipo no em lista ligada
} NO; //aresta, Nó

typedef struct vertice{
    NO* inicio;
} VERTICE; //aresta

NO* criaAdj(int v, int peso){ //v é o nó final da aresta
    NO *temp = (NO*)malloc(sizeof(NO)); //aloco espaço para um nó
    temp->vertice = v; //abasteço o vértice e o peso
    temp->peso = peso;
    temp->prox = NULL; //prox é NULL (vertice adicionado no final)
    return (temp); //retorno o endereço da adjacência que criei
}

bool criaAresta(VERTICE* g, int vi, int vf, int p, int n){ //vi = de onde sai, vf = onde chega, p = peso
    if(!g) return false;
    if((vf < 0) || (vf >= n)) return false; //a posição dos vertices começa em 0
    if((vi < 0) || (vi >= n)) return false;
    NO *novo = criaAdj(vf, p);
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
    return true;
}

void imprimeGrafo(VERTICE* g, int n){
    printf("Vértices: %d. \n", n);
    int i;
    for (i = 0; i < n; i++){
        printf("v%d:", i);
        NO *ad = g[i].inicio;//coloco o ponteiro na primeira adjacência
        while(ad){//enquanto a adjacência não for NULL
            printf("v%d(%d)", ad->vertice, ad->peso);
            ad = ad->prox; //vou para a próxima adjacência
        }
        printf("\n");
    }
}

void inicializarVertices(VERTICE* g, int n){
    for (int i = 0; i < n; i++){
        g[i].inicio = NULL; //inicializo cada espaço
    }
}


/*
Ideias:
- ler cada vértice e ir colocando no grafo
- getchar
- while para ler os registros
-

*/



int main(){

    int n;
    VERTICE *h = (VERTICE*)malloc(sizeof(VERTICE)*10);
    FILE* arq = NULL;
    int i;
    if((arq = fopen("teste.txt","r")) == NULL){ //adicionar arquivo texto se quiser
        printf("arq não encontrado");
    }
    printf("\nPara transformar o arquivo texto em .oi:\n");
        i = 0;
        int prox;
        int v1[MAX];
        int v2[MAX];
        int custo[MAX];
        int ler;
        struct registro arestas[MAX];
        if((arq = fopen("teste.txt","rb")) == NULL){ //adicionar arquivo texto se quiser
        }
        else{
            prox = 0;
            printf("Quantidade: %c", fgetc(arq));
            printf("Quantidade: %c", fgetc(arq));
            printf("\nO seu arquivo texto possui os seguintes registros:\n");
            while (!feof(arq)){
                    fscanf(arq, "%d/", &v1[prox]);
                    printf("    V1: %d", v1[prox]);
                    fscanf(arq, "%d/", &v2[prox]);
                    printf("V2: %d   ", v2[prox]);
                    fscanf(arq, "%d/\n", &custo[prox]);
                    printf("Custo: %d", custo[prox]);
                    prox++;
            }
            fclose(arq);
            printf("Lendo o arquivo .oi");
            for (int i = 0; i < prox; i++){
                arestas[i].v1 = v1[i];
                arestas[i].v2 = v2[i];
                arestas[i].custo = custo[i];
            }
            struct registro arestas_binarias[MAX];
            FILE* nova = NULL;
            if((nova = fopen("teste1.oi","wb+")) == NULL){
                printf("\nArquivo nao encontrado\n");
            }
            else{

                i = fwrite(arestas, sizeof(registro), prox, nova);
                rewind(nova);
                printf("\nSeu novo arquivo possui os seguintes registros:\n");
                inicializarVertices(h, prox);
                //printf("%c", fgetc(nova));
                for(i = 0; i < prox; i++){
                    ler = fread(&arestas_binarias[i], sizeof(registro), 1, nova);
                    printf("\n%d", arestas_binarias[i].v1);
                    printf("    %d", arestas_binarias[i].v2);
                    printf("    %d", arestas_binarias[i].custo);
                    criaAresta(h, (arestas_binarias[i].v1), (arestas_binarias[i].v2), arestas_binarias[i].custo, prox);
                }
                if(i < 0){
                    printf("\nArquivo vazio\n");
                }
            }
            printf("\nFim do processo");

                imprimeGrafo(h, prox-1);
            }

    return 0;
}


