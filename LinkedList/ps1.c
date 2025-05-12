#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a new node at the beginning of the list
void insertAtHead(struct Node** headRef, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = *headRef;
    *headRef = newNode;
}

// Function to print the elements of a linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to split the linked list into front and back halves
void splitLinkedList(struct Node* originalHead, struct Node** frontHalfHead, struct Node** backHalfHead) {
    struct Node* slow;
    struct Node* fast;

    // Edge case: 0 or 1 nodes — no split needed
    if (originalHead == NULL || originalHead->next == NULL) {
        *frontHalfHead = originalHead;
        *backHalfHead = NULL;
        return;
    }

    // Initialize slow and fast pointers
    slow = originalHead;
    fast = originalHead->next;

    // Move fast two steps and slow one step until fast reaches the end
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Split the list
    *frontHalfHead = originalHead;
    *backHalfHead = slow->next;
    slow->next = NULL;  // Break the list
}

// Main function to demonstrate the split
int main() {
    struct Node* fullList = NULL;
    struct Node* frontHalf = NULL;
    struct Node* backHalf = NULL;

    // Build the list: 2 -> 3 -> 5 -> 7 -> 11
    insertAtHead(&fullList, 11);
    insertAtHead(&fullList, 7);
    insertAtHead(&fullList, 5);
    insertAtHead(&fullList, 3);
    insertAtHead(&fullList, 2);

    printf("Original list:\n");
    printList(fullList);

    // Split the list into front and back halves
    splitLinkedList(fullList, &frontHalf, &backHalf);

    printf("Front half:\n");
    printList(frontHalf);

    printf("Back half:\n");
    printList(backHalf);

    return 0;
}
