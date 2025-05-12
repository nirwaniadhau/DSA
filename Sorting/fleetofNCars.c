#include <stdio.h>

// Structure for each car
typedef struct {
    int car_id;
    int repair_time;
} Car;

// Swap two cars
void swap(Car *a, Car *b) {
    Car temp = *a;
    *a = *b;
    *b = temp;
}

// Sort cars by repair time (ascending order) using simple Bubble Sort
void sortCarsByRepairTime(Car cars[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (cars[j].repair_time > cars[j+1].repair_time) {
                swap(&cars[j], &cars[j+1]);
            }
        }
    }
}

// Function to calculate total lost service time
int calculateTotalLostTime(Car cars[], int n) {
    int total_time = 0;
    int current_time = 0;
    
    for (int i = 0; i < n; i++) {
        current_time += cars[i].repair_time;
        total_time += current_time;
    }
    
    return total_time;
}

int main() {
    int n;
    
    printf("Enter number of cars: ");
    scanf("%d", &n);
    
    Car cars[n];
    
    for (int i = 0; i < n; i++) {
        printf("\nEnter repair time for Car %d: ", i+1);
        cars[i].car_id = i+1;
        scanf("%d", &cars[i].repair_time);
    }
    
    // Sort cars by increasing repair time
    sortCarsByRepairTime(cars, n);
    
    printf("\nBest Repair Schedule (Car ID - Repair Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Car %d - %d hours\n", cars[i].car_id, cars[i].repair_time);
    }
    
    int total_lost_time = calculateTotalLostTime(cars, n);
    
    printf("\nTotal Lost Service Time: %d hours\n", total_lost_time);
    
    return 0;
}
