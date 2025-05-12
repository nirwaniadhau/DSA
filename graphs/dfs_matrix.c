#include <stdio.h>
#define MAX_VERTICES 20

void dfs(int graph[MAX_VERTICES][MAX_VERTICES], int start, int n) {
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES];
    int top = -1;

    visited[start] = 1;
    stack[++top] = start;

    printf("DFS traversal starting from vertex %d is: ", start);

    while (top != -1) {
        int vertex = stack[top--];
        printf("%d ", vertex);

        for (int i = n - 1; i >= 0; i--) { // Check in reverse order to match stack behavior
            if (graph[vertex][i] == 1 && !visited[i]) {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

int main() {
    int n, start;
    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &n);

    printf("Enter the adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the starting vertex for DFS traversal: ");
    scanf("%d", &start);

    if (start >= n) {
        printf("Invalid starting vertex!\n");
        return 1;
    }

    dfs(graph, start, n);

    return 0;
}
