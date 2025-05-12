

#include <stdio.h>
#define MAX 100

typedef struct {
    int soldiers[MAX];
    int size;
    int front;
} CircularQueue;

// Initialize the circular queue
void initQueue(CircularQueue *q) {
    q->size = 0;
    q->front = 0;
}

// Add a soldier
void enqueue(CircularQueue *q, int value) {
    if (q->size == MAX) {
        printf("Queue Overflow!\n");
        return;
    }
    int rear = (q->front + q->size) % MAX;
    q->soldiers[rear] = value;
    q->size++;
}

// Remove a soldier at front
int dequeue(CircularQueue *q) {
    if (q->size == 0) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int value = q->soldiers[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return value;
}

// Remove a soldier at a given position
void removeAt(CircularQueue *q, int pos) {
    int idx = (q->front + pos) % MAX;
    for (int i = idx; i != (q->front + q->size - 1) % MAX; i = (i + 1) % MAX) {
        int next = (i + 1) % MAX;
        q->soldiers[i] = q->soldiers[next];
    }
    q->size--;
}

// Josephus Simulation
void josephusCircularQueue(int n, int m, int x) {
    CircularQueue q;
    initQueue(&q);

    // Fill soldiers
    for (int i = 1; i <= n; i++) {
        enqueue(&q, i);
    }

    // Adjust starting point
    q.front = (q.front + x - 1) % MAX;

    printf("Order of elimination:\n");

    int current = 0; // relative position from front


    //Loop continues until only one soldier is left in the queue
    while (q.size > 1) {
        current = (current + m - 1) % q.size;  // current points to the soldier to be eliminated.
        int idx = (q.front + current) % MAX;  //idx gives the real array position of the soldier to remove.
        printf("%d ", q.soldiers[idx]);
        removeAt(&q, current);
    }

    // Only one soldier left
    printf("\nThe soldier who will seek help is: %d\n", q.soldiers[q.front]);
}

int main() {
    int n, m, x;

    printf("Enter number of soldiers: ");
    scanf("%d", &n);
    printf("Enter counting number (m): ");
    scanf("%d", &m);
    printf("Enter starting position (x): ");
    scanf("%d", &x);

    josephusCircularQueue(n, m, x);

    return 0;
}
