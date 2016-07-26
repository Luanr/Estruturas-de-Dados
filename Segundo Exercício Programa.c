/**
*** Universidade Federal de Santa Catarina
*** Exercício programa da disciplina de Estruturas de Dados 2015/2
*** Alunos: Christian Roger Gaio (14202477) e Luan Rodrigues Silva (14209239)
*** Professor: Álvaro Junio


    Escalonador de Processos Simplificado

        Um processo pode ser visto como um conjunto de instruções que deve ser executado pelo
    processador de uma máquina. A cada instante de tempo, um sistema de escalonamento de
    processos deve escolher um processo para ser executado por um processador. Cada processo
    tem o seu identificador único (formado pelo prefixo “id” seguido por um número inteiro entre 1
    e 5000), o tempo necessário para executar todas as suas instruções no processador (um número
    inteiro entre 1 e 100 (unidade em milisegundos)), e a prioridade do processo (um núumero inteiro
    entre 1 e 1000). A cada instante de tempo, ou o processador fica ocioso (não existe processo
    esperando na fila para ser executado), ou um novo processo é escolhido espontaneamente para
    ser executado (termina a execu¸c˜ao de um processo), ou um processo é escolhido abruptamente
    para ser executado (passaram 50 ms de execução de um processo).


    Descrição das funções:

        int addHeap(processo v[], int n)
            - recebe um vetor de processos com um heap adicionado e o numero de posicoes e insere
              um heap na ultima posicao, devolve o numero de posicoes antigo mais um

        void heapfica(processo v[], int n)
            - recebe um quase max heap por baixo e heapfica o vetor até ele se tornar um heap completo

        void ler(processo v[], int n)
            - mostra cada processo de uma fila de prioridades junto com seu, id, tempo e prioridade

        void lerProcesso(processo v[], int k)
            - mostra um processo de uma fila de prioridade junto com seu id, tempo e prioridade

        void removefila(processo v[], int n, int k)
            - retira o maior elemento do vetor e troca pelo ultimo da fila

        void heapficaDeCima(processo v[], int n, int pai)
            - recebe um quase max heap por cima e heapfica o vetor até ele se tornar um heap completo


        Exemplo de entrada:

            4


            1
            25
            13

            2
            13
            1

            3
            15
            22

            4
            25
            30

        O usuário pediu para colocar quatro processos na nova fila de prioridade, após isso foi inseridas três entradas para cada processo, a primeira
               o id, segunda o tempo e a terceira a prioridade. Após isso os processos são colocados em um vetor, mais precisamente em um max heap das
               prioridades, depois o programa executará o processo que está no topo da fila de prioridade e remove ele depois de executar, heapficando
               novamente a fila até ser executado o próximo processo, quando não houver mais procesos o processador ficará ocioso.
*/
#include <locale.h>
#include <stdio.h>
#define N 100

typedef struct process {
    int id;
    int prioridade;
    int tempo;
} processo;

int addHeap(processo v[], int n);
void heapfica(processo v[], int n);
void ler(processo v[], int n);
void lerProcesso(processo v[], int k);
void removefila(processo v[], int n, int k);
void heapficaDeCima(processo v[], int n, int pai);

int main() {
    int i, n, prioridade, tempo, id, j;
    processo fila[N];

    setlocale(LC_ALL, "Portuguese");
    i = 1;

    printf("Digite a quantidade de processos que você quer colocar na fila de prioridade\n");
    scanf("%i", &n);



    printf("Digite o id, tempo (em milisegundos) e a prioridade de cada processo! \n");

    while(i <= n) {
        printf("Processo %i :\n", i);

        printf("id ");
        scanf("%i", &id);
        fila[i].id = id;

        printf("tempo ");
        scanf("%i",  &tempo);
        fila[i].tempo = tempo;

        printf("prioridade ");
        scanf("%i",&prioridade);
        fila[i].prioridade = prioridade;

        i = addHeap(fila, i);
    }


    printf("\n\n\nHeap com as prioridades dos processos da entrada:\n");

    ler(fila, n);

    printf("\nFim dos processos!\n");

    for(j = i; j > 1; j--) {

        lerProcesso(fila, 1);

        printf("\nRemovendo elemento! \n");

        removefila(fila, n, 1);
        n--;

        ler(fila, n);
    }

    return 0;
}

int addHeap(processo v[], int n) { /* vetor, posicao, valor */
    heapfica(v, n);
    return n + 1;
}

void heapfica(processo v[], int n) {
    int posicao;
    processo auxiliar;

    posicao = n;

    while(v[posicao/2].prioridade < v[posicao].prioridade && posicao / 2 != 0) { /* troca */
         auxiliar = v[posicao/2];
         v[posicao/2] = v[posicao];
         v[posicao] = auxiliar;
         posicao = posicao / 2;
    }
}

void ler(processo v[], int n) {
    int i;
    if(n == 0) {
        printf("\n\nSem processos a serem executados, processador ocioso!");
    }

    for(i = 1; i < n + 1; i++) {
        printf("\n\nId: %i  \nTempo: %i ms\nPrioridade: %i", v[i].id, v[i].tempo, v[i].prioridade);
    }
    printf("\n");
}

void lerProcesso(processo v[], int k) {
    printf("\n\n\nPróximo processo para ser executado: \nId: %i\nTempo: %i ms\nPrioridade: %i\n\n", v[k].id,v[k].tempo,v[k].prioridade);
}

void removefila(processo v[], int n, int k) {
    int aux;

    aux = v[k].prioridade;
    v[k] = v[n];
    v[n].prioridade = aux;

    heapficaDeCima(v, n - 1, k);
}

void heapficaDeCima (processo v[], int n, int pai) {
   int filho;
   processo k;

   filho = 2 * pai;
   k.id = v[pai].id;
   k.prioridade = v[pai].prioridade;
   k.tempo = v[pai].tempo;


   while (filho <= n) {
      if (filho < n && v[filho].prioridade < v[filho + 1].prioridade) {
        ++filho;
      }
      if (k.prioridade >= v[filho].prioridade) {
        return;
      }
      v[pai] = v[filho];
      pai = filho;
      filho = 2 * pai;
   }
   v[pai] = k;

}
