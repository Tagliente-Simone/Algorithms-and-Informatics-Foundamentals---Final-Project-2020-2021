#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INF 327680000
#define parent(x) (x - 1) / 2
#define left(x) 2 * x + 1
#define right(x) 2 * x + 2
//useful macros

typedef struct graph {
    unsigned int index;
    unsigned int cost;
} graph;
//struct used to save the index of a graph and its value of the sum of his shortest paths

typedef struct heap {
  graph *rank;
  int dim;
  int size;
} heap;
//heap used to handle the ranking

unsigned int dijkstra(unsigned int d, unsigned int Graph[d][d]);
//it calculates the sum of shortest paths of a graph from node 0

void parsing(unsigned int d, unsigned int matrix[d][d], char in[], int i);
//it splits a string in numbers and put them in the matrix

int to_int(int dim, char num[]);
//custom atoi

heap heap_malloc(int k);
//it allocates memory for the heap 

void print_heap(heap heap);
//it prints the heap

void swap(graph *graph1, graph *graph2);
//it swaps two element of the heap

void heapify(heap *hp, int i, heap heap);
//it scans the heap and swaps element when the property is of the heap is violated

void insertNode(heap *hp, int index, int cost, heap heap);
//it inserts a new node in the heap without violating his property


int main(){

    heap heap;
    unsigned int d, sum = 0, k, i = 0, index = -1, param = 0;

    if(param){}
    param = scanf("%d %d", &d, &k);
  
    char line[d*10];
    unsigned int matrix[d][d];

    heap = heap_malloc(k);

    while(fgets(line,  sizeof(line), stdin) != NULL){
      switch(line[0]){
        case 'A' : {
          i = 0;
          break;
        }
        case 'T' : {
          print_heap(heap);
          printf("\n");
          break;
        }
        default : {
          parsing(d, matrix, line, i);
          i++;
          if(i == d){
            index++;
            sum = dijkstra(d, matrix);
            insertNode(&heap, index, sum, heap);
            }
          break;
        }
      }
    }
}

void parsing(unsigned int d, unsigned int matr[d][d], char in[], int index){

  char num[11] = "";
  int i = 0, done = 0, j = 0, number = 0, rig = 0;

  while(done == 0){
    if(in[i] == ','){
      num[j] = '\0';
      number = to_int(11, num);
      matr[index][rig] = number;
      rig++;
      i++;
      j = 0;
    }
    else if(in[i] == '\n'){
      num[j] = '\0';
      number = to_int(11, num);
      matr[index][rig] = number;
      done = 1;
    }
    else{
      num[j] = in[i];
      j++;
      i++;
    }
  }
}

int to_int(int dim, char num[]){
  int i = 0, res = 0;

  for(i = 0; num[i] != '\0'; i++){
    res = res*10 + num[i] - '0';
  }
  return res;
}

unsigned int dijkstra(unsigned int d, unsigned int Graph[d][d]){
  unsigned int cost[d][d], distance[d], pred[d];
  unsigned int visited[d], count, mindistance, nextnode = 0, i, j, sum = 0;

  if(pred[0]){}

  for (i = 0; i < d; i++)
    for (j = 0; j < d; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INF;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i < d; i++){
    distance[i] = cost[0][i];
    pred[i] = 0;
    visited[i] = 0;
  }

  distance[0] = 0;
  visited[0] = 1;
  count = 1;

  while (count < d - 1){
    mindistance = INF;

    for (i = 0; i < d; i++)
      if (distance[i] < mindistance && !visited[i]){
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < d; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]){
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
    }
  }
    return sum;
}

heap heap_malloc(int k){
    heap hp;

    hp.size = 0;
    hp.dim = k;
    hp.rank = malloc((k+1) * sizeof(graph));

    return hp;
}

void print_heap(heap heap){
  int i;

  for(i = 0; i < heap.dim && i < heap.size; i++){
    if(i == heap.dim - 1 || i == heap.size - 1){
      printf("%d", heap.rank[i].index);
    }
    else{
      printf("%d ", heap.rank[i].index);
    }
  }
}

void swap(graph *graph1, graph *graph2){
    graph temp = *graph1;

    *graph1 = *graph2;
    *graph2 = temp;
}

void heapify(heap *hp, int i, heap heap){
  
    int l, r, posmax;

    l = left(i);
    r = right(i);

    if(l <= hp->size && hp->rank[l].cost > hp->rank[i].cost){
      posmax = l;
    }
    else{
      posmax = i;
    }

    if(r <= hp->size && hp->rank[r].cost > hp->rank[posmax].cost){
      posmax = r;
    }

    if(posmax != i){
      swap(&(hp->rank[i]), &(hp->rank[posmax]));
      heapify(hp, posmax, heap);
    } 
}

void insertNode(heap *hp, int index, int cost, heap heap){
    graph graph;

    graph.cost = cost;
    graph.index = index;

    int i = hp->size;

    if(hp->size < hp->dim){
      i = (hp->size)++;
      while(i && graph.cost > hp->rank[parent(i)].cost){
        hp->rank[i] = hp->rank[parent(i)];
        i = parent(i);
      }
      hp->rank[i] = graph;
    }
    else{
      if(hp->rank[0].cost > cost){
        hp->rank[0].cost = cost;
        hp->rank[0].index = index;
        heapify(hp, 0, heap);
      }    
    }
}
