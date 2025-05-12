#include <stdio.h>
#include <stdlib.h>

// Node definition
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Append a node at the end of a list
void append(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

// Print a doubly linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Case (a): Append List A at the START of List B
void appendAtStart(struct Node** listA, struct Node** listB) {
    if (*listA == NULL) return;
    if (*listB == NULL) {
        *listB = *listA;
        return;
    }

    // Find tail of A
    struct Node* tailA = *listA;
    while (tailA->next != NULL)
        tailA = tailA->next;

    tailA->next = *listB;
    (*listB)->prev = tailA;

    *listB = *listA;  // Update head of B
}

// Case (b): Append List A at the END of List B
void appendAtEnd(struct Node** listA, struct Node** listB) {
    if (*listA == NULL) return;
    if (*listB == NULL) {
        *listB = *listA;
        return;
    }

    // Find tail of B
    struct Node* tailB = *listB;
    while (tailB->next != NULL)
        tailB = tailB->next;

    tailB->next = *listA;
    (*listA)->prev = tailB;
}

// Driver code
int main() {
    struct Node* listA = NULL;
    struct Node* listB = NULL;

    // Creating List A
    append(&listA, 1);
    append(&listA, 2);
    append(&listA, 3);

    // Creating List B
    append(&listB, 4);
    append(&listB, 5);
    append(&listB, 6);

    printf("List A: ");
    printList(listA);
    printf("List B: ");
    printList(listB);

    // Uncomment one of the two options below:

    // Case A: Append A at START of B
    appendAtStart(&listA, &listB);
    printf("After appending List A at START of List B:\n");

    // // Case B: Append A at END of B
    // appendAtEnd(&listA, &listB);
    // printf("After appending List A at END of List B:\n");

    printList(listB);
    return 0;
}
