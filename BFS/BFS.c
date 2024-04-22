/*Algorithm
Step 1: SET STATUS = 1 (ready state) for each node in G

Step 2: Enqueue the starting node A and set its STATUS = 2 (waiting state)

Step 3: Repeat Steps 4 and 5 until QUEUE is empty

Step 4: Dequeue a node N. Process it and set its STATUS = 3 (processed state).

Step 5: Enqueue all the neighbours of N that are in the ready state (whose STATUS = 1) and set

their STATUS = 2

(waiting state)

[END OF LOOP]

Step 6: EXIT*/
#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

// Queue implementation for BFS
int queue[MAX_NODES];
int front = -1, rear = -1;

void enqueue(int node) {
    if (rear == MAX_NODES - 1) {
        printf("Queue is full\n");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = node;
}

int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    }
    int node = queue[front];
    front++;
    return node;
}

bool isQueueEmpty() {
    return front == -1 || front > rear;
}

// BFS function
void BFS(int graph[MAX_NODES][MAX_NODES], int nodes, int start) {
    bool visited[MAX_NODES] = {false};

    visited[start] = true;
    enqueue(start);

    while (!isQueueEmpty()) {
        int current = dequeue();
        printf("%d ", current);

        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = true;
                enqueue(i);
            }
        }
    }
}

int main() {
    int nodes, edges, start;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &nodes, &edges);

    int graph[MAX_NODES][MAX_NODES] = {0};
    printf("Enter the edges (from to): \n");
    for (int i = 0; i < edges; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        graph[from][to] = 1;
        graph[to][from] = 1; // Assuming undirected graph
    }

    printf("Enter the starting node: ");
    scanf("%d", &start);

    printf("BFS traversal starting from node %d: \n", start);
    BFS(graph, nodes, start);

    return 0;
}
/*Enter the number of nodes and edges: 6 7
Enter the edges (from to):
0 1
0 2
1 3
1 4
2 4
3 5
4 5
Enter the starting node: 0
BFS traversal starting from node 0:
0 1 2 3 4 5
*/