/*Write a Program to implement circular double ended queue where user
can add and remove the elements from both front and rear of the queue*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // You can change the size

typedef struct {
    int arr[MAX];
    int front;
    int rear;
} CircularDeque;

// Initialize the deque
void initDeque(CircularDeque* dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Check if the deque is full
int isFull(CircularDeque* dq) {
    return ((dq->front == 0 && dq->rear == MAX - 1) || (dq->front == dq->rear + 1));
}

// Check if the deque is empty
int isEmpty(CircularDeque* dq) {
    return (dq->front == -1);
}

// Insert element at the front
void insertFront(CircularDeque* dq, int value) {
    if (isFull(dq)) {
        printf("Overflow! Cannot insert at front.\n");
        return;
    }

    // First element insertion
    if (isEmpty(dq)) {
        dq->front = dq->rear = 0;
    }
    // Circularly move front backward
    else if (dq->front == 0) {
        dq->front = MAX - 1;
    } else {
        dq->front--;
    }

    dq->arr[dq->front] = value;
}

// Insert element at the rear
void insertRear(CircularDeque* dq, int value) {
    if (isFull(dq)) {
        printf("Overflow! Cannot insert at rear.\n");
        return;
    }

    // First element insertion
    if (isEmpty(dq)) {
        dq->front = dq->rear = 0;
    }
    // Circularly move rear forward
    else if (dq->rear == MAX - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }

    dq->arr[dq->rear] = value;
}

// Delete element from the front
void deleteFront(CircularDeque* dq) {
    if (isEmpty(dq)) {
        printf("Underflow! Cannot delete from front.\n");
        return;
    }

    printf("Deleted from front: %d\n", dq->arr[dq->front]);

    // Only one element
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    }
    // Move front forward
    else if (dq->front == MAX - 1) {
        dq->front = 0;
    } else {
        dq->front++;
    }
}

// Delete element from the rear
void deleteRear(CircularDeque* dq) {
    if (isEmpty(dq)) {
        printf("Underflow! Cannot delete from rear.\n");
        return;
    }

    printf("Deleted from rear: %d\n", dq->arr[dq->rear]);

    // Only one element
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    }
    // Move rear backward
    else if (dq->rear == 0) {
        dq->rear = MAX - 1;
    } else {
        dq->rear--;
    }
}

// Display the deque
void display(CircularDeque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deque elements: ");
    int i = dq->front;
    while (1) {
        printf("%d ", dq->arr[i]);
        if (i == dq->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    CircularDeque dq;
    int choice, value;

    initDeque(&dq);

    do {
        printf("\n--- Circular Double Ended Queue Operations ---\n");
        printf("1. Insert at front\n");
        printf("2. Insert at rear\n");
        printf("3. Delete from front\n");
        printf("4. Delete from rear\n");
        printf("5. Display deque\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(&dq, value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(&dq, value);
                break;
            case 3:
                deleteFront(&dq);
                break;
            case 4:
                deleteRear(&dq);
                break;
            case 5:
                display(&dq);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
