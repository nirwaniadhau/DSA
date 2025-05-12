#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

int isFull() {
    return top == MAX - 1;
}

int isEmpty() {
    return top == -1;
}

void push(char c) {
    if (isFull()) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (isEmpty()) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void infixToPostfix(char* infix) {
    int i, j = 0;
    char postfix[MAX];

    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty() && stack[top] != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty() && stack[top] == '(') {
                pop();
            }
        } else if (isOperator(infix[i])) {
            while (!isEmpty() && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }

    while (!isEmpty()) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
    printf("Postfix Expression: %s\n", postfix);
}

int main() {
    char infix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
