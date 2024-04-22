#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_NODES 100

void serialDFS(int graph[MAX_NODES][MAX_NODES], int nodes, int source) {
    int visited[MAX_NODES] = {0};
    int stack[MAX_NODES];
    int top = -1;
    
    visited[source] = 1;
    stack[++top] = source;
    
    while (top != -1) {
        int current = stack[top--];
        printf("%d ", current);
        
        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                stack[++top] = i;
            }
        }
    }
}

void parallelDFS(int graph[MAX_NODES][MAX_NODES], int nodes, int source) {
    int visited[MAX_NODES] = {0};
    int stack[MAX_NODES];
    int top = -1;
    
    visited[source] = 1;
    stack[++top] = source;
    
    while (top != -1) {
        #pragma omp parallel for
        for (int j = top; j >= 0; j--) {
            int current = stack[j];
            #pragma omp parallel for
            for (int i = 0; i < nodes; i++) {
                if (graph[current][i] && !visited[i]) {
                    int old_val = __sync_val_compare_and_swap(&visited[i], 0, 1);
                    if (old_val == 0) { // If the node was not visited
                        int pos = __sync_fetch_and_add(&top, 1);
                        stack[pos + 1] = i;
                        printf("%d ", i);
                    }
                }
            }
        }
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
    
    printf("\nSerial DFS: ");
    double start_serial = omp_get_wtime();
    serialDFS(graph, nodes, source);
    double end_serial = omp_get_wtime();
    printf("\nSerial DFS Execution Time: %f seconds\n", end_serial - start_serial);
    
    printf("\nParallel DFS: ");
    double start_parallel = omp_get_wtime();
    parallelDFS(graph, nodes, source);
    double end_parallel = omp_get_wtime();
    printf("\nParallel DFS Execution Time: %f seconds\n", end_parallel - start_parallel);
    
    return 0;
}
/*Enter the number of nodes: 4
Enter the adjacency matrix (0 for no edge, 1 for edge):
0 1 1 0
0 0 1 0
1 0 0 1
0 0 0 1
Enter the source vertex: 0
*/