#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Queue structure
typedef struct {
    int items[MAX_VERTICES];
    int front, rear;
} Queue;

// Global variables
Node* adjList[MAX_VERTICES]; // Adjacency list
int visited[MAX_VERTICES];   // To track visited vertices

// Queue functions
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front >= q->rear) // only one element
        q->front = q->rear = -1;
    else
        q->front++;
    return value;
}

// Add edge in adjacency list
void addEdge(int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = adjList[src];
    adjList[src] = newNode;
}

// BFS function
void bfs(int start, int n) {
    Queue q;
    initQueue(&q);

    visited[start] = 1;
    enqueue(&q, start);

    printf("BFS Traversal starting from vertex %d: ", start);

    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        Node* temp = adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(&q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Main function
int main() {
    int n, edges, src, dest, start;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize adjacency list
    for (int i = 0; i < n; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
        addEdge(dest, src); // For undirected graph
    }

    printf("Enter starting vertex for BFS: ");
    scanf("%d", &start);

    bfs(start, n);

    return 0;
}
