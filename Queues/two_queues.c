/*Write a Program to implement multiple queue i.e. two queues using
array and perform following operations on it. A. Addq, B. Delq, C.
Display Queue.*/


#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int arr[SIZE];
    int front1, rear1;
    int front2, rear2;
} MultiQueue;

// Initialize two queues
void initQueues(MultiQueue *mq) {
    mq->front1 = mq->rear1 = -1;
    mq->front2 = mq->rear2 = SIZE;
}

// Add element to queue
void AddQ(MultiQueue *mq, int queueNumber, int value) {
    if (mq->rear1 + 1 == mq->rear2) {
        printf("Queue Overflow! Cannot insert element.\n");
        return;
    }

    if (queueNumber == 1) {
        if (mq->front1 == -1) {
            mq->front1 = mq->rear1 = 0;
        } else {
            mq->rear1++;
        }
        mq->arr[mq->rear1] = value;
    } else if (queueNumber == 2) {
        if (mq->front2 == SIZE) {
            mq->front2 = mq->rear2 = SIZE - 1;
        } else {
            mq->rear2--;
        }
        mq->arr[mq->rear2] = value;
    } else {
        printf("Invalid queue number!\n");
    }
}

// Delete element from queue
void DelQ(MultiQueue *mq, int queueNumber) {
    if (queueNumber == 1) {
        if (mq->front1 == -1) {
            printf("Queue 1 Underflow! No element to delete.\n");
            return;
        }
        printf("Deleted from Queue 1: %d\n", mq->arr[mq->front1]);
        if (mq->front1 == mq->rear1) {
            mq->front1 = mq->rear1 = -1;
        } else {
            mq->front1++;
        }
    } else if (queueNumber == 2) {
        if (mq->front2 == SIZE) {
            printf("Queue 2 Underflow! No element to delete.\n");
            return;
        }
        printf("Deleted from Queue 2: %d\n", mq->arr[mq->front2]);
        if (mq->front2 == mq->rear2) {
            mq->front2 = mq->rear2 = SIZE;
        } else {
            mq->front2--;
        }
    } else {
        printf("Invalid queue number!\n");
    }
}

// Display queue elements
void Display(MultiQueue *mq, int queueNumber) {
    int i;

    if (queueNumber == 1) {
        if (mq->front1 == -1) {
            printf("Queue 1 is empty.\n");
            return;
        }
        printf("Queue 1 elements: ");
        for (i = mq->front1; i <= mq->rear1; i++) {
            printf("%d ", mq->arr[i]);
        }
        printf("\n");
    } else if (queueNumber == 2) {
        if (mq->front2 == SIZE) {
            printf("Queue 2 is empty.\n");
            return;
        }
        printf("Queue 2 elements: ");
        for (i = mq->front2; i >= mq->rear2; i--) {
            printf("%d ", mq->arr[i]);
        }
        printf("\n");
    } else {
        printf("Invalid queue number!\n");
    }
}

int main() {
    MultiQueue mq;
    int choice, queueNumber, value;

    initQueues(&mq);

    do {
        printf("\n--- Multiple Queue Menu ---\n");
        printf("1. AddQ\n");
        printf("2. DelQ\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &queueNumber);
                printf("Enter value to add: ");
                scanf("%d", &value);
                AddQ(&mq, queueNumber, value);
                break;
            case 2:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &queueNumber);
                DelQ(&mq, queueNumber);
                break;
            case 3:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &queueNumber);
                Display(&mq, queueNumber);
                break;
            case 4:
                printf("Exiting Program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
