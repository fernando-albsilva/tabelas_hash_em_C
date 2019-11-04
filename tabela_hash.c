#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
struct aluno{
    int mat;
    char nome[81];
    char email[41];

};

typedef struct aluno Aluno;

#define N 10

void inicializa_tabela_null(Aluno **);
void imprime_tabela(Aluno **);
void insere_na_tabela(Aluno **);
int calcula_indice(int);
void busca(Aluno**);
Aluno * busca_na_tabela(Aluno**);
void excluir_na_tabela(Aluno **);
Aluno* busca_exclusao(Aluno**,int);
int main(void)
{
    int i;
    Aluno * Hash[N];
   
    
    
    

    inicializa_tabela_null(&Hash[0]);
   
   for(;;){
    insere_na_tabela(&Hash[0]);
    imprime_tabela(&Hash[0]);
   // busca(&Hash[0]);
    excluir_na_tabela(&Hash[0]);
    imprime_tabela(&Hash[0]);
   }
    return 0;
}

void inicializa_tabela_null(Aluno ** tab)
{
    int i;
    for(i=0;i<N;i++)
    {
        *tab=NULL;
        tab++;

    }

    
}

void imprime_tabela(Aluno ** tab)
{
    int i;
    Aluno * aux;
    for(i=0;i<N;i++)
    {
        if ( *tab == NULL)
        {
            printf("\n Hash[%d] = NULL\n",i);
            tab++;
        }else{
            aux=*tab;
            printf("\n Hash[%d] = ",i);
            printf("\n        matricula = %d",aux->mat);
            printf("\n        nome      = %s",aux->nome);
            printf("\n        email     = %s\n",aux->email);
            
            tab++;
            
        }

    }

}

void insere_na_tabela(Aluno ** Hash)
{
    Aluno * aux;
    int indice,teste=1,cont,testeTudo=0;
    int matricula;
    char nome[81];
    char email[41];
    char turma;

    //imprime_tabela(&Hash[0]);

    do
    { 
        
    
        printf("\n Obs:se a matricula digitada ja existir o programa ira atualizar os dados com os mesmos inseridos a seguir e saira da funçao de inserir.\n\nDigite a matricula :");
        scanf("%d",&matricula);

        printf("\nDigite o nome do aluno:");
        scanf("%s",nome);

        printf("\nDigite o e-mail do aluno:");
        scanf("%s",email);


        indice=calcula_indice(matricula);

        if(Hash[indice] == NULL || Hash[indice]->mat == -1)
        {
            aux=(Aluno*)malloc(sizeof(Aluno));
            if(aux == NULL)
            {
                printf("\n Nao há memoria suficiente.");
                free(aux);
                exit(1);
            }else{
                     aux->mat=matricula;
                     strcpy(aux->nome,nome);
                     strcpy(aux->email,email);
                    

                     Hash[indice]=aux;
            }

        }else{
           
            cont=0;
            testeTudo=indice;
            while(Hash[indice]!= NULL && indice < N)
            {
                if(matricula==Hash[indice]->mat)
                {
                     Hash[indice]->mat=matricula;
                     strcpy(Hash[indice]->nome,nome);
                     strcpy(Hash[indice]->email,email);
                     return;
                }
                cont++;
                indice=calcula_indice(matricula+cont);
                if(indice == testeTudo)
                {
                    printf("\n Nao ha espaco para inserir mais.");
                    exit(1);
                }
            }
            aux=(Aluno*)malloc(sizeof(Aluno));
            if(aux == NULL)
            {
                printf("\n Nao há memoria suficiente.");
                free(aux);
                exit(1);
            }         
                     aux->mat=matricula;
                     strcpy(aux->nome,nome);
                     strcpy(aux->email,email);
                 

                     Hash[indice]=aux;

        }
    
         printf("\n Deseja continuar incluindo na tabela ?  Digite '1' para continuar,  ou qualquer outro número para sair:");
        scanf("%d",&teste);
    
    }while( teste == 1);

    imprime_tabela(&Hash[0]);
}
int calcula_indice(int mat)
{
    return mat%N;
}
void busca(Aluno** Hash )
{
    Aluno * busca;

    busca=busca_na_tabela(&Hash[0]);
    if(busca != NULL){
    printf("\nAchou:\n");
            printf("\n        matricula = %d",busca->mat);
            printf("\n        nome      = %s",busca->nome);
            printf("\n        email     = %s",busca->email);
    }else{
        printf("\n Não achou.\n");
    }
}
Aluno* busca_na_tabela(Aluno** Hash)
{   
    int mat,indice,testeTudo,cont=0;

    
    printf("\nDigite a matricula que deseja procurar:");
    scanf("%d",&mat);

    indice=calcula_indice(mat);
             testeTudo=indice;
    if (Hash[indice]==NULL)
    {
        printf("\n Não existe essa matricula na tabela.");
        return NULL;

    }else{
        while(Hash[indice] != NULL)
        {
            if (Hash[indice]->mat == mat)
            {
                return Hash[indice];
            }else{
                cont++;
                indice=calcula_indice(mat+cont);
                if(testeTudo==indice)
                {
                    printf("\n Nao existe essa matricula na tabela.\n");
                    return NULL;
                }

            }
            
        }
        
    }


}

void excluir_na_tabela(Aluno ** Hash)
{
    int mat;
    Aluno * posicao;
    printf("\nDigite a matricula do aluno que deseja excluir: ");
    scanf("%d",&mat);
    posicao=busca_exclusao(&Hash[0],mat);
    posicao->mat=-1;
    strcpy(posicao->nome,"xxxxxxxxxx");
    strcpy(posicao->email,"xxxxxxxxxx");


}

Aluno * busca_exclusao(Aluno ** Hash,int mat)
{
    int indice,testeTudo,cont=0;
    indice=calcula_indice(mat);
             testeTudo=indice;
    if (Hash[indice]==NULL)
    {
        printf("\n Não existe essa matricula na tabela.");
        return NULL;

    }else{
        while(Hash[indice] != NULL)
        {
            if (Hash[indice]->mat == mat)
            {
                return Hash[indice];
            }else{
                cont++;
                indice=calcula_indice(mat+cont);
                if(testeTudo==indice)
                {
                    printf("\n Nao existe essa matricula na tabela.\n");
                    return NULL;
                }

            }
            
        }
        
    }
}