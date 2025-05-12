#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define structure for tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Queue for level-order traversal
struct Queue {
    struct TreeNode* arr[MAX];
    int front, rear;
};

// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Initialize queue
void initQueue(struct Queue* q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(struct Queue* q) {
    return q->front == -1;
}

// Enqueue
void enqueue(struct Queue* q, struct TreeNode* node) {
    if (q->rear == MAX - 1) return;

    if (q->front == -1)
        q->front = 0;
    q->arr[++(q->rear)] = node;
}

// Dequeue
struct TreeNode* dequeue(struct Queue* q) {
    if (isEmpty(q)) return NULL;
    struct TreeNode* temp = q->arr[q->front];

    if (q->front == q->rear) // Last element
        q->front = q->rear = -1;
    else
        q->front++;

    return temp;
}

// a. Level-order display (non-recursive)
void levelOrder(struct TreeNode* root) {
    if (root == NULL) return;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    printf("Level-wise traversal:\n");
    while (!isEmpty(&q)) {
        struct TreeNode* node = dequeue(&q);
        printf("%d ", node->data);

        if (node->left)
            enqueue(&q, node->left);
        if (node->right)
            enqueue(&q, node->right);
    }
    printf("\n");
}

// b. Mirror image (non-recursive using queue)
void mirrorTree(struct TreeNode* root) {
    if (root == NULL) return;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        struct TreeNode* node = dequeue(&q);

        // Swap left and right
        struct TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;

        if (node->left)
            enqueue(&q, node->left);
        if (node->right)
            enqueue(&q, node->right);
    }
}

// c. Display height (non-recursive)
int treeHeight(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int height = 0;

    while (!isEmpty(&q)) {
        int levelSize = q.rear - q.front + 1;
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = dequeue(&q);
            if (node->left)
                enqueue(&q, node->left);
            if (node->right)
                enqueue(&q, node->right);
        }
        height++;
    }

    return height;
}

// d. Count leaf nodes (non-recursive)
int countLeafNodes(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int leafCount = 0;
    while (!isEmpty(&q)) {
        struct TreeNode* node = dequeue(&q);

        if (node->left == NULL && node->right == NULL)
            leafCount++;

        if (node->left)
            enqueue(&q, node->left);
        if (node->right)
            enqueue(&q, node->right);
    }

    return leafCount;
}

// Sample tree creation (can be modified to take user input)
struct TreeNode* createSampleTree() {
    struct TreeNode* root = createNode(10);
    root->left = createNode(7);
    root->right = createNode(12);
    root->left->left = createNode(20);
    root->left->right = createNode(25);
    root->right->left = createNode(17);
    root->right->right = createNode(55);
    return root;
}

// Main function
int main() {
    struct TreeNode* root = createSampleTree();

    printf("Original Tree:\n");
    levelOrder(root);

    printf("Height of Tree: %d\n", treeHeight(root));

    mirrorTree(root);

    printf("Mirror Image Tree:\n");
    levelOrder(root);

    printf("Height of Mirror Tree: %d\n", treeHeight(root));

    printf("Number of Leaf Nodes in Mirror Tree: %d\n", countLeafNodes(root));
    return 0;
}
