//
// Created by Simone Tagliente on 02/08/2021.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct graph {
    int index;
    int cost;
    struct graph * next;
} graph;

int * parser(char str[], int dim);
void inputScan(int dim);

int main(){
    int d, k;
    scanf("%d,%d", &d, &k);
    inputScan(d);
}

void inputScan(int dim){
    int * singleMatrix[dim];
    int count = 0;
    char str[3000];
    
    int done = 0;
    
    while(!done){
        fflush(stdin);
        fgets(str, 3000, stdin);
        switch(str[0]){
            case 'A': {
                //crea grafo
            }
            case 'T' : {
                done = 1;
                //fai classifica
            }
            default : {
            singleMatrix[count] = parser(str, dim);
            }
        }
    }
}

int * parser(char str[], int dim){

    int counter1, counter2, index;
    char number[11];
    int *array = malloc(sizeof(dim));

    index = 0;
    counter1 = -1;
    counter2 = 0;

    do{
        counter1++;
        if(str[counter1] == ',' || str[counter1] == '\n'){
            array[index] = atoi(number);        
            counter2 = 0;
            index++;
            memset(number,0,sizeof(number));
        }
        else{
            number[counter2] = str[counter1];
            counter2++;
        }
    } while(str[counter1] != '\n');
    
    return array;
}



