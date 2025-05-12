#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int emp_id;
    char name[50];
    float salary;
    struct Employee *left, *right;
} Employee;

// Create a new node
Employee* createNode(int id, char name[], float salary) {
    Employee* new = (Employee*)malloc(sizeof(Employee));
    new->emp_id = id;
    strcpy(new->name, name);
    new->salary = salary;
    new->left = new->right = NULL;
    return new;
}

// Insert based on emp_id
Employee* insert(Employee* root, int id, char name[], float salary) {
    if (!root) return createNode(id, name, salary);
    if (id < root->emp_id)
        root->left = insert(root->left, id, name, salary);
    else if (id > root->emp_id)
        root->right = insert(root->right, id, name, salary);
    else
        printf("Duplicate ID not allowed: %d\n", id);
    return root;
}

// Search by emp_id
Employee* search(Employee* root, int id) {
    while (root) {
        if (id == root->emp_id)
            return root;
        else if (id < root->emp_id)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// Inorder traversal for ascending order
void inorder(Employee* root) {
    if (!root) return;
    inorder(root->left);
    printf("ID: %d\tName: %s\tSalary: %.2f\n", root->emp_id, root->name, root->salary);
    inorder(root->right);
}

int main() {
    Employee* root = NULL;
    int choice, id;
    char name[50];
    float salary;

    do {
        printf("\nMenu:\n1. Insert Employee\n2. Search Employee\n3. Display All (Sorted by ID)\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Salary: ");
                scanf("%f", &salary);
                root = insert(root, id, name, salary);
                break;

            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                Employee* found = search(root, id);
                if (found)
                    printf("Found -> ID: %d, Name: %s, Salary: %.2f\n", found->emp_id, found->name, found->salary);
                else
                    printf("Employee with ID %d not found.\n", id);
                break;

            case 3:
                printf("\nEmployees sorted by ID:\n");
                inorder(root);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    return 0;
}
