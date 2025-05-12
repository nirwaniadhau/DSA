#include <stdio.h>

void findSwappedElements(int arr[], int n) {
    int x = -1, y = -1; // The two swapped elements
    int pos1 = -1, pos2 = -1;

    for (int i = 0; i < n-1; i++) {
        if (arr[i] > arr[i+1]) {
            if (x == -1) {
                // First time violation
                x = arr[i];
                pos1 = i;
            }
            // Second element to swap (may get updated)
            y = arr[i+1];
            pos2 = i+1;
        }
    }

    if (x != -1 && y != -1) {
        printf("Swapped elements are %d (position %d) and %d (position %d)\n", x, pos1, y, pos2);
    } else {
        printf("No swapped elements found.\n");
    }
}

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements of array:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    findSwappedElements(arr, n);

    return 0;
}
