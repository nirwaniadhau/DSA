#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

// Create a new node
struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// Function to perform insertion sort
struct ListNode* insertionSortList(struct ListNode* head) {
    struct ListNode* dummy = createNode(-10000);  // Dummy node with a small value

    while (head != NULL) {
        struct ListNode* next = head->next;
        struct ListNode* temp = dummy;

        // Find the correct spot to insert the current node
        while (temp->next != NULL && temp->next->val < head->val) {
            temp = temp->next;
        }

        head->next = temp->next;
        temp->next = head;

        head = next;
    }

    struct ListNode* sortedHead = dummy->next;
    free(dummy);  // Free dummy if no longer needed
    return sortedHead;
}

// Print the list
void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

// Driver code
int main() {
    struct ListNode* head = NULL;
    int n, val;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Insert elements at the beginning
    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &val);
        struct ListNode* newNode = createNode(val);
        newNode->next = head;
        head = newNode;
    }

    printf("Unsorted List:\n");
    printList(head);

    head = insertionSortList(head);

    printf("Sorted List:\n");
    printList(head);

    return 0;
}
