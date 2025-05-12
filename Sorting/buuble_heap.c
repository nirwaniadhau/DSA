#include <stdio.h>
#include <string.h>

// Define the Employee structure
typedef struct {
    char name[50];
    int emp_no;
    float salary;
} Employee;

// Function to swap two employees
void swap(Employee *a, Employee *b) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort with swap count
void bubbleSort(Employee arr[], int n, int *swap_count) {
    int i, j;
    *swap_count = 0;
    
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j].emp_no > arr[j+1].emp_no) {
                swap(&arr[j], &arr[j+1]);
                (*swap_count)++;
            }
        }
    }
}

// Heapify function for Heap Sort
void heapify(Employee arr[], int n, int i, int *swap_count) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if (left < n && arr[left].emp_no > arr[largest].emp_no)
        largest = left;
    
    if (right < n && arr[right].emp_no > arr[largest].emp_no)
        largest = right;
    
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        (*swap_count)++;
        heapify(arr, n, largest, swap_count);
    }
}

// Heap Sort with swap count
void heapSort(Employee arr[], int n, int *swap_count) {
    *swap_count = 0;
    
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swap_count);
    
    // Extract elements from heap one by one
    for (int i = n-1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        (*swap_count)++;
        heapify(arr, i, 0, swap_count);
    }
}

// Function to print Employee array
void printEmployees(Employee arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Emp No: %d, Salary: %.2f\n",
               arr[i].name, arr[i].emp_no, arr[i].salary);
    }
}

int main() {
    int n, i;
    int bubbleSwapCount = 0, heapSwapCount = 0;
    
    printf("Enter number of employees: ");
    scanf("%d", &n);
    
    Employee employees[n], employees_copy[n];
    
    for (i = 0; i < n; i++) {
        printf("\nEnter details for employee %d:\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", employees[i].name);
        printf("Emp No: ");
        scanf("%d", &employees[i].emp_no);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }
    
    // Make a copy for Heap Sort
    for (i = 0; i < n; i++)
        employees_copy[i] = employees[i];
    
    // Bubble Sort
    printf("\nApplying Bubble Sort...\n");
    bubbleSort(employees, n, &bubbleSwapCount);
    printEmployees(employees, n);
    printf("Total swaps performed in Bubble Sort: %d\n", bubbleSwapCount);
    
    // Heap Sort
    printf("\nApplying Heap Sort...\n");
    heapSort(employees_copy, n, &heapSwapCount);
    printEmployees(employees_copy, n);
    printf("Total swaps performed in Heap Sort: %d\n", heapSwapCount);
    
    return 0;
}
