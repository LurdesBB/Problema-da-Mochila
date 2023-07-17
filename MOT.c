#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//máximo de itens: 100
//capacidade: 500

typedef struct{
    int prioridade;
    int peso;
}item;

/*void imprimir_item(item *ITEM,int capacidade,int quantidade){
    printf("\nCapacidade:%d\n",capacidade);
    printf("\nItens:\n\n");
    for(int i=0;i<quantidade;i++){
        printf("Item [%d]\nPeso:       %d\nPrioridade: %d\n\n",i+1,ITEM[i].peso,ITEM[i].prioridade);
    }
}*/

void ordenar(int quantidade,item *ITEM){
    item auxiliar;
    for(int i=0;i<quantidade-1;i++){
        for(int k=0;k<quantidade-i-1;k++){
            if(ITEM[k].peso <= ITEM[k+1].peso){
                if(ITEM[k].peso!=ITEM[k+1].peso || ITEM[k].prioridade < ITEM[k+1].prioridade){
                    auxiliar = ITEM[k];
                    ITEM[k] = ITEM[k+1];
                    ITEM[k+1] = auxiliar;   
                }
            }
        }
    }
    /*printf("\nPesos ordenados:\n");
    for(int i=0;i<quantidade;i++){
        printf("%d ",ITEM[i].peso);
    }
    printf("\n\nPrioridades ordenadas em relacao ao peso:\n");
    for(int i=0;i<quantidade;i++){
        printf("%d ",ITEM[i].prioridade);
    }*/
}

int mochila(int capacidade,item *ITEM,int quantidade, double *time_spent){
    int pesoTotal=0, prioridadeTotal=0, i=0;

    ordenar(quantidade,ITEM);
    clock_t begin = clock();

    while(i<quantidade){
        if(pesoTotal + ITEM[i].peso > capacidade){
            i++;
        }else{
            pesoTotal += ITEM[i].peso;
            prioridadeTotal += ITEM[i].prioridade;
        }
    }
    clock_t end = clock();
    *time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("\nTempo decorrido: %lf\n\n\n",*time_spent);
    return prioridadeTotal;
}

int main(){
    int p=0, solucao=0;
    double mediaS=0, media=0;
    FILE *file = fopen("G1.txt","r");
    FILE *arquivo = fopen("MOT.txt","w+");
    
    while(p<100){
        int capacidade = 500;
        int quantidade = 10000;
        item *ITEM = malloc(quantidade*sizeof(item)); 

        for (int i=0;i<quantidade;i++){
            fscanf(file,"%d %d",&ITEM[i].peso,&ITEM[i].prioridade);
        }

        //imprimir_item(ITEM,capacidade,quantidade);

        double tempo = 0.0;
        
        solucao = mochila(capacidade,ITEM,quantidade,&tempo);

        //printf("\n\nSolucao do MOT: %d\n\n",solucao);
        free(ITEM);

        fprintf(arquivo,"%d %lf\n",solucao,tempo);
        media += tempo;
        mediaS += solucao;
        p++;
    }

    media /= 100;
    mediaS /= 100;

    printf("\nMedia de tempo: %lf",media);
    printf("\nMedia da solucao: %.2f",mediaS);
    fclose(file);
    fclose(arquivo);
    return 0;
}