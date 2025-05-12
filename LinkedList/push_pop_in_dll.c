#include <stdio.h>
#include <stdlib.h>

// Node structure for Doubly Linked List
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* top = NULL;  // Top of the stack

// Push operation
void push(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = top;

    if (top != NULL)
        top->prev = newNode;

    top = newNode;
    printf("%d pushed onto the stack.\n", value);
}

// Pop operation
void pop() {
    if (top == NULL) {
        printf("Stack is empty. Cannot pop.\n");
        return;
    }

    struct Node* temp = top;
    printf("%d popped from the stack.\n", temp->data);

    top = top->next;
    if (top != NULL)
        top->prev = NULL;

    free(temp);
}

// Display stack from top to bottom
void display() {
    struct Node* temp = top;
    if (temp == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack (Top to Bottom): ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Driver code
int main() {
    int choice, value;

    do {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
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
    } while(choice != 4);

    return 0;
}
