#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack for room traversal
int roomStack[MAX];
int topRoom = -1;

// Stack for binary conversion
int binStack[MAX];
int topBin = -1;

// Push and pop for room traversal
void pushRoom(int room) {
    if (topRoom == MAX - 1)
        printf("Room stack overflow\n");
    else
        roomStack[++topRoom] = room;
}

int popRoom() {
    if (topRoom == -1)
        return -1;
    else
        return roomStack[topRoom--];
}

// Push and pop for binary conversion
void pushBin(int bit) {
    if (topBin == MAX - 1)
        printf("Binary stack overflow\n");
    else
        binStack[++topBin] = bit;
}

int popBin() {
    if (topBin == -1)
        return -1;
    else
        return binStack[topBin--];
}

// Function to convert decimal to binary using stack
void convertToBinary(int num) {
    while (num > 0) {
        pushBin(num % 2);
        num /= 2;
    }

    printf("Binary code to unlock the treasure: ");
    while (topBin != -1) {
        printf("%d", popBin());
    }
    printf("\n");
}

int main() {
    int i;
    int treasureCode;

    printf("Person starts moving from Room 1 to Room 5...\n");
    for (i = 1; i <= 5; i++) {
        printf("Entered Room %d\n", i);
        pushRoom(i);
    }

    printf("\nFound a box in Room 5.\n");
    printf("Enter the decimal code written on the box: ");
    scanf("%d", &treasureCode);

    convertToBinary(treasureCode);

    printf("\nReturning back to Room 1...\n");
    while ((i = popRoom()) != -1) {
        printf("Returned to Room %d\n", i);
    }

    printf("Unlocked treasure in Room 1!\n");

    return 0;
}
