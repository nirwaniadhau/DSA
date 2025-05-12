#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure to represent a passenger
typedef struct {
    char name[50];
    int arrival_time;  // Time of arrival
    int service_time;  // Time to be served
} Passenger;

// Queue structure
typedef struct {
    Passenger queue[MAX];
    int front, rear;
} Queue;

// Function to initialize the queue
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Function to check if the queue is full
int isFull(Queue* q) {
    return q->rear == MAX - 1;
}

// Function to enqueue a passenger
void enqueue(Queue* q, Passenger p) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->queue[++(q->rear)] = p;
}

// Function to dequeue a passenger
Passenger dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        Passenger empty = {"", 0, 0};
        return empty;
    }
    Passenger p = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;  // Queue becomes empty
    } else {
        q->front++;
    }
    return p;
}

// Function to simulate the ticket counter
void simulateTicketCounter(Queue* regularQueue, Queue* frequentQueue, int total_passengers, int strategy) {
    int total_waiting_time = 0;
    int served_count = 0;
    
    while (!isEmpty(regularQueue) || !isEmpty(frequentQueue)) {
        Passenger current;

        if (strategy == 1) {  // Serve frequent flyers first
            if (!isEmpty(frequentQueue)) {
                current = dequeue(frequentQueue);
            } else {
                current = dequeue(regularQueue);
            }
        } else if (strategy == 2) {  // Serve regular customers first
            if (!isEmpty(regularQueue)) {
                current = dequeue(regularQueue);
            } else {
                current = dequeue(frequentQueue);
            }
        } else {  // Alternate between the two
            if (served_count % 2 == 0 && !isEmpty(frequentQueue)) {
                current = dequeue(frequentQueue);
            } else {
                current = dequeue(regularQueue);
            }
        }

        // Calculate waiting time for the customer
        int wait_time = served_count * current.service_time - current.arrival_time;
        if (wait_time < 0) wait_time = 0;
        total_waiting_time += wait_time;
        
        printf("Serving %s (Arrival: %d, Service time: %d, Waiting time: %d)\n", 
               current.name, current.arrival_time, current.service_time, wait_time);

        served_count++;
    }
    
    // Calculate average waiting time
    double avg_waiting_time = (double) total_waiting_time / total_passengers;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
}

// Main function
int main() {
    Queue regularQueue, frequentQueue;
    initQueue(&regularQueue);
    initQueue(&frequentQueue);

    int total_passengers;
    printf("Enter the total number of passengers: ");
    scanf("%d", &total_passengers);

    // Input data for passengers
    for (int i = 0; i < total_passengers; i++) {
        Passenger p;
        int type;  // 0 for regular, 1 for frequent flyer

        printf("\nEnter name of passenger %d: ", i + 1);
        scanf("%s", p.name);
        printf("Enter arrival time: ");
        scanf("%d", &p.arrival_time);
        printf("Enter service time: ");
        scanf("%d", &p.service_time);
        printf("Enter passenger type (0 for regular, 1 for frequent flyer): ");
        scanf("%d", &type);

        if (type == 0) {
            enqueue(&regularQueue, p);
        } else {
            enqueue(&frequentQueue, p);
        }
    }

    int strategy;
    printf("\nChoose a strategy:\n");
    printf("1. Serve frequent flyers first\n");
    printf("2. Serve regular customers first\n");
    printf("3. Alternate between frequent flyers and regular customers\n");
    printf("Enter your choice: ");
    scanf("%d", &strategy);

    // Simulate the ticket counter based on the selected strategy
    simulateTicketCounter(&regularQueue, &frequentQueue, total_passengers, strategy);

    return 0;
}
