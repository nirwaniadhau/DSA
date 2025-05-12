#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert at head
void insertAtHead(struct Node** head, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

// Print the list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Append listB to the end of listA
void Append(struct Node** listA, struct Node** listB) {
    if (*listA == NULL) {
        *listA = *listB;
    } else {
        struct Node* temp = *listA;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = *listB;
    }
    *listB = NULL;
}

// Main
int main() {
    struct Node* a = NULL;
    struct Node* b = NULL;

    // Create list a: 1 → 2
    insertAtHead(&a, 2);
    insertAtHead(&a, 1);

    // Create list b: 3 → 4
    insertAtHead(&b, 4);
    insertAtHead(&b, 3);

    printf("List A before append:\n");
    printList(a);

    printf("List B before append:\n");
    printList(b);

    Append(&a, &b);

    printf("List A after append:\n");
    printList(a);

    printf("List B after append (should be empty):\n");
    printList(b);

    return 0;
}
