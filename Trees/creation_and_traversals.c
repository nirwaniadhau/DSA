#include <stdio.h>
#include <stdlib.h>
#define MAX 100


struct Treenode {
    int data;
    struct Treenode* left;
    struct Treenode* right;
};


struct Stack {
    struct Treenode* arr[MAX];
    int top;
};


void initialize_stack(struct Stack* st) {
    st->top = -1;
}


int isFull(struct Stack* st) {
    return st->top == MAX - 1;
}


int isEmpty(struct Stack* st) {
    return st->top == -1;
   }


void push(struct Stack* st, struct Treenode* node) {
    if (isFull(st)) return;
    st->arr[++(st->top)] = node;
}


struct Treenode* pop(struct Stack* st) {
    if (isEmpty(st)) return NULL;
    return st->arr[(st->top)--];
}


struct Treenode* topNode(struct Stack* st) {
    if (!isEmpty(st))
        return st->arr[st->top];
    return NULL;
}


struct Treenode* create(int data) {
    struct Treenode* temp = (struct Treenode*)malloc(sizeof(struct Treenode));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}


void preorder(struct Treenode* root, struct Stack* st) {
    while (root != NULL ) {
        printf("%d -> ", root->data);
        push(st, root);
        root = root->left;
    }
        while (!isEmpty(st)) {
            root = pop(st);
            root = root->right;


        while(root!=NULL){
            printf("%d -> ", root->data);
            push(st, root);
            root = root->left;
        }
       
    }
}




void inorder(struct Treenode* root, struct Stack* st) {
    while (root != NULL ) {
        push(st, root);
        root = root->left;
    }
        while (!isEmpty(st)) {
            root=pop(st);
            printf("%d ->",root->data);
            root=root->right;


            while(root!=NULL){
                push(st, root);
                root = root->left;
            }
    }
}


void postorder(struct Treenode* root, struct Stack* st) {
    struct Treenode* prev = NULL;
    struct Stack tempStack;
    initialize_stack(&tempStack);


    while (root != NULL || !isEmpty(st)) {
        while (root != NULL) {
            push(st, root);
            root = root->left;
        }


        root = topNode(st);
        if (root->right == NULL || root->right == prev) {
            printf("%d -> ", root->data);
            pop(st);
            prev = root;
            root = NULL;
        } else {
            root = root->right;
        }
    }
}
int countNodes(struct Treenode* root) {
    if (root == NULL)
        return 0;

    struct Stack st;
    initialize_stack(&st);
    int count = 0;

    push(&st, root);

    while (!isEmpty(&st)) {
        struct Treenode* node = pop(&st);
        count++;

        // Push right and left children if they exist
        if (node->right)
            push(&st, node->right);
        if (node->left)
            push(&st, node->left);
    }

    return count;
}

struct Queue {
    struct Treenode* items[MAX];
    int front, rear;
};

void initializeQueue(struct Queue* q) {
    q->front = q->rear = -1;
}

int isQueueEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, struct Treenode* node) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++(q->rear)] = node;
}

struct Treenode* dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) return NULL;
    struct Treenode* node = q->items[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return node;
}

int height(struct Treenode* root) {
    if (root == NULL) return 0;

    struct Queue q;
    initializeQueue(&q);
    enqueue(&q, root);
    int height = 0;

    while (!isQueueEmpty(&q)) {
        int levelSize = q.rear - q.front + 1;

        for (int i = 0; i < levelSize; i++) {
            struct Treenode* node = dequeue(&q);
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
        }
        height++;
    }

    return height;
}



int main() {
    struct Treenode* root;
    struct Stack st;
    initialize_stack(&st);


    root = create(10);
    root->left = create(7);
    root->right = create(12);
    root->left->left = create(20);
    root->left->right = create(25);
    root->right->left = create(17);
    root->right->right = create(55);


    printf("Preorder Traversal:\n");
    preorder(root, &st);


    initialize_stack(&st);
    printf("\nInorder Traversal:\n");
    inorder(root, &st);


    initialize_stack(&st);
    printf("\nPostorder Traversal:\n");
    postorder(root, &st);

    int total = countNodes(root);
    printf("\nTotal number of nodes: %d\n", total);


    printf("\nHeight of the tree: %d\n", height(root));




    return 0;
}



