//Copyright 2013 Ciano Saraiva <saraiva.ufc@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
//A.txt && B.txt == 2 MB && RES.txt == 6 MB
#define fori(a,b) for(int a=0 ; a < b ; a++)

FILE *Matriz_1;
FILE *Matriz_2;
FILE *Matriz_RES;

typedef struct
{
    int **matriz;
} Matriz;

Matriz matriz[3];
int tam;

//Prototipo das Funções
void imprime_matriz(Matriz matriz,int tam, FILE *Arquivo);
int ** cria_matriz(int tam);
void Multiplica_Rapida();

pthread_t threads[8];

int ** cria_matriz(int tam)
{
    int **matriz=(int **) malloc (tam * sizeof(int*));
    fori(i,tam)
    {
        matriz[i]=(int *) malloc (tam * sizeof(int));
    }
    fori(i,tam)
    {
        fori(k,tam)
        {
            matriz[i][k] = (int) rand()%100;
        }
    }
    return matriz;
}
void *Multiplica_Rapida_1(void *arg)
{
    for(int i=0 ; i<tam*0.50 ; i++)
    {
        for(int k=0 ; k<tam*0.25 ; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}
void *Multiplica_Rapida_2(void *arg)
{
    for(int i=0 ; i<tam*0.50 ; i++)
    {
        for(int k=tam*0.25 ; k<tam*0.50 ; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}
void *Multiplica_Rapida_3(void *arg)
{
    for(int i=0 ; i<tam*0.50 ; i++)
    {
        for(int k=tam*0.50 ; k<tam*0.75 ; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}
void *Multiplica_Rapida_4(void *arg)
{
    for(int i=0 ; i<tam*0.50; i++)
    {
        for(int k=tam*0.75 ; k<tam; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}
void *Multiplica_Rapida_5(void *arg)
{
    for(int i=tam*0.50 ; i<tam; i++)
    {
        for(int k=0; k<tam*0.25; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}
void *Multiplica_Rapida_6(void *arg)
{
    for(int i=tam*0.50 ; i<tam; i++)
    {
        for(int k=tam*0.25 ; k<tam*0.50; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}
void *Multiplica_Rapida_7(void *arg)
{
    for(int i=tam*0.50 ; i<tam; i++)
    {
        for(int k=tam*0.50 ; k<tam*0.75; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}
void *Multiplica_Rapida_8(void *arg)
{
    for(int i=tam*0.50 ; i<tam; i++)
    {
        for(int k=tam*0.75 ; k<tam; k++)
        {
            for(int w=0 ; w<tam ; w++)
            {
                matriz[2].matriz[i][k] += matriz[0].matriz[i][w] * matriz[1].matriz[w][k];
            }
        }
    }
}

void imprime_matriz(Matriz matriz,int tam, FILE *Arquivo)
{
    fori(i,tam)
    {
        fori(k,tam)
        {
            fprintf(Arquivo,"%d ",matriz.matriz[i][k]);
        }
        fprintf(Arquivo,"\n");
    }
}

int main()
{
    srand(time(NULL));
    Matriz_1=fopen("A.txt","w+");
    Matriz_2=fopen("B.txt","w+");
    Matriz_RES=fopen("RES.txt","w+");
    printf("Digite o tamanho das Matrizes:");
    scanf("%d",&tam);
    //Matriz matrix_Resultado;
    matriz[0].matriz=cria_matriz(tam);
    matriz[1].matriz=cria_matriz(tam);
    matriz[2].matriz=(int **) malloc(tam * sizeof(int*));
    fori(i,tam)
    {
        matriz[2].matriz[i]=(int *) malloc(tam * sizeof(int));
    }
    //Criando as Threads
    pthread_create(&(threads[0]), NULL, Multiplica_Rapida_1, NULL);
    pthread_create(&(threads[1]), NULL, Multiplica_Rapida_2, NULL);
    pthread_create(&(threads[2]), NULL, Multiplica_Rapida_3, NULL);
    pthread_create(&(threads[3]), NULL, Multiplica_Rapida_4, NULL);
    pthread_create(&(threads[4]), NULL, Multiplica_Rapida_5, NULL);
    pthread_create(&(threads[5]), NULL, Multiplica_Rapida_6, NULL);
    pthread_create(&(threads[6]), NULL, Multiplica_Rapida_7, NULL);
    pthread_create(&(threads[7]), NULL, Multiplica_Rapida_8, NULL);
    //Matando as Threads
    for(int i=0 ; i< 8 ; i++)
        pthread_join(threads[i], NULL);

    //criando arquivos
    imprime_matriz(matriz[0],tam,Matriz_1);
    imprime_matriz(matriz[1],tam,Matriz_2);
    imprime_matriz(matriz[2],tam,Matriz_RES);
    //fechando arquivos
    fclose(Matriz_1);
    fclose(Matriz_2);
    fclose(Matriz_RES);
    return 0;
}
