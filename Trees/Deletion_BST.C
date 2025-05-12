#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Create a new node
Node* createNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert a key in BST
Node* insert(Node* root, int key) {
    if (root == NULL) return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        printf("Key already exists.\n");
    return root;
}

// Find the minimum node in BST
Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete a node from BST
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // One child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Two children: Replace with inorder successor
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Non-recursive postorder traversal using two stacks
void postorderNonRecursive(Node* root) {
    if (root == NULL) return;

    Node* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    while (top1 != -1) {
        Node* curr = stack1[top1--];
        stack2[++top2] = curr;

        if (curr->left) stack1[++top1] = curr->left;
        if (curr->right) stack1[++top1] = curr->right;
    }

    printf("Postorder (Non-Recursive): ");
    while (top2 != -1) {
        printf("%d ", stack2[top2--]->key);
    }
    printf("\n");
}

int main() {
    Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Display Postorder (Non-Recursive)\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
        }
        else if (choice == 2) {
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
        }
        else if (choice == 3) {
            postorderNonRecursive(root);
        }
        else if (choice == 4) {
            printf("Exiting.\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
