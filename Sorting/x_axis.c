#include <stdio.h>
#include <stdlib.h>

// Function to compare two integers (used for sorting)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to find the closest pair of points
void findClosestPair(int points[], int n) {
    // Sort the points
    qsort(points, n, sizeof(int), compare);

    // Initialize the minimum distance to a large value
    int minDist = abs(points[1] - points[0]);
    int p1 = points[0], p2 = points[1];

    // Compare consecutive points to find the minimum distance
    for (int i = 1; i < n - 1; i++) {
        int dist = abs(points[i + 1] - points[i]);
        if (dist < minDist) {
            minDist = dist;
            p1 = points[i];
            p2 = points[i + 1];
        }
    }

    // Output the closest pair and the minimum distance
    printf("The closest pair is: (%d, %d) with a minimum distance of %d\n", p1, p2, minDist);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("There must be at least two points.\n");
        return 0;
    }

    int points[n];
    
    // Input points
    printf("Enter the points on the x-axis:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &points[i]);
    }

    // Find and display the closest pair
    findClosestPair(points, n);

    return 0;
}
