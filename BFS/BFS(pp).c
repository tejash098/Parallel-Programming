#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_NODES 100

void serialBFS(int graph[MAX_NODES][MAX_NODES], int nodes, int source) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = -1, rear = -1;
    
    visited[source] = 1;
    queue[++rear] = source;
    
    while (front != rear) {
        int current = queue[++front];
        printf("%d ", current);
        
        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

void parallelBFS(int graph[MAX_NODES][MAX_NODES], int nodes, int source) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = -1, rear = -1;
    
    visited[source] = 1;
    queue[++rear] = source;
    
    while (front != rear) {
        #pragma omp parallel for
        for (int j = front + 1; j <= rear; j++) {
            int current = queue[j];
            #pragma omp parallel for
            for (int i = 0; i < nodes; i++) {
                if (graph[current][i] && !visited[i]) {
                    int old_val = __sync_val_compare_and_swap(&visited[i], 0, 1);
                    if (old_val == 0) { // If the node was not visited
                        int pos = __sync_fetch_and_add(&rear, 1);
                        queue[pos + 1] = i;
                        printf("%d ", i);
                    }
                }
            }
        }
        front = rear;
    }
}
int main() {
    int graph[MAX_NODES][MAX_NODES];
    int nodes, source;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);
    
    printf("Enter the adjacency matrix (0 for no edge, 1 for edge):\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    
    printf("\nSerial BFS: ");
    double start_serial = omp_get_wtime();
    serialBFS(graph, nodes, source);
    double end_serial = omp_get_wtime();
    printf("\nSerial BFS Execution Time: %f seconds\n", end_serial - start_serial);
    
    printf("\nParallel BFS: ");
    double start_parallel = omp_get_wtime();
    parallelBFS(graph, nodes, source);
    double end_parallel = omp_get_wtime();
    printf("\nParallel BFS Execution Time: %f seconds\n", end_parallel - start_parallel);
    
    return 0;
}