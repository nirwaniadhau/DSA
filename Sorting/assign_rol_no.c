#include <stdio.h>
#include <string.h>

// Define student structure
typedef struct {
    char name[50];
    int marks;
    int roll_no;
} Student;

// Swap function
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
int partition(Student arr[], int low, int high) {
    int pivot = arr[high].marks; // pivot is marks
    int i = low - 1;

    for (int j = low; j <= high -1; j++) {
        if (arr[j].marks > pivot) { // Sorting in descending order
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

// Quick Sort
void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    Student s[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Student %d\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", s[i].name);
        printf("Marks: ");
        scanf("%d", &s[i].marks);
    }

    // Sort students by marks descending
    quickSort(s, 0, n-1);

    // Assign roll numbers
    for (int i = 0; i < n; i++) {
        s[i].roll_no = i + 1;
    }

    // Display
    printf("\n--- Roll Number Assignment ---\n");
    for (int i = 0; i < n; i++) {
        printf("Roll No: %d, Name: %s, Marks: %d\n", s[i].roll_no, s[i].name, s[i].marks);
    }

    return 0;
}
