#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent each stack
typedef struct {
    int *array;
    int top;
    int capacity;
} Stack;

// Function to create a stack of given capacity
Stack* createStack(int capacity) {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is full
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Function to push an element to the stack
void push(Stack *stack, int item) {
    if (isFull(stack)) {
        printf("Stack is full, utilizing next stack...\n");
    } else {
        stack->array[++(stack->top)] = item;
    }
}

// Function to simulate the stacks and handle overflow
void simulateStacks(int arr[], int n, int m) {
    // Create m stacks
    Stack *stacks[m];
    int baseSize = n / m;
    int extra = n % m;  // Distribute extra elements

    // Initialize each stack
    for (int i = 0; i < m; i++) {
        stacks[i] = createStack(baseSize + (i < extra ? 1 : 0)); // Allocate extra space for first 'extra' stacks
    }

    int currentStack = 0;

    // Insert elements into stacks
    for (int i = 0; i < n; i++) {
        // Push element into the current stack
        push(stacks[currentStack], arr[i]);

        // If the current stack is full, move to the next stack
        if (isFull(stacks[currentStack]) && currentStack < m - 1) {
            currentStack++;
        }
    }

    // Display all stacks
    for (int i = 0; i < m; i++) {
        printf("\nStack %d (top to bottom): ", i + 1);
        for (int j = 0; j <= stacks[i]->top; j++) {
            printf("%d ", stacks[i]->array[j]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    int n, m;

    // Input size of array and number of stacks
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    printf("Enter the number of stacks (m): ");
    scanf("%d", &m);

    if (m <= 2 || m >= n) {
        printf("Invalid number of stacks. Ensure 2 < m < n.\n");
        return 0;
    }

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Simulate the stacks and handle overflow
    simulateStacks(arr, n, m);

    return 0;
}
