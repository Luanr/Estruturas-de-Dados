#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define primeiraMat "matrizum.txt"
#define segundaMat "matrizdois.txt"

typedef struct celula{
    int conteudo;
    int coluna;
    struct celula *seguinte;
} lista;

typedef struct vet {
    lista * linha;
} vetor;

typedef struct mat{
    int linhas;
    int colunas;
    vetor * listas;
} matriz;

/** Protótipos de função para a lista */
lista * criaLista();    /* cria e retorna uma nova lista com cabeca */
lista * insere(lista * cel, int x, int coluna);
void remover(lista *lst);
int valorNaColuna(lista * cabeca, int posicao);
/** fim de protótipos para listas */

/** Protótipos de função para matrizes e vetores */
void escreveM(matriz mat);
matriz leM(FILE * arq);
void desalocaM(matriz mat);
matriz somaMatriz(matriz mat1, matriz mat2);
matriz subtraiMatriz(matriz mat1, matriz mat2);
void atribuiMatriz(matriz mat1, matriz mat2);
matriz multiplicaMatriz(matriz mat1, matriz mat2);
matriz potenciaMatriz(matriz mat1, int n);
matriz matrizIdentidade(matriz mat1);
/** fim de protótipos para matrizes e vetores */

/** outras funções*/
void interface();
/** fim de outras funções*/

int main() {
    int continuar;

    continuar = 0;

    while(continuar == 0) {
        interface();
        printf("Digite 0 para reiniciar o programa ou outra tecla para sair\n");
        scanf("%i", &continuar);
        system("cls");
    }
    return -1;
}

void interface() {
    int escolha, n;
    matriz mt1, mt2, mt3;
    FILE * arq;



    printf("Digite alguma tecla para iniciar a Primeira matriz");
    scanf("%i", &escolha);
    arq = fopen(primeiraMat, "r");
    mt1 = leM(arq);
    arq = (FILE *) fclose(arq);
    printf("\n\n");
    escreveM(mt1);



    printf("\n\nO que deseja fazer com a matriz? \n\n 1 - Iniciar outra Matriz \n 2 - desalocar\n 3 - elevar a potencia de N\n\n");
    scanf("%i", &escolha);

    if(escolha == 1) { /* iniciar outra */
        arq = fopen(segundaMat, "r");
        mt2 = leM(arq);
        arq = (FILE *) fclose(arq);
        escreveM(mt2);
    } else if (escolha == 2) { /* desalocar */
        desalocaM(mt1);
        printf("Matriz desalocada com sucesso!\n");
        escolha = -1;
    } else if (escolha == 3) { /* elevar a potencia n */
        if(mt1.linhas == mt1.colunas) {
            printf("Digite o expoente da potenciacao!\n");
            scanf("%i", &n);

            if(n >= 0) {
                mt2 = potenciaMatriz(mt1, n);
                escreveM(mt2);
            } else {
                printf("Expoente inválido, esta matriz faz somente potências positivas\n");
                escolha = -1;
            }
        } else {
            printf("Você só pode fazer a potência de matrizes quadradas, ou seja, o numero de linhas deve ser igual ao numero de colunas\n");
            escolha = -1;
        }
    } else {
        escolha = -1;
    }



    if (escolha != -1) {
        printf("\n\n1 - Somar as duas matrizes\n2 - Subtrair as duas matrizes\n3 - Multiplicar as duas matrizes \n4 - Atribuir matriz a outra\n");
        scanf("%i", &escolha);
    }

    if(escolha == 1) { /* soma */
        if(mt1.colunas == mt2.colunas && mt1.linhas == mt2.linhas) {
            mt3 = somaMatriz(mt1, mt2);
            escreveM(mt3);
        } else {
            printf("A soma é possível somente se você tiver duas matrizes de mesma ordem!\n");
        }
    } else if (escolha == 2) { /* subtracao */
        if(mt1.colunas == mt2.colunas && mt1.linhas == mt2.linhas) {
            mt3 = subtraiMatriz(mt1, mt2);
            escreveM(mt3);
        } else {
            printf("A soma é possível somente se você tiver duas matrizes de mesma ordem!\n");
        }
    } else if (escolha == 3) { /* multiplicacao */
        if(mt1.colunas == mt2.linhas) {
            mt3 = multiplicaMatriz(mt1, mt2);
            escreveM(mt3);
        } else {
            printf("Você só pode fazer multiplicação de uma matriz se a quantidade de colunas da primeira for igual a quantidade de linhas da segunda\n");
        }
    } else if (escolha == 4) { /* atribuição */
        if(mt1.linhas == mt2.linhas && mt1.colunas == mt2.colunas) {
            desalocaM(mt2);
            atribuiMatriz(mt1, mt2);
            escreveM(mt2);
        } else {
            printf("Você só pode fazer atribuição de uma matriz n x m com uma n x m\n");
        }
    }
}

