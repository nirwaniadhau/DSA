#include <stdio.h>

#define MAX 100

// Stack for general use
int stack[MAX];
int top = -1;

// Push operation
void push(int val) {
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = val;
}

// Pop operation
int pop() {
    if (top == -1)
        return -1; // Underflow
    else
        return stack[top--];
}

// A. Factorial using Stack
int factorial(int n) {
    int result = 1;
    top = -1;  // reset stack

    for (int i = n; i >= 1; i--) {
        push(i);
    }

    while (top != -1) {
        result *= pop();
    }

    return result;
}

// B. Fibonacci using Stack (pushing and popping previous values)
void fibonacci(int terms) {
    int a, b, next;

    // Reset stack
    top = -1;

    // Initialize first two values
    push(0); // a
    push(1); // b

    printf("Fibonacci Series: ");

    if (terms >= 1) printf("%d ", stack[0]); // a
    if (terms >= 2) printf("%d ", stack[1]); // b

    for (int i = 3; i <= terms; i++) {
        // Pop last two values
        b = pop();  // top
        a = pop();  // next top

        next = a + b;
        printf("%d ", next);

        // Push back the updated values for next iteration
        push(b);      // old b becomes new a
        push(next);   // new b
    }

    printf("\n");
}

int main() {
    int choice, num;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Factorial using Stack\n");
        printf("2. Fibonacci using Stack\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number to find factorial: ");
                scanf("%d", &num);
                printf("Factorial of %d = %d\n", num, factorial(num));
                break;

            case 2:
                printf("Enter number of terms for Fibonacci series: ");
                scanf("%d", &num);
                fibonacci(num);
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
