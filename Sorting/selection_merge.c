#include <stdio.h>
#include <string.h>

// Define the Student structure
typedef struct {
    char name[50];
    int roll_no;
    float total_marks;
} Student;

// Function to swap two students
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// Selection Sort with swap count
void selectionSort(Student arr[], int n, int *swap_count) {
    int i, j, min_idx;
    *swap_count = 0;
    
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j].roll_no < arr[min_idx].roll_no) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx]);
            (*swap_count)++;
        }
    }
}

// Merge function for Merge Sort (counts swaps when merging)
void merge(Student arr[], int l, int m, int r, int *swap_count) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    Student L[n1], R[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i].roll_no <= R[j].roll_no) {
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

// Merge Sort function
void mergeSort(Student arr[], int l, int r, int *swap_count) {
    if (l < r) {
        int m = l + (r - l) / 2;
        
        mergeSort(arr, l, m, swap_count);
        mergeSort(arr, m+1, r, swap_count);
        
        merge(arr, l, m, r, swap_count);
    }
}

// Function to print array
void printStudents(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Roll No: %d, Marks: %.2f\n",
               arr[i].name, arr[i].roll_no, arr[i].total_marks);
    }
}

int main() {
    int n, i;
    int selectionSwapCount = 0, mergeSwapCount = 0;
    
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    Student students[n], students_copy[n];
    
    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);
        printf("Roll No: ");
        scanf("%d", &students[i].roll_no);
        printf("Total Marks: ");
        scanf("%f", &students[i].total_marks);
    }
    
    // Make a copy for merge sort
    for (i = 0; i < n; i++)
        students_copy[i] = students[i];
    
    // Selection Sort
    printf("\nApplying Selection Sort...\n");
    selectionSort(students, n, &selectionSwapCount);
    printStudents(students, n);
    printf("Total swaps performed in Selection Sort: %d\n", selectionSwapCount);
    
    // Merge Sort
    printf("\nApplying Merge Sort...\n");
    mergeSort(students_copy, 0, n-1, &mergeSwapCount);
    printStudents(students_copy, n);
    printf("Total swaps performed in Merge Sort: %d\n", mergeSwapCount);
    
    return 0;
}
