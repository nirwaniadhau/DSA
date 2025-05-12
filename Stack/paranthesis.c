
//WAP to accept a string of parenthesis and check its validity by using stack.
#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Push function
void push(char ch) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = ch;
    }
}

// Pop function
void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
    } else {
        top--;
    }
}

// Function to check if parentheses are balanced
int isValidParentheses(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        // Push opening brackets
        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch);
        }
        // Check for closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1) {
                return 0; // No opening bracket to match
            }

            // Match and pop only if correct pair
            if ((ch == ')' && stack[top] == '(') ||
                (ch == '}' && stack[top] == '{') ||
                (ch == ']' && stack[top] == '[')) {
                pop(); // Valid match, so pop
            } else {
                return 0; // Mismatch
            }
        }
    }

    // After traversal, stack should be empty
    return (top == -1);
}

int main() {
    char expr[MAX];

    printf("Enter a string of parentheses: ");
    scanf("%s", expr);

    if (isValidParentheses(expr)) {
        printf("The parentheses are valid.\n");
    } else {
        printf("The parentheses are NOT valid.\n");
    }

    return 0;
}
