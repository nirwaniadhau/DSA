    #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    int marks;
    int roll;
    struct Student *left, *right;
} Student;

// Create a new node
Student* createNode(char name[], int marks) {
    Student* new = (Student*)malloc(sizeof(Student));
    strcpy(new->name, name);
    new->marks = marks;
    new->roll = 0;
    new->left = new->right = NULL;
    return new;
}

// Insert by marks (higher marks go to the left for descending order)
Student* insert(Student* root, char name[], int marks) {
    if (!root) return createNode(name, marks);
    if (marks > root->marks)
        root->left = insert(root->left, name, marks);
    else
        root->right = insert(root->right, name, marks);
    return root;
}

// Assign roll numbers in descending order of marks
void assignRolls(Student* root, int* roll) {
    if (!root) return;
    assignRolls(root->left, roll);
    root->roll = (*roll)++;
    assignRolls(root->right, roll);
}

// Display tree in-order (roll number order)
void display(Student* root) {
    if (!root) return;
    display(root->left);
    printf("Roll No: %d\tName: %s\tMarks: %d\n", root->roll, root->name, root->marks);
    display(root->right);
}

int main() {
    Student* root = NULL;
    int n, marks;
    char name[50];

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter name of student %d: ", i + 1);
        scanf("%s", name);
        printf("Enter marks of %s: ", name);
        scanf("%d", &marks);
        root = insert(root, name, marks);
    }

    int roll = 1;
    assignRolls(root, &roll);

    printf("\n--- Assigned Roll Numbers (Topper gets Roll No. 1) ---\n");
    display(root);

    return 0;
}
