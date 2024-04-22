/*Algorithm
Step 1: SET STATUS = 1 (ready state) for each node in G

Step 2: Push the starting node A on the stack and set its STATUS = 2 (waiting state)

Step 3: Repeat Steps 4 and 5 until STACK is empty

Step 4: Pop the top node N. Process it and set its STATUS = 3 (processed state)

Step 5: Push on the stack all the neighbors of N that are in the ready state (whose STATUS = 1) and set their STATUS = 2 (waiting state)

[END OF LOOP]

Step 6: EXIT

Pseudocode
DFS(G,v)   ( v is the vertex where the search starts )    
        Stack S := {};   ( start with an empty stack )    
        for each vertex u, set visited[u] := false;    
        push S, v;    
        while (S is not empty) do    
           u := pop S;    
           if (not visited[u]) then    
              visited[u] := true;    
              for each unvisited neighbour w of uu    
                 push S, w;    
           end if    
        end while    
     END DFS()    */
     #include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

// Stack implementation for DFS
int stack[MAX_NODES];
int top = -1;

void push(int node) {
    if (top == MAX_NODES - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = node;
}

int pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

bool isStackEmpty() {
    return top == -1;
}

// DFS function
void DFS(int graph[MAX_NODES][MAX_NODES], int nodes, int start) {
    bool visited[MAX_NODES] = {false};

    push(start);

    while (!isStackEmpty()) {
        int current = pop();
        if (!visited[current]) {
            printf("%d ", current);
            visited[current] = true;
        }

        for (int i = nodes - 1; i >= 0; i--) {
            if (graph[current][i] && !visited[i]) {
                push(i);
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

    printf("DFS traversal starting from node %d: \n", start);
    DFS(graph, nodes, start);

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
*/