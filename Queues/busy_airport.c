#include <stdio.h>
#include <stdlib.h>
#include <time.h>
    
// Constants
#define SIMULATION_TIME 120  // Total simulation time in minutes
#define OPERATION_TIME 15    // Each operation (landing/takeoff) takes 15 mins

// Queue node for planes
struct PlaneNode {
    int id;           // Plane ID
    int requestTime;  // Time when the plane requested landing/takeoff
    struct PlaneNode* next;
};

// Queue structure using linked list
struct Queue {
    struct PlaneNode* front;
    struct PlaneNode* rear;
    int size;
};

// Runway structure
struct Runway {
    int busy;             // 0 if free, 1 if occupied
    int remainingTime;    // Remaining busy time
};

// Function to initialize a queue
void initQueue(struct Queue* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// Function to enqueue a plane
void enqueue(struct Queue* q, int id, int time) {
    struct PlaneNode* newNode = (struct PlaneNode*)malloc(sizeof(struct PlaneNode));
    newNode->id = id;
    newNode->requestTime = time;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// Function to dequeue a plane
struct PlaneNode* dequeue(struct Queue* q) {
    if (q->front == NULL) return NULL;
    struct PlaneNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    q->size--;
    return temp;
}

// Function to get the front plane (without removing)
struct PlaneNode* peek(struct Queue* q) {
    return q->front;
}

// Main simulation function
int main() {
    struct Queue landingQueue, takeoffQueue;
    struct Runway runway1 = {0, 0}, runway2 = {0, 0};
    int currentTime, planeID = 1;  // Rename 'time' to 'currentTime'
    int landingsCompleted = 0, takeoffsCompleted = 0;
    int totalLandingWait = 0, totalTakeoffWait = 0;

    srand(time(NULL));  // Seed the random number generator
    initQueue(&landingQueue);
    initQueue(&takeoffQueue);

    for (currentTime = 0; currentTime <= SIMULATION_TIME; currentTime++) {  // Use 'currentTime' here
        // Every 5 minutes, generate a request
        if (currentTime % 5 == 0) {
            if (rand() % 2 == 0) {
                enqueue(&landingQueue, planeID, currentTime);
                printf("Time %d: Plane %d requests LANDING.\n", currentTime, planeID);
            } else {
                enqueue(&takeoffQueue, planeID, currentTime);
                printf("Time %d: Plane %d requests TAKEOFF.\n", currentTime, planeID);
            }
            planeID++;
        }

        // Process Runway 1
        if (runway1.busy) {
            runway1.remainingTime--;
            if (runway1.remainingTime == 0) {
                runway1.busy = 0;
            }
        } else {
            if (landingQueue.front != NULL) {
                struct PlaneNode* plane = dequeue(&landingQueue);
                printf("Time %d: Plane %d starts LANDING on Runway 1.\n", currentTime, plane->id);
                totalLandingWait += (currentTime - plane->requestTime);
                landingsCompleted++;
                free(plane);
                runway1.busy = 1;
                runway1.remainingTime = OPERATION_TIME;
            } else if (takeoffQueue.front != NULL) {
                struct PlaneNode* plane = dequeue(&takeoffQueue);
                printf("Time %d: Plane %d starts TAKEOFF on Runway 1.\n", currentTime, plane->id);
                totalTakeoffWait += (currentTime - plane->requestTime);
                takeoffsCompleted++;
                free(plane);
                runway1.busy = 1;
                runway1.remainingTime = OPERATION_TIME;
            }
        }

        // Process Runway 2 (same logic as runway 1)
        if (runway2.busy) {
            runway2.remainingTime--;
            if (runway2.remainingTime == 0) {
                runway2.busy = 0;
            }
        } else {
            if (landingQueue.front != NULL) {
                struct PlaneNode* plane = dequeue(&landingQueue);
                printf("Time %d: Plane %d starts LANDING on Runway 2.\n", currentTime, plane->id);
                totalLandingWait += (currentTime - plane->requestTime);
                landingsCompleted++;
                free(plane);
                runway2.busy = 1;
                runway2.remainingTime = OPERATION_TIME;
            } else if (takeoffQueue.front != NULL) {
                struct PlaneNode* plane = dequeue(&takeoffQueue);
                printf("Time %d: Plane %d starts TAKEOFF on Runway 2.\n", currentTime, plane->id);
                totalTakeoffWait += (currentTime - plane->requestTime);
                takeoffsCompleted++;
                free(plane);
                runway2.busy = 1;
                runway2.remainingTime = OPERATION_TIME;
            }
        }
    }

    // After simulation, show the results
    printf("\n=== Simulation Finished ===\n");
    printf("Total Landings Completed: %d\n", landingsCompleted);
    printf("Total Takeoffs Completed: %d\n", takeoffsCompleted);

    printf("Planes still waiting to LAND: %d\n", landingQueue.size);
    printf("Planes still waiting to TAKEOFF: %d\n", takeoffQueue.size);

    if (landingsCompleted > 0)
        printf("Average Landing Wait Time: %.2f minutes\n", (float)totalLandingWait / landingsCompleted);
    else
        printf("No landings were completed.\n");

    if (takeoffsCompleted > 0)
        printf("Average Takeoff Wait Time: %.2f minutes\n", (float)totalTakeoffWait / takeoffsCompleted);
    else
        printf("No takeoffs were completed.\n");

    // Free remaining planes in queues
    while (landingQueue.front != NULL) free(dequeue(&landingQueue));
    while (takeoffQueue.front != NULL) free(dequeue(&takeoffQueue));

    return 0;
}
