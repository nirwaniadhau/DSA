#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert a node into a sorted list
void sortedInsert(struct Node** head, struct Node* newNode) {
    if (*head == NULL || (*head)->data > newNode->data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int n, value;

    printf("Enter number of initial elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the value at position %d: ", i + 1);
        scanf("%d", &value);
        struct Node* newNode = createNode(value);
        sortedInsert(&head, newNode);
    }

    printf("\nOriginal Sorted List: ");
    printList(head);

    printf("Enter the value to insert into the sorted list: ");
    scanf("%d", &value);
    struct Node* extraNode = createNode(value);
    sortedInsert(&head, extraNode);

    printf("Updated Sorted List: ");
    printList(head);

    return 0;
}
