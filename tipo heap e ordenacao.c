/**
*** Universidade Federal de Santa Catarina
*** Exercício programa da disciplina de Estruturas de Dados 2015/2
*** Alunos: Christian Roger Gaio (14202477) e Luan Rodrigues Silva (14209239)
*** Professor: Álvaro Junio


        Descrição do programa: o programa lê até dois arquivos no formato
    txt e transforma ele em um tipo de dado abstrato chamado matriz
    que armazena a quantidade de linhas, colunas e um vetor com
    várias listas encadeadas com cabeca. Na matriz não são armazenados
    valores iguais a 0.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

typedef struct process {
    int id;
    int prioridade;
    int tempo;
} processo;

/*
@TODO:
 funcao para heapficar um quase max heap
 funcao para heapsort
 implementar heap sort com as prioridades

*/

int main() {
    int i, v[N], n, prioridade, tempo, id, valor;

    i = 1;

    printf("digite a quantidade de numeros que o vetor de prioridade deve ter");
    scanf("%i", &n);



    printf("Digite o id, tempo e prioridade de cada processo! \n");
    while(i < n + 1) {
        scanf("%i", &v[i]);
        i = addHeap(v, i);
    }

    ler(v, n);

    removefila(v, n, 1);
    n--;

    ler(v, n);

    removefila(v, n, 1);
    n--;

    ler(v, n);


    return 0;
}

int maior(int v[], int n, int p) {
    int i, maior;

    p = v[1];

    for(i = 1; i < n; i++) {
        if(v[i] > maior) {
            maior = v[i];
        }
    }
    return maior;
}

int addHeap(processo v[], int n) { /* vetor, posicao, valor */
    heapfica(v, n);
    return n + 1;
}

void heapfica(int v[], int n) {
    int posicao;
    int auxiliar, aux2;

    posicao = n;



    while(v[posicao/2] < v[posicao] && posicao /2 != 0) { /* troca */
            auxiliar = v[posicao/2];
            v[posicao/2] = v[posicao];
            v[posicao] = auxiliar;
            posicao = posicao / 2;

    }
}

int maiorTodos(int v[], int n) {
    int i, maior;

    maior = 1;
    for(i = 1; i < n; i++) {
        if(v[i] > v[maior]) {
            maior = i;
        }
    }
    return maior;
}

int eMaxHeap(int v[], int n) { /* retorna 1 para true, 0 para false */
    int i;
    for(i = 1; i < n; i++) {
        if(v[i] < v[i/2]) {
            return 0;
        }
    }
    return 1;
}


void ler(int v[], int n) {
    int i;

    for(i = 1; i < n + 1; i++) {
        printf("%i ", v[i]);
    }
    printf("\n");
}

void removefila(int v[], int n, int k) {
    int aux;


    aux = v[k];
    v[k] = v[n];
    v[n] = aux;


    heapficaDeCima(v, n - 1, k);
}

void heapfica2(int v[], int n, int k) {
    int posicao;
    int auxiliar, aux2, esquerda, direita, maior;

    posicao = k;




    if( (v[posicao] < v[posicao * 2] && (posicao * 2) <= n)     ||     v[posicao] < v[(posicao * 2) + 1] && ((posicao * 2) + 1) <= n ) { /* se tem algum filho maior e este esta dentro do alcance do vetor */

        esquerda = v[posicao * 2];
        direita = v[(posicao * 2) +1];

        if(v[esquerda] > v[direita] && (posicao * 2) + 1 <= n) { /* troca pai pela esquerda */
            auxiliar = v[esquerda];
            v[esquerda] = v[posicao];
            v[posicao] = auxiliar;
            posicao = (posicao * 2) + 1;
            heapfica2(v, n, posicao);
        } else if(v[direita] > v[esquerda] && (posicao * 2) <= n) {
            auxiliar = v[direita];
            v[direita] = v[k];
            v[posicao] = auxiliar;
            posicao = (posicao * 2);
            heapfica2(v, n, posicao * 2);
        }
    }
}

void heapficaDeCima (int v[], int n, int pai) {
   int filho, k;

   filho = 2 * pai;
   k = v[pai];

   while (filho <= n) {
      if (filho < n && v[filho] < v[filho + 1]) {
        ++filho;
      }
      if (k >= v[filho]) {
        break;
      }
      v[pai] = v[filho];
      pai = filho;
      filho = 2 * pai;
   }
   v[pai] = k;
}
