#include <stdio.h>
#include <string.h>

// Define structure
typedef struct {
    char name[50];
    float height;
    float weight;
    float average;
} Employee;

// Swap function
void swap(Employee *a, Employee *b) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort by average
void sortEmployees(Employee emp[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (emp[j].average > emp[j+1].average) {
                swap(&emp[j], &emp[j+1]);
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    Employee emp[n];

    // Input employees
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", emp[i].name);
        printf("Height (in cm): ");
        scanf("%f", &emp[i].height);
        printf("Weight (in kg): ");
        scanf("%f", &emp[i].weight);

        // Calculate average
        emp[i].average = (emp[i].height + emp[i].weight) / 2;
    }

    // Sort employees by average
    sortEmployees(emp, n);

    // Display
    printf("\n--- Sorted List of Employees by Average ---\n");
    printf("Name\t\tHeight\tWeight\tAverage\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t\t%.2f\t%.2f\t%.2f\n", emp[i].name, emp[i].height, emp[i].weight, emp[i].average);
    }

    return 0;
}
