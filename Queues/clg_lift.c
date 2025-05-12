/*There is a lift in our college. Students, staff and guest are utilizing it.
Students are using the lift when no staff is there. Whenever staff is in the
lift students are moving out of the lift. Whenever HOD's / Dean's /
Director want to use lift then staff are moving out of the lift. It means
every entity which is using the lift is having some priority. High priority
entity will be served first. Simulate this situation by using appropriate
queue.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define NAME_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    int priority;  // 1 = HOD/Dean/Director, 2 = Staff, 3 = Student
} Person;

typedef struct {
    Person people[MAX];
    int count;
} Lift;

// Initialize the lift
void initLift(Lift *lift) {
    lift->count = 0;
}

// Function to determine priority from role
int getPriority(char role[]) {
    if (strcmp(role, "HOD") == 0 || strcmp(role, "Dean") == 0 || strcmp(role, "Director") == 0)
        return 1;
    else if (strcmp(role, "Staff") == 0)
        return 2;
    else if (strcmp(role, "Student") == 0)
        return 3;
    else
        return 4; // unknown
}

// Remove lower priority people from lift
void removeLowerPriority(Lift *lift, int newPriority) {
    int i, j;
    for (i = 0; i < lift->count; ) {
        if (lift->people[i].priority > newPriority) {
            printf("%s left the lift due to higher priority entity arriving.\n", lift->people[i].name);
            // Shift everyone else left
            for (j = i; j < lift->count - 1; j++) {
                lift->people[j] = lift->people[j+1];
            }
            lift->count--;
        } else {
            i++;
        }
    }
}

// Add a person to the lift
void enterLift(Lift *lift, char name[], char role[]) {
    if (lift->count == MAX) {
        printf("Lift is full! Cannot enter.\n");
        return;
    }

    int priority = getPriority(role);
    if (priority == 4) {
        printf("Unknown role entered. Cannot process.\n");
        return;
    }

    removeLowerPriority(lift, priority);

    lift->people[lift->count].priority = priority;
    strcpy(lift->people[lift->count].name, name);
    lift->count++;

    printf("%s (%s) entered the lift.\n", name, role);
}

// Display the people inside the lift
void displayLift(Lift *lift) {
    if (lift->count == 0) {
        printf("Lift is empty.\n");
        return;
    }

    printf("People currently in the lift:\n");
    for (int i = 0; i < lift->count; i++) {
        printf("- %s (Priority %d)\n", lift->people[i].name, lift->people[i].priority);
    }
}

int main() {
    Lift lift;
    int choice;
    char name[NAME_SIZE];
    char role[NAME_SIZE];

    initLift(&lift);

    do {
        printf("\n--- College Lift Management ---\n");
        printf("1. Enter lift\n");
        printf("2. Display lift status\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Enter role (Student/Staff/HOD/Dean/Director): ");
                fgets(role, NAME_SIZE, stdin);
                role[strcspn(role, "\n")] = 0;

                enterLift(&lift, name, role);
                break;

            case 2:
                displayLift(&lift);
                break;

            case 3:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
