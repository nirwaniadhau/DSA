#include <stdio.h>
#include <limits.h>
#define MAX 100

int minKey(int key[], int mstSet[], int nodes) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < nodes; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int graph[MAX][MAX], int nodes) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < nodes; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[MAX][MAX], int nodes) {
    int parent[MAX];
    int key[MAX];
    int mstSet[MAX];

    for (int i = 0; i < nodes; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < nodes - 1; count++) {
        int u = minKey(key, mstSet, nodes);
        mstSet[u] = 1;

        for (int v = 0; v < nodes; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printMST(parent, graph, nodes);
}

int main() {
    int graph[MAX][MAX], nodes, edges, u, v, w;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for(int i=0; i<nodes; i++)
        for(int j=0; j<nodes; j++)
            graph[i][j] = 0;

    printf("Enter edges in format: src dest weight\n");
    for(int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    primMST(graph, nodes);
    return 0;
}
