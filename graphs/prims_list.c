#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Create node
Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Add edge (undirected)
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Find vertex with minimum key value, from the set of vertices not yet included in MST
int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Prim's algorithm
void primMST(Graph* graph) {
    int V = graph->numVertices;
    int parent[V]; // Store MST
    int key[V];    // Key values to pick minimum weight edge
    int mstSet[V]; // Vertices included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    // Start from vertex 0
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the min key vertex not yet included in MST
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;

        // Update key and parent of adjacent vertices
        Node* temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->dest;
            int w = temp->weight;

            if (mstSet[v] == 0 && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, key[i]);
}

// Free memory
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->adjLists);
    free(graph);
}

// Main
int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    Graph* graph = createGraph(V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges as (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printf("Minimum Spanning Tree using Prim's Algorithm:\n");
    primMST(graph);

    freeGraph(graph);
    return 0;
}
