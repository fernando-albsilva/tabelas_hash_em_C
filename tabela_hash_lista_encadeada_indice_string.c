/* A chave para o indice na tabela hash é o primeiro nome do aluno, 
    nao foi considerado que haverá matricula em duplicidade. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct aluno
{
    char nome[82];
    int mat;
    struct aluno *prox;
};

typedef struct aluno Aluno;

#define N 10
void inicializa_hash(Aluno **);
void imprime_hash_endereco(Aluno **);
int calcula_indice(char *);
void incluir_na_tabela(Aluno **);
void imprime_conteudo(Aluno **);
void busca_elemento(Aluno **);
void excluir_elemento(Aluno *,Aluno *,Aluno *);
void colisao(Aluno **);

int main(void)
{
    Aluno *hash[N];
    
    inicializa_hash(&hash[0]);
    imprime_hash_endereco(&hash[0]);
    for(;;){
    incluir_na_tabela(&hash[0]);
    imprime_conteudo(&hash[0]);
    colisao(&hash[0]);
    busca_elemento(&hash[0]);
    imprime_conteudo(&hash[0]);
    }

    return 0;
}
/* Percorre a tabela hash iniciando todos elementos , fazendo com que apontem
para NULL */
void inicializa_hash(Aluno **ptrhash)
{
    int i = 0;

    for (; i < N; i++)
    {
        *ptrhash = NULL;
        ptrhash++;
    }
}
/* imprime os elementos da tabela hash para verificar para onde estão apontando */
void imprime_hash_endereco(Aluno **ptrhash)
{
    int i = 0;

    for (; i < N; i++)
    {
        printf("\n hash[%d] = %p ", i, *ptrhash);
        ptrhash++;
    }
}

/* Recebe o primeiro elemento que aparece na string por referencia,
percorre a string somando  cada char e retorna como indice  o total % N, onde N 
siginifica o tamanho da tabela hash */

int calcula_indice(char *ptrChar)
{
    int total = 0;

    while (*ptrChar != '\0')
    {
        total += (int)*ptrChar;
        ptrChar++;
    }
    return total % N;
}

/* Recebe o endereço do primeiro ponteiro para lista ta tabela hash */
void incluir_na_tabela(Aluno **ptrHash)
{
    int mat, teste = 0, indice = 0;
    char nome[82];

    Aluno *pai, *aux;

    do
    {
        printf("\n -----------------------------------------------------------------------\n");
        printf("\nInclusão de aluno.\n");
        printf("\nDigite o nome do aluno: ");
        scanf("%s", nome);
        printf("\nDigite a matricula do aluno: ");
        scanf("%d", &mat);
        indice = calcula_indice(&nome[0]);
        /* Se a posicao da tabela hash estiver vazia ele cria uma lista */

        if (ptrHash[indice] == NULL)
        {
            aux = (Aluno *)malloc(sizeof(Aluno));
            if (aux == NULL)
            {
                printf("\n Nao ha memoria suficiente");
                free(aux);
                exit(1);
            }
            else
            {
                aux->mat = mat;
                strcpy(aux->nome, nome);

                aux->prox = NULL;
                ptrHash[indice] = aux;
            }
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
            else
            {
                aux->mat = mat;
                strcpy(aux->nome, nome);

                aux->prox = NULL;
                pai->prox = aux;
            }
        }

        printf("\n Digite 1 para incluir novamente ou qualquer outro número para sair: ");
        scanf("%d", &teste);
    } while (teste == 1);
}
/*imprime o conteudo das listas encadeadas se houver elemento nas mesmas*/
void imprime_conteudo(Aluno **ptrhash)
{
    int i = 0;
    Aluno *aux;
    for (; i < N; i++)
    {

        if (*ptrhash != NULL)
        {
            printf("\n----------------------------------\n");
            aux = *ptrhash;
            while (aux != NULL)
            {
                printf("\n hash[%d]: \n", i);
                printf("\nNome: %s", aux->nome);
                printf("\nMatricula: %d\n", aux->mat);
                aux = aux->prox;
            }
        }
        else
        {
            printf("\n----------------------------------\n");
            printf("\n hash[%d] = %p ", i, *ptrhash);
        }
        ptrhash++;
    }
}
void busca_elemento(Aluno **ptrHash)
{
    char busca_nome[82];
    int busca_mat, indice;
    Aluno *aux, *pai, *neto;
    
    printf("\nDigite o nome do aluno que deseja buscar.");
    scanf("%s", busca_nome);
    printf("Digite a matricula do aluno para que a exclusao seja feita:");
    scanf("%d", &busca_mat);

    indice = calcula_indice(busca_nome);
    /* verifica se o nome do aluno existe na tabela */
    if (ptrHash[indice] == NULL)
    {
        printf("\n Não existe esse aluno na tabela.\n");
    }
    else
    {
        aux = ptrHash[indice];
        /* Se for o primeiro elemento da lista o programa exclui e linka com o proximo elemento
            idependente dele ser NULL */
        if (aux->mat == busca_mat)
        {   
            ptrHash[indice]=aux->prox;
            free(aux);   
        }
        /*Se nao for o primeiro elemento da lista ele percorre ate achar a matricula correta */
        else
        {
            while (aux->mat != busca_mat && aux != NULL)
            {
                pai = aux;
                aux =aux->prox;
                neto = aux->prox;
            }
            /* Se aux for NULL ele percorreu a lista toda e nao encontrou a matricula */
            if(aux==NULL)
            {
                printf("\n Matricula nao encontrada.\n");
                return ;
            }else
            {
                excluir_elemento(aux,pai,neto);
            }
            
        }
    }
}
/* exclui o aluno  e faz a ligação da lista */
void excluir_elemento(Aluno* aux, Aluno  *pai, Aluno * neto)
{
    if (aux->prox==NULL)
    {
        free(aux);
        pai->prox=NULL;
    }else{
        pai->prox=neto;
        free(aux);
    }
}

/* Conta quantas Alunos colidiram em determinado indice */

void colisao(Aluno ** ptrHash)
{ 
    int i = 0,cont=0;
    Aluno *aux;
    for (; i < N; i++)
    {

        if (*ptrHash != NULL)
        {
            printf("\n----------------------------------\n");
            aux = *ptrHash;
            while (aux != NULL)
            {   
                cont++;
                aux = aux->prox;
            }
                printf("\n hash[%d]: %d colisoes.\n", i ,cont);
                cont=0;
        }
        else
        {
            printf("\n----------------------------------\n");
            printf("\n hash[%d] = %d colisoes.\n ", i, cont);
        }
        ptrHash++;
    }
}