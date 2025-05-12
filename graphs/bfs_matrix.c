#include<stdio.h>
#define MAX_VERTICES 20

void bfs(int graph[MAX_VERTICES][MAX_VERTICES], int start, int n) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    // Mark the start node as visited and enqueue it
    visited[start] = 1;
    queue[rear++] = start;
    printf("BFS traversal starting from vertex %d is: ", start);

    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        // Visit all adjacent vertices of the current vertex
        for (int i = 0; i < n; i++) {
            if (graph[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
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

    printf("Enter the starting vertex for BFS traversal: ");
    scanf("%d", &start);

    if (start >= n) {
        printf("Invalid starting vertex!\n");
        return 1;
    }

    bfs(graph, start, n);
    return 0;
}

/*
{0, 1, 0, 1},
{1, 0 ,1, 0},
{0, 1 ,0, 1},
{1, 0, 1, 0}
*/
