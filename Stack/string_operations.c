/*WAP to accept a string from user and perform following operations on it
using stacks. A. Palindrome B. String Reverse C. String Concat D.String
compare*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

char stack[MAX];
int top = -1;

// Stack operations
void push(char ch) {
    if (top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++top] = ch;
}

char pop() {
    if (top == -1) return '\0';
    return stack[top--];
}

// A. Check if string is palindrome using stack
void checkPalindrome(char str[]) {
    top = -1;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        push(str[i]);
    }

    for (int i = 0; i < len; i++) {
        if (str[i] != pop()) {
            printf("Not a Palindrome.\n");
            return;
        }
    }
    printf("Palindrome String.\n");
}

// B. Reverse string using stack
void reverseString(char str[]) {
    top = -1;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        push(str[i]);
    }

    printf("Reversed String: ");
    while (top != -1) {
        printf("%c", pop());
    }
    printf("\n");
}

// C. Concatenate two strings using stack
void concatStrings(char str1[], char str2[]) {
    top = -1;

    for (int i = 0; str1[i] != '\0'; i++) {
        push(str1[i]);
    }

    for (int i = 0; str2[i] != '\0'; i++) {
        push(str2[i]);
    }

    char temp[MAX * 2];
    int idx = -1;

    while (top != -1) {
        temp[++idx] = pop();
    }

    printf("Concatenated String: ");
    while (idx >= 0) {
        printf("%c", temp[idx--]);
    }
    printf("\n");
}

// D. Compare strings using stack (not strcmp)
void compareStrings(char str1[], char str2[]) {
    char s1[MAX], s2[MAX];
    int t1 = -1, t2 = -1;
    int i;

    for (i = 0; str1[i] != '\0'; i++)
        s1[++t1] = str1[i];
    for (i = 0; str2[i] != '\0'; i++)
        s2[++t2] = str2[i];

    if (t1 != t2) {
        printf("Strings are NOT Equal.\n");
        return;
    }

    while (t1 != -1) {
        if (s1[t1--] != s2[t2--]) {
            printf("Strings are NOT Equal.\n");
            return;
        }
    }
    printf("Strings are Equal.\n");
}

int main() {
    char str1[MAX], str2[MAX];
    int choice;

    while (1) {
        printf("\n--- STRING OPERATIONS USING STACK ---\n");
        printf("1. Check Palindrome\n");
        printf("2. Reverse String\n");
        printf("3. Concatenate Two Strings\n");
        printf("4. Compare Two Strings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter string: ");
                scanf("%s", str1);
                checkPalindrome(str1);
                break;

            case 2:
                printf("Enter string: ");
                scanf("%s", str1);
                reverseString(str1);
                break;

            case 3:
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                concatStrings(str1, str2);
                break;

            case 4:
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                compareStrings(str1, str2);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
