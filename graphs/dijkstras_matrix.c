#include <stdio.h>
#define INF 9999
#define MAX 100

int minDistance(int dist[], int vset[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (vset[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void display(int dist[], int src, int V) {
    printf("\nShortest distances from Source Vertex %d:\n", src);
    printf("Vertex \t Distance\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void Dijkstras(int G[MAX][MAX], int src, int V) {
    int dist[MAX], vset[MAX];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        vset[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, vset, V);
        if (u == -1) break; // No reachable vertex remaining
        vset[u] = 1;

        for (int j = 0; j < V; j++) {
            if (!vset[j] && G[u][j] && dist[u] != INF &&
                dist[u] + G[u][j] < dist[j]) {
                dist[j] = dist[u] + G[u][j];
            }
        }
    }

    display(dist, src, V);
}

int main() {
    int V, G[MAX][MAX], source;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    printf("Enter the source vertex (0 to %d): ", V - 1);
    scanf("%d", &source);

    if (source < 0 || source >= V) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    Dijkstras(G, source, V);

    return 0;
}
