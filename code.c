// Dijkstra's Algorithm in C

#include <stdio.h>
#define INF 32768
#define MAX 10



int Dijkstra(int d, int Graph[d][d]);
void parsing(int d, int matrix[d][d]);
void printMatrix(int d, int matrix[d][d]);

void printMatrix(int d, int matrix[d][d]){
    int i, j;

    for(i = 0; i < d; i++){
        for(j = 0; j < d; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void parsing(int d, int matr[d][d]){


}

int Dijkstra(int d, int Graph[d][d]) {
  int cost[d][d], distance[d], pred[d];
  int visited[d], count, mindistance, nextnode, i, j, sum = 0;

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

  // Printing the distance
  for (i = 0; i < d; i++)
    if (i != 0) {
      sum = sum + distance[i];
    }
    printf("%d\n",sum);
    return sum;

}


int main(){
    int d, sum, k;
    char line[3000];

    scanf("%d,%d", &d, &k);

    int matrix[d][d];


    while(fgets(line,  sizeof(line), stdin)){
        parsing(d, matrix);
        printMatrix(d, matrix);
    }
    Dijkstra(d, matrix);
}
