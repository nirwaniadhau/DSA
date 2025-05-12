/*Assume that there are three jobs to be done (J1, J2, J3) by using queue.
Each is requiring different time for processing i.e. (t1, t2, t3), which is
greater than fixed time quantum 'n'. After 'n' time the current job is
forcefully preempted/ stopped and remaining task of the current job is
added at last of the queue. then next job is taken for processing.*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define NAME_SIZE 10

typedef struct {
    char name[NAME_SIZE];
    int remaining_time;
} Job;

typedef struct {
    Job jobs[MAX];
    int front;
    int rear;
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Check if queue is full
int isFull(Queue* q) {
    return ((q->rear + 1) % MAX == q->front);
}

// Enqueue a job
void enqueue(Queue* q, Job job) {
    if (isFull(q)) {
        printf("Queue is full! Cannot add job.\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }

    q->jobs[q->rear] = job;
}

// Dequeue a job
Job dequeue(Queue* q) {
    Job job = {"", 0};

    if (isEmpty(q)) {
        printf("Queue is empty! Nothing to dequeue.\n");
        return job;
    }

    job = q->jobs[q->front];

    if (q->front == q->rear) {
        // Last element
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }

    return job;
}

// Simulate Round Robin Scheduling
void simulateRoundRobin(Queue* q, int time_quantum) {
    while (!isEmpty(q)) {
        Job current_job = dequeue(q);

        printf("\nProcessing %s:\n", current_job.name);

        if (current_job.remaining_time > time_quantum) {
            printf("%s processed for %d units. Remaining: %d units\n",
                   current_job.name, time_quantum, current_job.remaining_time - time_quantum);
            current_job.remaining_time -= time_quantum;
            enqueue(q, current_job);
        } else {
            printf("%s completed in %d units.\n", current_job.name, current_job.remaining_time);
        }
    }
}

int main() {
    Queue jobQueue;
    int t1, t2, t3, time_quantum;

    initQueue(&jobQueue);

    printf("Enter time required for J1: ");
    scanf("%d", &t1);

    printf("Enter time required for J2: ");
    scanf("%d", &t2);

    printf("Enter time required for J3: ");
    scanf("%d", &t3);

    printf("Enter fixed time quantum: ");
    scanf("%d", &time_quantum);

    // Create jobs
    Job j1 = {"J1", t1};
    Job j2 = {"J2", t2};
    Job j3 = {"J3", t3};

    // Enqueue jobs
    enqueue(&jobQueue, j1);
    enqueue(&jobQueue, j2);
    enqueue(&jobQueue, j3);

    // Start simulation
    simulateRoundRobin(&jobQueue, time_quantum);

    printf("\nAll jobs completed!\n");

    return 0;
}
