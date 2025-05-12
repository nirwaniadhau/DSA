#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define NAME_SIZE 50

typedef struct {
    char name[NAME_SIZE];
} Task;

typedef struct {
    Task tasks[MAX];
    int front;
    int rear;
} Queue;

// Initialize the queue
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Check if queue is full
int isFull(Queue *q) {
    return ((q->rear + 1) % MAX == q->front);
}

// Enqueue a task
void enqueue(Queue *q, Task task) {
    if (isFull(q)) {
        printf("Queue is full! Cannot add task.\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }

    q->tasks[q->rear] = task;
}

// Dequeue a task
Task dequeue(Queue *q) {
    Task task = {"NoTask"};

    if (isEmpty(q)) {
        printf("Queue is empty! Nothing to dequeue.\n");
        return task;
    }

    task = q->tasks[q->front];

    if (q->front == q->rear) {
        // Last element
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }

    return task;
}

// Process all tasks in a queue
void processQueue(Queue *q, char taskType[]) {
    while (!isEmpty(q)) {
        Task currentTask = dequeue(q);
        printf("Processing %s task: %s\n", taskType, currentTask.name);
    }
}

int main() {
    Queue downloadQueue, musicQueue, gameQueue;
    int choice;
    char taskName[NAME_SIZE];

    initQueue(&downloadQueue);
    initQueue(&musicQueue);
    initQueue(&gameQueue);

    do {
        printf("\n--- Multitasking System Simulation ---\n");
        printf("1. Add Download Task\n");
        printf("2. Add Music Task\n");
        printf("3. Add Game Task\n");
        printf("4. Start Processing Tasks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer after reading choice

        switch (choice) {
            case 1:
                printf("Enter Download Task Name: ");
                // Use scanf to read the task name
                scanf("%49s", taskName);  // Limit input to avoid buffer overflow

                // Create Task object and copy taskName into it
                Task newTask;
                strcpy(newTask.name, taskName);
                enqueue(&downloadQueue, newTask);  // Enqueue the task
                break;
            case 2:
                printf("Enter Music Task Name: ");
                // Use scanf to read the task name
                scanf("%49s", taskName);

                // Create Task object and copy taskName into it
                Task musicTask;
                strcpy(musicTask.name, taskName);
                enqueue(&musicQueue, musicTask);  // Enqueue the task
                break;
            case 3:
                printf("Enter Game Task Name: ");
                // Use scanf to read the task name
                scanf("%49s", taskName);

                // Create Task object and copy taskName into it
                Task gameTask;
                strcpy(gameTask.name, taskName);
                enqueue(&gameQueue, gameTask);  // Enqueue the task
                break;
            case 4:
                printf("\nStarting task processing...\n");

                // Highest priority: Download
                printf("\nProcessing Download Tasks:\n");
                processQueue(&downloadQueue, "Download");

                // Then music
                printf("\nProcessing Music Tasks:\n");
                processQueue(&musicQueue, "Music");

                // Then game
                printf("\nProcessing Game Tasks:\n");
                processQueue(&gameQueue, "Game");

                printf("\nAll tasks completed!\n");
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
