#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
typedef struct {
    int source;
    int dest;
    int weight;
} Edge;

// Comparator for sorting edges by weight
int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

// Function to find parent of a node with path compression
int findParent(int vertex, int parent[]) {
    if (parent[vertex] == vertex)
        return vertex;
    return parent[vertex] = findParent(parent[vertex], parent);
}

// Kruskal's Algorithm
void kruskal(Edge edges[], int V, int E) {
    // Sort edges by weight
    qsort(edges, E, sizeof(Edge), compareEdges);

    int* parent = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
        parent[i] = i;

    Edge* mst = (Edge*)malloc((V - 1) * sizeof(Edge));
    int count = 0, i = 0;

    while (count < V - 1 && i < E) {
        Edge currentEdge = edges[i++];

        int srcParent = findParent(currentEdge.source, parent);
        int destParent = findParent(currentEdge.dest, parent);

        if (srcParent != destParent) {
            mst[count++] = currentEdge;
            parent[srcParent] = destParent;
        }
    }

    printf("\nMinimum Spanning Tree Edges:\n");
    for (int i = 0; i < count; i++)
        printf("%d -- %d == %d\n", mst[i].source, mst[i].dest, mst[i].weight);

    free(parent);
    free(mst);
}

// Main Function
int main() {
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    Edge* edges = (Edge*)malloc(E * sizeof(Edge));

    printf("Enter edges in format (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].source, &edges[i].dest, &edges[i].weight);
    }

    kruskal(edges, V, E);

    free(edges);
    return 0;
}
