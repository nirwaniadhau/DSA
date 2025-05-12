#include <stdio.h>
#include <string.h>

// Define the Faculty structure
typedef struct {
    char faculty_name[50];
    int faculty_ID;
    char subject_codes[100];
    char class_names[100];
} Faculty;

// Function to swap two faculty records
void swap(Faculty *a, Faculty *b) {
    Faculty temp = *a;
    *a = *b;
    *b = temp;
}

// Merge function for Merge Sort
void merge(Faculty arr[], int l, int m, int r, int *swap_count) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Faculty L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;

    while (i < n1 && j < n2) {
        if (L[i].faculty_ID <= R[j].faculty_ID) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            (*swap_count)++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort
void mergeSort(Faculty arr[], int l, int r, int *swap_count) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, swap_count);
        mergeSort(arr, m + 1, r, swap_count);
        merge(arr, l, m, r, swap_count);
    }
}

// Heapify function for Heap Sort
void heapify(Faculty arr[], int n, int i, int *swap_count) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left].faculty_ID > arr[largest].faculty_ID)
        largest = left;
    
    if (right < n && arr[right].faculty_ID > arr[largest].faculty_ID)
        largest = right;
    
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        (*swap_count)++;
        heapify(arr, n, largest, swap_count);
    }
}

// Heap Sort
void heapSort(Faculty arr[], int n, int *swap_count) {
    *swap_count = 0;

    // Build heap (rearrange array)
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i, swap_count);

    // Extract elements from heap
    for (int i = n-1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        (*swap_count)++;
        heapify(arr, i, 0, swap_count);
    }
}

// Function to print faculty list
void printFaculties(Faculty arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, ID: %d, Subjects: %s, Classes: %s\n",
            arr[i].faculty_name, arr[i].faculty_ID, arr[i].subject_codes, arr[i].class_names);
    }
}

int main() {
    int n, i;
    int mergeSwapCount = 0, heapSwapCount = 0;

    printf("Enter number of faculties: ");
    scanf("%d", &n);

    Faculty faculties[n], faculties_copy[n];

    for (i = 0; i < n; i++) {
        printf("\nEnter details for faculty %d:\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", faculties[i].faculty_name);
        printf("Faculty ID: ");
        scanf("%d", &faculties[i].faculty_ID);
        printf("Subject Codes: ");
        scanf(" %[^\n]", faculties[i].subject_codes);
        printf("Class Names: ");
        scanf(" %[^\n]", faculties[i].class_names);
    }

    // Copy array for second sort
    for (i = 0; i < n; i++)
        faculties_copy[i] = faculties[i];

    // Merge Sort
    printf("\nApplying Merge Sort...\n");
    mergeSort(faculties, 0, n-1, &mergeSwapCount);
    printFaculties(faculties, n);
    printf("Total swaps (comparisons where right side inserted first) in Merge Sort: %d\n", mergeSwapCount);

    // Heap Sort
    printf("\nApplying Heap Sort...\n");
    heapSort(faculties_copy, n, &heapSwapCount);
    printFaculties(faculties_copy, n);
    printf("Total swaps in Heap Sort: %d\n", heapSwapCount);

    return 0;
}
