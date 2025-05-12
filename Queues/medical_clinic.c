/* Write a Program to keep track of patients as they check into a medical
clinic, assigning patients to doctors on a first­come, first­served basis.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50   // Maximum number of patients
#define NAME_SIZE 100

typedef struct {
    char name[NAME_SIZE];
} Patient;

typedef struct {
    Patient patients[MAX];
    int front;
    int rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return (q->front == -1);
}

// Check if queue is full
int isFull(Queue* q) {
    return ((q->rear + 1) % MAX == q->front);
}

// Add a patient to the queue
void checkInPatient(Queue* q, char* name) {
    if (isFull(q)) {
        printf("Clinic is full! Cannot add more patients.\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }

    strcpy(q->patients[q->rear].name, name);
    printf("Patient %s checked in successfully.\n", name);
}

// Assign a patient to a doctor (serve the patient)
void assignToDoctor(Queue* q) {
    if (isEmpty(q)) {
        printf("No patients to assign.\n");
        return;
    }

    printf("Assigning patient %s to a doctor...\n", q->patients[q->front].name);

    // Only one patient in the queue
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

// Display the waiting patients
void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("No patients in the clinic.\n");
        return;
    }

    printf("Patients waiting:\n");
    int i = q->front;
    while (1) {
        printf("- %s\n", q->patients[i].name);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
}

int main() {
    Queue clinicQueue;
    int choice;
    char name[NAME_SIZE];

    initQueue(&clinicQueue);

    do {
        printf("\n--- Medical Clinic Patient Management ---\n");
        printf("1. Check-in Patient\n");
        printf("2. Assign Patient to Doctor\n");
        printf("3. Display Waiting Patients\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the input buffer

        switch (choice) {
            case 1:
                printf("Enter patient's name: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                checkInPatient(&clinicQueue, name);
                break;
            case 2:
                assignToDoctor(&clinicQueue);
                break;
            case 3:
                displayQueue(&clinicQueue);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
