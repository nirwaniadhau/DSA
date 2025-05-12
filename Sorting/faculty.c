#include <stdio.h>
#include <string.h>

// Faculty structure
typedef struct {
    char name[50];
    int id;
    char designation[30];
    int rank; // 1 = Professor, 2 = Associate, 3 = Assistant
} Faculty;

// Function to get rank
int getRank(char designation[]) {
    if (strcmp(designation, "Professor") == 0)
        return 1;
    else if (strcmp(designation, "Associate Professor") == 0)
        return 2;
    else
        return 3;
}

// Simple sorting by rank
void sortFaculties(Faculty f[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (f[j].rank > f[j+1].rank) {
                Faculty temp = f[j];
                f[j] = f[j+1];
                f[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of faculties: ");
    scanf("%d", &n);

    Faculty f[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Faculty %d\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", f[i].name);
        printf("ID: ");
        scanf("%d", &f[i].id);
        printf("Designation (Professor/Associate Professor/Assistant Professor): ");
        scanf(" %[^\n]", f[i].designation);

        f[i].rank = getRank(f[i].designation);
    }

    // Sort
    sortFaculties(f, n);

    // Display
    printf("\n--- Sorted Faculty List ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s (ID: %d) - %s\n", f[i].name, f[i].id, f[i].designation);
    }

    return 0;
}
