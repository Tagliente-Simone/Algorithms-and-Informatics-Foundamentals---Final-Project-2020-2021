#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 327680000

typedef struct graph {
    unsigned int index;
    unsigned int cost;
    struct graph * next;
} graph;

typedef struct graph * pointer;

unsigned int Dijkstra(unsigned int d, unsigned int Graph[d][d]);
void parsing(unsigned int d, unsigned int matrix[d][d], char in[], int i);
void printMatrix(unsigned int d, unsigned int matrix[d][d]);
pointer createNode();
pointer push(pointer head, int index, int cost);
void printlist(pointer head);
void fillArray(int dim, int array[dim], pointer head);
void bubbleSort(pointer start);
void swap(pointer a, pointer b);

void bubbleSort(pointer start){
    int swapped;
    pointer ptr1;
    pointer lptr = NULL;
  
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do{
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr){
            if (ptr1->cost > ptr1->next->cost){ 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void swap(pointer a, pointer b){
    unsigned int cost = a->cost;
    unsigned int index = a->index;

    a->cost = b->cost;
    b->cost = cost;
    a->index = b->index;
    b->index = index;
}

void fillArray(int dim, int array[dim], pointer head){

    pointer tmp = head;
    int counter = 0;

    while(tmp != NULL){
      array[counter] = tmp -> index;
      tmp = tmp -> next;
      counter++;
    }
}

pointer createNode(){
    pointer temp;
    temp = (pointer)malloc(sizeof(graph));
    temp->next = NULL;
    return temp;
}

pointer push(pointer head, int index, int cost){
    pointer temp,p;
    
    temp = createNode();
    
    temp->index = index;
    temp->cost = cost;
    if(head == NULL){
        
        head = temp;
    }
    else{
        p  = head;
        while(p->next != NULL){
            p = p->next;
        }
        temp->next = p->next;
        p->next = temp;
    }
    return head;
}

void print_list(pointer head, int k) {
    pointer current = head;
    int counter = 0;

    while (current != NULL && counter < k) {
        printf("%d ", current->index);
        counter++;
        current = current->next;
    }
}

void printMatrix(unsigned int d, unsigned int matrix[d][d]){
    int i, j;

    for(i = 0; i < d; i++){
        for(j = 0; j < d; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void parsing(unsigned int d, unsigned int matr[d][d], char in[], int i){
  const char s[2] = ",";
  char *token;
  int j = 0, num = 55;
   
  token = strtok(in, s);
  
  while( token != NULL ) {
    num  = atoi(token); 
    matr[i][j] = num;
    token = strtok(NULL, s);
    j++;
  }
  
}

unsigned int Dijkstra(unsigned int d, unsigned int Graph[d][d]) {
  unsigned int cost[d][d], distance[d], pred[d];
  unsigned int visited[d], count, mindistance, nextnode = 0, i, j, sum = 0;

  if(pred[0]){}
  // Creating cost matrix
  for (i = 0; i < d; i++)
    for (j = 0; j < d; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INF;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i < d; i++) {
    distance[i] = cost[0][i];
    pred[i] = 0;
    visited[i] = 0;
  }

  distance[0] = 0;
  visited[0] = 1;
  count = 1;

  while (count < d - 1) {
    mindistance = INF;

    for (i = 0; i < d; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < d; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  for (i = 0; i < d; i++){
    if (i != 0) {
      if(distance[i] != INF){ 
        sum = sum + distance[i];
      }
      //printf("DISTANCE %d: %d\n", i, distance[i]);
    }
    //printf("%d ", sum);
    //printf("\n");
  }
    return sum;

}

int main(){
    pointer firstGraph = NULL;
    unsigned int d, sum = 0, k, i = 0, index = 0, param = 0;
    char line[50000];

    if(param){}
    param = scanf("%d %d", &d, &k);
    printf("%d, %d\n", d, k);
    unsigned int matrix[d][d];
    while(fgets(line,  sizeof(line), stdin) != NULL){
      switch(line[0]){
        case 'A' : {
          //printf("AggiungiGrafo\n");
          i = 0;
          break;
        }
        case 'T' : {
          bubbleSort(firstGraph);
          print_list(firstGraph, k);
          printf("\n");
          //fillArray(index, array, firstGraph);
          //quicksort(array, 0, index - 1);
          break;
        }
        default : {
          parsing(d, matrix, line, i);
          i++;
          if(i == d){
            //printMatrix(d, matrix);
            sum = Dijkstra(d, matrix);
            firstGraph = push(firstGraph, index, sum);
            index++;
            
          }
          break;
        }
      }
    }
}
