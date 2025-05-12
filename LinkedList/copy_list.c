#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert a new node at the front of the list
void insertAtFront(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

// Print the entire linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to create and return a deep copy of a linked list
struct Node* copyLinkedList(struct Node* originalList) {
    if (originalList == NULL) return NULL;

    struct Node* newListHead = NULL;
    struct Node* newListTail = NULL;
    struct Node* currentOriginalNode = originalList;

    while (currentOriginalNode != NULL) {
        // Create a new node
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = currentOriginalNode->data;
        newNode->next = NULL;

        if (newListHead == NULL) {
            // First node in the new list
            newListHead = newNode;
            newListTail = newNode;
        } else {
            newListTail->next = newNode;
            newListTail = newNode;
        }

        currentOriginalNode = currentOriginalNode->next;
    }

    return newListHead;
}

// Main function to test
int main() {
    struct Node* originalList = NULL;

    // Creating original list: 1 → 2 → 3
    insertAtFront(&originalList, 3);
    insertAtFront(&originalList, 2);
    insertAtFront(&originalList, 1);

    printf("Original list:\n");
    printList(originalList);

    struct Node* copiedList = copyLinkedList(originalList);

    printf("Copied list:\n");
    printList(copiedList);

    return 0;
}
