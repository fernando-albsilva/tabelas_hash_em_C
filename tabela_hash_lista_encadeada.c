#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct aluno
{
    int mat;
    char nome[81];
    char email[41];
    struct aluno *prox;
};

typedef struct aluno Aluno;

#define N 10

void inicializa_tabela(Aluno **);
void imprime_tabela_Hash(Aluno **);
void imprime_conteudo(Aluno **);
int calcula_indice(int);
void incluir_na_tabela_Hash(Aluno **);
void busca_na_tabela(Aluno **);
void excluir_na_tabela(Aluno**);

int main(void)
{
    Aluno *Hash[N];
    inicializa_tabela(&Hash[0]);
    imprime_tabela_Hash(&Hash[0]);
    incluir_na_tabela_Hash(&Hash[0]);
imprime_tabela_Hash(&Hash[0]);
   // imprime_conteudo(&Hash[0]);
    busca_na_tabela(&Hash[0]);
    excluir_na_tabela(&Hash[0]);

}

void inicializa_tabela(Aluno **ptrHash)
{
    int i;
    for (i = 0; i < N; i++)
    {
        *ptrHash = NULL;
        ptrHash++;
    }
}

void imprime_tabela_Hash(Aluno **ptrHash)
{
    int i;
    printf("\n---------------------------------------------\n");
    for (i = 0; i < N; i++)
    {
        printf("\n Hash[%d] = %p\n", i, *ptrHash);
        ptrHash++;
    }
    printf("\n---------------------------------------------\n");
}

void imprime_conteudo(Aluno **ptrHash)
{
    Aluno *aux;
    int i;
    printf("\n---------------------------------------------\n");
    for (i = 0; i < N; i++)
    {
        if (ptrHash[i] == NULL)
        {
            printf("\n Hash[%d] = %p\n", i, *ptrHash);
        }
        else
        {
            printf("\n Hash[%d] :   ", i);
            printf("\n Matricula = %d :", ptrHash[i]->mat);
            printf("\n Nome = %s: ", ptrHash[i]->nome);
            printf("\n Email = %s \n", ptrHash[i]->email);
            aux = ptrHash[i]->prox;
            while (aux != NULL)
            {
                printf("\n Hash[%d] :   ", i);
                printf("\n Matricula = %d :", aux->mat);
                printf("\n Nome = %s: ", aux->nome);
                printf("\n Email = %s \n", aux->email);
                aux = aux->prox;
            }
        }
    }
    printf("\n---------------------------------------------\n");
}
int calcula_indice(int mat)
{
    return mat % N;
}

void incluir_na_tabela_Hash(Aluno **ptrHash)
{
    int teste = 1, mat, indice;
    char nome[81];
    char email[41];
    Aluno *aux, *pai;

    do
    {

        printf("\n Digite a matricula do aluno: ");
        scanf("%d", &mat);
        printf("\n Digite o nome do aluno: ");
        scanf("%s", nome);
        printf("\n Digite a email do aluno: ");
        scanf("%s", email);

        indice = calcula_indice(mat);

        if (ptrHash[indice] == NULL)
        {
            aux = (Aluno *)malloc(sizeof(Aluno));
            if (aux == NULL)
            {
                printf("\n Nao ha memoria suficiente");
                free(aux);
                exit(1);
            }
            aux->mat = mat;
            strcpy(aux->nome, nome);
            strcpy(aux->email, email);
            aux->prox = NULL;
            ptrHash[indice] = aux;
        }
        else
        {
            aux = ptrHash[indice];
            while (aux != NULL)
            {
                pai = aux;
                aux = aux->prox;
            }
            aux = (Aluno *)malloc(sizeof(Aluno));
            if (aux == NULL)
            {
                printf("\n Nao ha memoria suficiente");
                free(aux);
                exit(1);
            }
            aux->mat = mat;
            strcpy(aux->nome, nome);
            strcpy(aux->email, email);
            aux->prox = NULL;
            pai->prox = aux;
        }

        printf("\n Digite 1 para incluir novamente ou qualquer outro numero para sair: ");
        scanf("%d", &teste);
    } while (teste == 1);
}

void busca_na_tabela(Aluno **ptrHash)
{
    int mat, indice;
    Aluno *aux;

    printf("\n Digite a matricula do aluno: ");
    scanf("%d", &mat);

    indice = calcula_indice(mat);

    if (ptrHash[indice] == NULL)
    {
        printf(" \n Matricula nao existe na tabela.");
        return;
    }
    else
    {
        aux = ptrHash[indice];
        while (aux != NULL)
        {
            if (aux->mat == mat)
            {
                printf("\n Matricula encontrada. \n");
                printf("\n Hash[%d] :   ", indice);
                printf("\n Matricula = %d :", aux->mat);
                printf("\n Nome = %s: ", aux->nome);
                printf("\n Email = %s \n", aux->email);
                return;
            }
            else
            {
                aux = aux->prox;
            }
        }
        if(aux==NULL)
        {
            printf("\n Matricula nao existe na tabela");
        }
    }
}

void excluir_na_tabela(Aluno **ptrHash)
{
    
}