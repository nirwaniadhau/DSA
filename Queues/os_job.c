#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_JOBS 100
#define PRINTER_SPEED 10  // 10 pages per minute

// Structure to represent a print job
typedef struct {
    int job_id;
    int pages;  // Number of pages in the job
} PrintJob;

// Min-Heap to implement priority queue
typedef struct {
    PrintJob heap[MAX_JOBS];
    int size;
} MinHeap;

// Function to initialize the priority queue (min-heap)
void initMinHeap(MinHeap* h) {
    h->size = 0;
}

// Function to swap two elements in the heap
void swap(PrintJob* a, PrintJob* b) {
    PrintJob temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue
void heapify(MinHeap* h, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->size && h->heap[left].pages < h->heap[smallest].pages) {
        smallest = left;
    }
    if (right < h->size && h->heap[right].pages < h->heap[smallest].pages) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&h->heap[index], &h->heap[smallest]);
        heapify(h, smallest);
    }
}

// Function to insert a job into the priority queue
void insertJob(MinHeap* h, PrintJob job) {
    h->heap[h->size] = job;
    int index = h->size++;
    while (index > 0 && h->heap[(index - 1) / 2].pages > h->heap[index].pages) {
        swap(&h->heap[(index - 1) / 2], &h->heap[index]);
        index = (index - 1) / 2;
    }
}

// Function to extract the job with the least number of pages
PrintJob extractMin(MinHeap* h) {
    if (h->size == 0) {
        PrintJob emptyJob = {-1, 0};
        return emptyJob;
    }
    PrintJob root = h->heap[0];
    h->heap[0] = h->heap[--(h->size)];
    heapify(h, 0);
    return root;
}

// Function to simulate printing with multiple printers
void simulatePrinting(int numPrinters, MinHeap* printQueue) {
    int timeElapsed = 0;
    int printerStatus[numPrinters];  // Array to track each printer's availability
    int printerJobs[numPrinters];    // Array to track the job assigned to each printer

    // Initialize printer statuses and jobs
    for (int i = 0; i < numPrinters; i++) {
        printerStatus[i] = 0;  // Printer is available
        printerJobs[i] = -1;   // No job assigned
    }

    printf("\nPrinting with %d printers:\n", numPrinters);
    while (printQueue->size > 0) {
        bool jobAssigned = false;
        for (int i = 0; i < numPrinters; i++) {
            if (printerStatus[i] == 0 && printQueue->size > 0) {
                // Assign the next job to the printer
                PrintJob job = extractMin(printQueue);
                printerStatus[i] = job.pages / PRINTER_SPEED;  // Calculate printing time for this job
                printerJobs[i] = job.job_id;
                printf("Time %d: Printer %d started Job %d with %d pages\n", timeElapsed, i + 1, job.job_id, job.pages);
                jobAssigned = true;
                break;
            }
        }

        // Decrease the status of all printers (decrementing the remaining time)
        for (int i = 0; i < numPrinters; i++) {
            if (printerStatus[i] > 0) {
                printerStatus[i]--;
                if (printerStatus[i] == 0) {
                    printf("Time %d: Printer %d finished Job %d\n", timeElapsed, i + 1, printerJobs[i]);
                    printerJobs[i] = -1;
                }
            }
        }

        timeElapsed++;
    }

    printf("\nAll jobs are completed in %d minutes.\n", timeElapsed);
}

// Main function to simulate the print job scheduling
int main() {
    MinHeap printQueue;
    initMinHeap(&printQueue);

    // Generate 100 random print jobs (pages between 1 and 50)
    for (int i = 0; i < 100; i++) {
        PrintJob job = {i + 1, rand() % 50 + 1};
        insertJob(&printQueue, job);
    }

    int numPrinters;
    printf("Enter the number of printers (1, 2, or 3): ");
    scanf("%d", &numPrinters);

    // Simulate the printing process with the given number of printers
    if (numPrinters < 1 || numPrinters > 3) {
        printf("Invalid number of printers! Please choose between 1, 2, or 3 printers.\n");
        return -1;
    }

    // Call the function to simulate printing
    simulatePrinting(numPrinters, &printQueue);

    return 0;
}
