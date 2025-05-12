#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue for level order traversal (for non-recursive height)
typedef struct Queue {
    Node* node;
    struct Queue* next;
} Queue;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a node into BST
Node* insert(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Inorder traversal (Left, Root, Right)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to create a mirror copy of a tree
Node* mirrorCopy(Node* root) {
    if (root == NULL)
        return NULL;
    Node* newRoot = createNode(root->data);
    newRoot->left = mirrorCopy(root->right);
    newRoot->right = mirrorCopy(root->left);
    return newRoot;
}

// Function to mirror the tree in place
void mirrorInPlace(Node* root) {
    if (root == NULL)
        return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirrorInPlace(root->left);
    mirrorInPlace(root->right);
}

// Queue operations for level order traversal (used in height function)
void enqueue(Queue** front, Queue** rear, Node* node) {
    Queue* temp = (Queue*)malloc(sizeof(Queue));
    temp->node = node;
    temp->next = NULL;
    if (*rear == NULL) {
        *front = *rear = temp;
        return;
    }
    (*rear)->next = temp;
    *rear = temp;
}

Node* dequeue(Queue** front, Queue** rear) {
    if (*front == NULL)
        return NULL;
    Queue* temp = *front;
    Node* node = temp->node;
    *front = (*front)->next;
    if (*front == NULL)
        *rear = NULL;
    free(temp);
    return node;
}

int isEmpty(Queue* front) {
    return front == NULL;
}

// Function to find height of tree without recursion
int treeHeight(Node* root) {
    if (root == NULL)
        return 0;
    
    Queue* front = NULL;
    Queue* rear = NULL;
    enqueue(&front, &rear, root);
    int height = 0;
    
    while (1) {
        int nodeCount = 0;
        Queue* temp = front;
        
        // Count nodes at current level
        while (temp != NULL) {
            nodeCount++;
            temp = temp->next;
        }
        
        if (nodeCount == 0)
            return height;
        
        height++;
        
        // Process all nodes at current level
        while (nodeCount > 0) {
            Node* node = dequeue(&front, &rear);
            if (node->left)
                enqueue(&front, &rear, node->left);
            if (node->right)
                enqueue(&front, &rear, node->right);
            nodeCount--;
        }
    }
}

// Free memory
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function
int main() {
    Node* root = NULL;
    int choice, data;
    
    do {
        printf("\n1. Insert\n2. Display Inorder\n3. Display Mirror Image Without Changing Original\n4. Display Mirror Image By Modifying Tree\n5. Display Height (Non-Recursive)\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3: {
                Node* mirrorRoot = mirrorCopy(root);
                printf("Mirror Image (Inorder Traversal): ");
                inorder(mirrorRoot);
                printf("\n");
                freeTree(mirrorRoot);
                break;
            }
            case 4:
                mirrorInPlace(root);
                printf("Tree has been mirrored (Inorder Traversal): ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Height of tree (non-recursive): %d\n", treeHeight(root));
                break;
            case 6:
                printf("Exiting...\n");
                freeTree(root);
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);
    
    return 0;
}
