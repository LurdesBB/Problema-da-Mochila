#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEM 100
#define MAX_PESO 191
#define MAX_PRIORIDADE 91

//máximo de itens: 100
//peso máximo: 191
//prioridade máxima: 90
//capacidade: 500

typedef struct{
    int prioridade;
    int peso;
} item;

int main()
{
    srand(time(NULL));
    for(int i=0;i<100;i++){
        item *ITEM = malloc(1000*sizeof(item));
        FILE *file = fopen("M2.txt","a");

        for(int k=0;k<1000;k++){
            ITEM[k].peso = rand() % 301+200;
            ITEM[k].prioridade = rand() % 91+10;
            fprintf(file,"%d %d\n",ITEM[k].peso,ITEM[k].prioridade);
        }
        fclose(file);
        free(ITEM);
    }
    return 0;
}