matriz matrizIdentidade(matriz mat1) {
    int linhas, i;
    matriz identidade;
    vetor * vete;
    lista * aux, * cabeca;

    linhas = mat1.linhas;

    vete = malloc(linhas * sizeof(vetor));
    i = 0;

    while(i < linhas) {
        cabeca = criaLista();
        aux = cabeca;
        aux = insere(aux,1,i);
        vete[i].linha = cabeca;
        i++;
    }

    identidade.colunas = linhas;
    identidade.linhas = linhas;
    identidade.listas = vete;
    return identidade;
}

matriz potenciaMatriz(matriz mat1, int n) {
    int i;
    matriz mat3;

    if(n == 0) {
        return matrizIdentidade(mat1);
    } else  if (n == 1) {
        return mat1;
    } else {
        mat3 = multiplicaMatriz(mat1, mat1);
        for(i = 0; i < n - 2; i++) {
            mat3 = multiplicaMatriz(mat1, mat3);
        }
        return mat3;
    }
}

matriz multiplicaMatriz(matriz mat1, matriz mat2) {
    matriz mat3;
    int soma, i, j, w, a, b;
    lista * aux3, * cabeca;
    vetor * vete;

    mat3.linhas = mat1.linhas;
    mat3.colunas = mat2.colunas;
    vete = malloc(mat3.linhas * sizeof(vetor));

    mat3.listas = vete;

    for(i = 0; i < mat3.linhas; i++) {
        cabeca = criaLista();
        aux3 = cabeca;

        soma = 0;
        for(j = 0; j < mat3.colunas; j++) {
            soma = 0, a = 0, b = 0;
            for(w = 0; w < mat1.colunas; w++) {
                a = valorNaColuna(mat1.listas[i].linha, w);
                b = valorNaColuna(mat2.listas[w].linha, j);
                soma += a * b;
            }

            if(soma != 0) {
                aux3 = insere(aux3, soma,j);
            }
        }
        mat3.listas[i].linha = cabeca;
    }

    return mat3;
}

void atribuiMatriz(matriz mat1, matriz mat2) {
    int n, m, i, j;
    lista * cabeca, * aux1, * aux2;

    desalocaM(mat2);

    n = mat1.linhas;
    m = mat1.colunas;

    for(i = 0; i < n; i++) {
        cabeca = mat2.listas[i].linha;
        aux2 = cabeca;
        aux1 = mat1.listas[i].linha->seguinte;

        for(j = 0; j < m; j++) {
            if(aux1 != NULL) {
                if(aux1->coluna == j) {
                    aux2 = insere(aux2, aux1->conteudo, j);
                    aux1 = aux1->seguinte;
                }
            }
        }
        mat2.listas[i].linha = cabeca;
    }
}

