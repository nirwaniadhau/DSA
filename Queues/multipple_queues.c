#include <stdio.h>
#include <stdlib.h>

void distributeArray(int arr[], int n, int m) {
    // Create a 2D array to represent the m queues
    int** queues = (int**)malloc(m * sizeof(int*));
    int* queue_sizes = (int*)malloc(m * sizeof(int));  // Store the size of each queue
    int remaining = n;

    // Step 1: Calculate approximate size for each queue
    for (int i = 0; i < m; i++) {
        queue_sizes[i] = remaining / (m - i);  // Divide remaining elements evenly
        remaining -= queue_sizes[i];
        queues[i] = (int*)malloc(queue_sizes[i] * sizeof(int));  // Allocate space for each queue
    }

    // Step 2: Fill the queues with the array elements
    int index = 0;  // Index for the original array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < queue_sizes[i]; j++) {
            queues[i][j] = arr[index++];
        }
    }

    // Step 3: Print the divided queues
    for (int i = 0; i < m; i++) {
        printf("Queue %d: ", i + 1);
        for (int j = 0; j < queue_sizes[i]; j++) {
            printf("%d ", queues[i][j]);
        }
        printf("\n");
    }

    // Free the memory used for queues
    for (int i = 0; i < m; i++) {
        free(queues[i]);
    }
    free(queues);
    free(queue_sizes);
}

int main() {
    int n, m;

    // Take user input for size of array and number of queues
    printf("Enter the size of the array (n): ");
    scanf("%d", &n);

    if (n < 3) {
        printf("Array size should be at least 3.\n");
        return -1;
    }

    printf("Enter the number of subarrays (m): ");
    scanf("%d", &m);

    if (m <= 2 || m >= n) {
        printf("Invalid value for m. It must satisfy 2 < m < n.\n");
        return -1;
    }

    // Declare the array
    int arr[n];

    // Take user input for the array elements
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Call the function to divide and distribute the array
    distributeArray(arr, n, m);

    return 0;
}
