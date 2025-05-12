#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Front and Rear pointers for the queue
struct Node* front = NULL;
struct Node* rear = NULL;

// Function to add (enqueue) an element to the queue
void enqueue(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (rear == NULL) {
        // Queue is empty
        front = rear = newNode;
    } else {
        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
    }
    printf("%d added to the queue\n", value);
}

// Function to delete (dequeue) an element from the queue
void dequeue() {
    if (front == NULL) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }

    struct Node* temp = front;
    printf("%d removed from the queue\n", temp->data);

    front = front->next;

    if (front != NULL) {
        front->prev = NULL;
    } else {
        rear = NULL; // Queue became empty
    }

    free(temp);
}

// Function to display the queue
void display() {
    struct Node* temp = front;
    if (temp == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Driver code
int main() {
    int choice, value;

    do {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