matriz subtraiMatriz(matriz mat1, matriz mat2) {
    int i, j;

    matriz mat3;
    lista * aux1, * aux2, * aux3, * cabeca;
    vetor * vete;

    mat3.colunas = mat1.colunas;
    mat3.linhas = mat1.linhas;

    vete =(vetor *) malloc(mat3.linhas * sizeof(vetor));

    for(i = 0; i < mat1.linhas; i++) {
        aux1 = mat1.listas[i].linha;
        aux2 = mat2.listas[i].linha;
        cabeca = criaLista();
        aux3 = cabeca;

        for(j = 0; j < mat1.colunas; j++) {
            if(valorNaColuna(aux1, j) - valorNaColuna(aux2, j) != 0) {
                aux3 = insere(aux3, valorNaColuna(aux1, j) - valorNaColuna(aux2, j), j);
            }
        }
        vete[i].linha = cabeca;
    }

    mat3.listas = vete;
    return mat3;
}

matriz somaMatriz(matriz mat1, matriz mat2) {
    int i, j;

    matriz mat3;
    lista * aux1, * aux2, * aux3, * cabeca;
    vetor * vete;

    mat3.colunas = mat1.colunas;
    mat3.linhas = mat1.linhas;


    vete =(vetor *) malloc(mat3.linhas * sizeof(vetor));

    for(i = 0; i < mat1.linhas; i++) {
        aux1 = mat1.listas[i].linha;
        aux2 = mat2.listas[i].linha;
        cabeca = criaLista();
        aux3 = cabeca;

        for(j = 0; j < mat1.colunas; j++) {
            if(valorNaColuna(aux1, j) + valorNaColuna(aux2, j) > 0) {
                aux3 = insere(aux3, valorNaColuna(aux1, j) + valorNaColuna(aux2, j), j);
            }
        }
        vete[i].linha = cabeca;
    }

    mat3.listas = vete;
    return mat3;
}

int valorNaColuna(lista * cabeca, int posicao) {
    int resultado;

    resultado = 0;
    while(cabeca->seguinte != NULL) {
        cabeca = cabeca->seguinte;
        if(cabeca->coluna == posicao) {
            resultado = cabeca->conteudo;
        }
    }
    return resultado;
}

void desalocaM(matriz mat) {
    int i;
    for(i = 0; i < mat.linhas; i++) {
        while(mat.listas[i].linha->seguinte != NULL) {
            remover(mat.listas[i].linha);
        }
    }
}

matriz leM(FILE * arq) {
    int valor, n, m, i, j;
    lista * cabeca, * aux;
    vetor * vete;
    matriz mat;

    fscanf(arq, "%d", &n); /* n - linhas */
    fscanf(arq, "%d", &m); /* m - coluna */
    vete = (vetor *) malloc( sizeof(vetor)*n);

    for(i = 0; i < n; i++) {
        cabeca = criaLista();
        aux = cabeca;
        for(j = 0; j < m; j++) {
            fscanf(arq, "%d", &valor);
            if(valor != 0) {
                aux = insere(aux, valor, j);
            }
        }
        vete[i].linha = cabeca;
    }
    mat.colunas = m;
    mat.linhas = n;
    mat.listas = vete;

    return mat;
}

void escreveM(matriz mat) {
    int i, j, linha, coluna;
    lista * aux = (lista *) malloc(sizeof(lista));

    linha = mat.linhas;
    coluna = mat.colunas;


    for(i = 0; i < linha; i++) {
        aux = mat.listas[i].linha->seguinte;

        for(j = 0; j < coluna; j++) {
            if(aux == NULL) {
                printf("0 ");
            } else {
                if(aux->coluna == j) {
                    printf("%i ", aux->conteudo);
                    aux = aux ->seguinte;
                } else {
                    printf("0 ");
                }
            }
        }
        printf("\n");
        free(aux);
    }
}

lista * criaLista() {
    lista * lst;
    lst = (lista *) malloc(sizeof(lista));
    lst->seguinte = NULL;
    return lst;
}

lista * insere(lista * cel, int x, int coluna) {
    lista * nova;
    nova = (lista *) malloc(sizeof(lista));
    nova-> seguinte = NULL;
    nova-> conteudo = x;
    nova-> coluna = coluna;
    cel -> seguinte = nova;
    return nova;
}

void remover(lista *cel) {
    lista * lixo;
    lixo = cel -> seguinte;
    cel -> seguinte = lixo ->seguinte;
    free(lixo);
}
