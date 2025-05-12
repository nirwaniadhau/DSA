#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Check if queue is full
int isFull(Queue* q) {
    return ((q->rear + 1) % MAX == q->front);
}

// Enqueue operation
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (isEmpty(q))
        q->front = q->rear = 0;
    else
        q->rear = (q->rear + 1) % MAX;

    q->items[q->rear] = value;
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % MAX;
    return value;
}

// Replace function
void replace(Queue* q, int oldItem, int newItem) {
    Queue tempQueue;
    initQueue(&tempQueue);

    int replaced = 0;

    while (!isEmpty(q)) {
        int current = dequeue(q);
        if (current == oldItem && !replaced) {
            enqueue(&tempQueue, newItem);
            replaced = 1;
        } else {
            enqueue(&tempQueue, current);
        }
    }

    // Copy back to original queue
    while (!isEmpty(&tempQueue)) {
        enqueue(q, dequeue(&tempQueue));
    }
}

// Function to display the queue
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    int n, value, oldItem, newItem;

    // Input number of elements to add to the queue
    printf("Enter the number of elements to enqueue: ");
    scanf("%d", &n);

    // Adding elements to the queue
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);
        enqueue(&q, value);
    }

    // Display the queue before replacement
    printf("Before replace:\n");
    display(&q);

    // Input the item to replace and the new item
    printf("Enter the item to replace: ");
    scanf("%d", &oldItem);
    printf("Enter the new item to replace with: ");
    scanf("%d", &newItem);

    // Replace the old item with the new item
    replace(&q, oldItem, newItem);

    // Display the queue after replacement
    printf("After replace:\n");
    display(&q);

    return 0;
}
