#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//máximo de itens: 100
//capacidade: 500

typedef struct{
    int prioridade;
    int peso;
    double fator;
}item;

/*void imprimir_item(item *ITEM,int quantidade,int capacidade){
    printf("\nCapacidade:%d\n",capacidade);
    printf("\nItens:\n\n");
    for(int i=0;i<quantidade;i++){
        printf("Item [%d]\nPeso:       %d\nPrioridade: %d\n\n",i+1,ITEM[i].peso,ITEM[i].prioridade);
    }
}*/

int ComparaFator(const void *a, const void *b){

    const item *elem1 = (const item *)a;
    const item *elem2 = (const item *)b;

    if (elem1->fator > elem2->fator){
        return -1;
    }
    else if (elem1->fator < elem2->fator){
        return 1;
    }else{
        return 0;
    }
}

void ordenar(int quantidade, item *ITEM){
    double fator[2];
    item auxiliar;
    for(int i=0;i<quantidade-1;i++){
        for(int k=0;k<quantidade-i-1;k++){
            fator[0] = (double)(ITEM[k].prioridade / ITEM[k].peso);
            fator[1] = (double)(ITEM[k+1].prioridade / ITEM[k+1].peso);
            if(fator[0] <= fator[1]){
                if(fator[0]!=fator[1] && ITEM[k].peso > ITEM[k+1].peso){
                    auxiliar = ITEM[k];
                    ITEM[k] = ITEM[k+1];
                    ITEM[k+1] = auxiliar;
                }
            }
        }
    }
    /*printf("\nFator ordenado de prioridade sobre peso:\n");
    for(int i=0;i<quantidade;i++){
        printf("%.4f ",(float)ITEM[i].prioridade/ITEM[i].peso);
    }
    printf("\n\nPrioridades ordenadas em relacao ao fator:\n");
    for(int i=0;i<quantidade;i++){
        printf("%d ",ITEM[i].prioridade);
    }
    printf("\n\nPesos ordenados em relacao ao fator:\n");
    for(int i=0;i<quantidade;i++){
        printf("%d ",ITEM[i].peso);
    }*/
}

int mochila(int capacidade,item *ITEM,int quantidade, double *time_spent){
    int pesoTotal=0, prioridadeTotal=0, i=0;

    //ordenar(quantidade,ITEM);
    qsort(ITEM,quantidade,sizeof(item),ComparaFator);

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


int main() {
    int p=0, solucao=0;
    double media=0, mediaS=0;
    FILE *arquivo = fopen("MOPT.txt","w+");
    FILE *file = fopen("m2ga.txt","r");
    
    while(p<100){
        int capacidade = 500;
        int quantidade = 1000;
        item *ITEM = malloc(quantidade*sizeof(item));

        for (int i=0;i<quantidade;i++){
            fscanf(file,"%d %d",&ITEM[i].peso,&ITEM[i].prioridade);
            ITEM[i].fator = (double)(ITEM[i].prioridade/ITEM[i].peso);
        }

        //imprimir_item(ITEM,quantidade,capacidade);

        double tempo = 0.0;

        solucao = mochila(capacidade,ITEM,quantidade,&tempo);

        //printf("\n\nSolucao do MOPT: %d\n\n",solucao);
        free(ITEM);

        //printf("\nTempo decorrido: %lf\n\n\n",tempo);

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