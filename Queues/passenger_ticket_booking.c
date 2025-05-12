/*Write a menu­driven program that maintains a queue of passengers
waiting to see a ticket agent. The program user should be able to insert a
new passenger at the rear of the queue, display the passenger at the front
of the queue, or remove the passenger at the front of the queue. The
program will display the number of passengers left in the queue just
before it terminates.*/

#include <stdio.h>
#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

void insertPassenger(int passengerID) {
    if (rear == MAX - 1) {
        printf("Queue is full. Cannot add more passengers.\n");
        return;
    }
    if (front == -1) front = 0;
    rear++;
    queue[rear] = passengerID;
    printf("Passenger %d added to the queue.\n", passengerID);
}

void displayFrontPassenger() {
    if (front == -1 || front > rear) {
        printf("Queue is empty. No passenger at the front.\n");
        return;
    }
    printf("Passenger at front: %d\n", queue[front]);
}

void removePassenger() {
    if (front == -1 || front > rear) {
        printf("Queue is empty. No passenger to remove.\n");
        return;
    }
    printf("Passenger %d removed from the queue.\n", queue[front]);
    front++;
}

void displayRemainingPassengers() {
    if (front == -1 || front > rear) {
        printf("No passengers left in the queue.\n");
    } else {
        printf("Number of passengers left in the queue: %d\n", rear - front + 1);
    }
}

int main() {
    int choice, passengerID;
    do {
        printf("\n--- Passenger Queue Management ---\n");
        printf("1. Insert new passenger\n");
        printf("2. Display passenger at front\n");
        printf("3. Remove passenger at front\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter Passenger ID to insert: ");
                scanf("%d", &passengerID);
                insertPassenger(passengerID);
                break;
            case 2:
                displayFrontPassenger();
                break;
            case 3:
                removePassenger();
                break;
            case 4:
                displayRemainingPassengers();
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while(choice != 4);

    return 0;
}
