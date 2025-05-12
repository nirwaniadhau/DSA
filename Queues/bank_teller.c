#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep function

// Structure to represent a customer
typedef struct {
    int customerId;
    int arrivalTime;
    int serviceTime;  // Time taken to serve the customer
} Customer;

// Define a simple Queue structure
#define MAX_QUEUE_SIZE 100

typedef struct {
    Customer queue[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

// Function to initialize the queue
void initializeQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Function to check if the queue is full
int isFull(Queue* q) {
    return q->rear == MAX_QUEUE_SIZE - 1;
}

// Function to enqueue a customer into the queue
void enqueue(Queue* q, Customer c) {
    if (isFull(q)) {
        printf("Queue is full! Cannot add more customers.\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;  // First element being added
    }
    q->queue[++(q->rear)] = c;
}

// Function to dequeue a customer from the queue
Customer dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! No customers to serve.\n");
        Customer empty = { -1, -1, -1 };  // Return an empty customer
        return empty;
    }
    Customer c = q->queue[q->front];
    if (q->front == q->rear) {  // Last customer in the queue
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return c;
}

// Function to simulate processing customers with one teller
void simulateOneTeller(Queue* q) {
    int totalWaitingTime = 0;
    int currentTime = 0;  // Start from time 0

    printf("\nSimulation with ONE Teller:\n");
    printf("Customer ID  Arrival Time  Service Time  Waiting Time\n");

    while (!isEmpty(q)) {
        Customer c = dequeue(q);
        
        // Customer arrives after current time, so calculate waiting time
        if (c.arrivalTime > currentTime) {
            currentTime = c.arrivalTime;
        }
        int waitingTime = currentTime - c.arrivalTime;
        totalWaitingTime += waitingTime;

        // Print the details of each customer
        printf("%10d  %12d  %12d  %12d\n", c.customerId, c.arrivalTime, c.serviceTime, waitingTime);
        
        // Add service time to current time
        currentTime += c.serviceTime;
        sleep(1);  // To simulate time passing for each customer
    }
    printf("Average waiting time with one teller: %.2f\n", (float)totalWaitingTime / (q->rear + 1));
}

// Function to simulate processing customers with two tellers
void simulateTwoTellers(Queue* q) {
    int totalWaitingTime = 0;
    int teller1Time = 0, teller2Time = 0;
    int currentTime = 0;  // Start from time 0

    printf("\nSimulation with TWO Tellers:\n");
    printf("Customer ID  Arrival Time  Service Time  Waiting Time\n");

    while (!isEmpty(q)) {
        Customer c = dequeue(q);
        
        // Check which teller is free
        int tellerTime = (teller1Time <= teller2Time) ? teller1Time : teller2Time;
        if (c.arrivalTime > tellerTime) {
            currentTime = c.arrivalTime;
        } else {
            currentTime = tellerTime;
        }
        
        // Calculate waiting time
        int waitingTime = currentTime - c.arrivalTime;
        totalWaitingTime += waitingTime;
        
        // Print the details of each customer
        printf("%10d  %12d  %12d  %12d\n", c.customerId, c.arrivalTime, c.serviceTime, waitingTime);

        // Assign service time to the respective teller
        if (teller1Time <= teller2Time) {
            teller1Time = currentTime + c.serviceTime;
        } else {
            teller2Time = currentTime + c.serviceTime;
        }

        sleep(1);  // Simulate time passing for each customer
    }
    printf("Average waiting time with two tellers: %.2f\n", (float)totalWaitingTime / (q->rear + 1));
}

int main() {
    int numCustomers;
    
    printf("Enter the number of customers: ");
    scanf("%d", &numCustomers);
    
    Queue q;
    initializeQueue(&q);
    
    // Create customers with arrival times and service times
    for (int i = 0; i < numCustomers; i++) {
        Customer c;
        c.customerId = i + 1;
        printf("\nEnter arrival time for Customer %d: ", i + 1);
        scanf("%d", &c.arrivalTime);
        printf("Enter service time for Customer %d: ", i + 1);
        scanf("%d", &c.serviceTime);
        
        enqueue(&q, c);  // Add customer to the queue
    }

    // Simulate with one teller
    simulateOneTeller(&q);

    // Reset queue for next simulation
    initializeQueue(&q);

    // Create customers again (assuming a fresh set of customers for two tellers)
    for (int i = 0; i < numCustomers; i++) {
        Customer c;
        c.customerId = i + 1;
        printf("\nEnter arrival time for Customer %d: ", i + 1);
        scanf("%d", &c.arrivalTime);
        printf("Enter service time for Customer %d: ", i + 1);
        scanf("%d", &c.serviceTime);
        
        enqueue(&q, c);  // Add customer to the queue
    }

    // Simulate with two tellers
    simulateTwoTellers(&q);

    return 0;
}
