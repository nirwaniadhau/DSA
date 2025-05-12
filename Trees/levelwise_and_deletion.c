#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Queue structure for level order
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

// Create a new node
Node* createNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert into BST
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

// Find the minimum node
Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete node from BST
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
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
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Initialize queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Enqueue
void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL)
        q->front = q->rear = temp;
    else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

// Dequeue
Node* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    Node* node = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return node;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Level-wise display (Breadth-First)
void levelOrder(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);

    printf("Level-wise Display: ");
    while (!isEmpty(q)) {
        Node* temp = dequeue(q);
        printf("%d ", temp->key);

        if (temp->left) enqueue(q, temp->left);
        if (temp->right) enqueue(q, temp->right);
    }
    printf("\n");
    free(q);
}

int main() {
    Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Display Level-wise\n4. Exit\nChoice: ");
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
            levelOrder(root);
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
