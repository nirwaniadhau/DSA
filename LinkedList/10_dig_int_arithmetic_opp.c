#include <stdio.h>
#include <stdlib.h>

struct Node {
    int digit;
    struct Node* next;
};

// Insert digit at the end (to preserve digit order)
void insertDigit(struct Node** head, int digit) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->digit = digit;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Reverse a linked list (useful for arithmetic)
struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* curr = head;
    struct Node* next = NULL;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

// Add two large integers represented as linked lists
struct Node* addLists(struct Node* first, struct Node* second) {
    first = reverseList(first);
    second = reverseList(second);

    struct Node* result = NULL;
    int carry = 0;

    while (first || second || carry) {
        int sum = carry;
        if (first) {
            sum += first->digit;
            first = first->next;
        }
        if (second) {
            sum += second->digit;
            second = second->next;
        }

        carry = sum / 10;
        insertDigit(&result, sum % 10);
    }

    return reverseList(result);
}

// Display the number
void printNumber(struct Node* head) {
    while (head) {
        printf("%d", head->digit);
        head = head->next;
    }
    printf("\n");
}

// Convert integer string to linked list
void createNumberFromString(struct Node** head, char* numberStr) {
    for (int i = 0; numberStr[i] != '\0'; i++) {
        insertDigit(head, numberStr[i] - '0');
    }
}

// Main function to test
int main() {
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;

    // Store two 10-digit numbers as strings
    char number1[] = "9876543210";
    char number2[] = "1234567890";

    createNumberFromString(&num1, number1);
    createNumberFromString(&num2, number2);

    printf("Number 1: ");
    printNumber(num1);
    printf("Number 2: ");
    printNumber(num2);

    struct Node* result = addLists(num1, num2);

    printf("Sum:      ");
    printNumber(result);

    return 0;
}
