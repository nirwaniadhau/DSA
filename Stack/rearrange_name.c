#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct {
    char *data[MAX];
    int top;
} Stack;

// Function to initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Function to check if the stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Function to check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Function to push an element to the stack
void push(Stack *s, char *str) {
    if (!isFull(s)) {
        s->data[++(s->top)] = str;
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop an element from the stack
char* pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return NULL;
}

// Function to split a string by spaces and push each part into the stack
void splitAndPush(Stack *s, char *name) {
    char *word = strtok(name, " ");
    while (word != NULL) {
        push(s, word);
        word = strtok(NULL, " ");
    }
}

// Main function
int main() {
    char fullName[MAX];
    Stack s;
    initStack(&s);

    // Input the full name
    printf("Enter your full name (First name Middle name Surname): ");
    fgets(fullName, sizeof(fullName), stdin);

    // Remove the newline character if it exists
    fullName[strcspn(fullName, "\n")] = '\0';

    // Split the full name and push each word to the stack
    splitAndPush(&s, fullName);

    // Pop the words from the stack and print them in "Surname, First name, Middle name" order
    printf("Rearranged name: ");
    while (!isEmpty(&s)) {
        printf("%s ", pop(&s));
    }

    printf("\n");

    return 0;
}
