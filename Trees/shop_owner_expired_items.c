#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for each product
typedef struct Product {
    int code;
    char name[50];
    float price;
    int stock;
    char dateReceived[11];
    char expirationDate[11];
    struct Product *left, *right;
} Product;

// Function to create a new product node
Product* createProduct(int code, char name[], float price, int stock, char dateReceived[], char expirationDate[]) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    newProduct->code = code;
    strcpy(newProduct->name, name);
    newProduct->price = price;
    newProduct->stock = stock;
    strcpy(newProduct->dateReceived, dateReceived);
    strcpy(newProduct->expirationDate, expirationDate);
    newProduct->left = newProduct->right = NULL;
    return newProduct;
}

// Insert product into BST based on code
Product* insert(Product* root, int code, char name[], float price, int stock, char dateReceived[], char expirationDate[]) {
    if (root == NULL) {
        return createProduct(code, name, price, stock, dateReceived, expirationDate);
    }
    if (code < root->code) {
        root->left = insert(root->left, code, name, price, stock, dateReceived, expirationDate);
    } else if (code > root->code) {
        root->right = insert(root->right, code, name, price, stock, dateReceived, expirationDate);
    } else {
        printf("Duplicate code not allowed!\n");
    }
    return root;
}

// Compare two dates in format YYYY-MM-DD
int isExpired(char* expDate, char* currentDate) {
    return strcmp(expDate, currentDate) < 0;
}

// Preorder traversal to list expired products
void listExpiredPrefix(Product* root, char* currentDate) {
    if (root) {
        if (isExpired(root->expirationDate, currentDate)) {
            printf("Code: %d, Name: %s, Price: %.2f, Stock: %d, Received: %s, Expires: %s\n",
                   root->code, root->name, root->price, root->stock, root->dateReceived, root->expirationDate);
        }
        listExpiredPrefix(root->left, currentDate);
        listExpiredPrefix(root->right, currentDate);
    }
}

// Inorder traversal to list all products
void listAll(Product* root) {
    if (root) {
        listAll(root->left);
        printf("Code: %d, Name: %s, Price: %.2f, Stock: %d, Received: %s, Expires: %s\n",
               root->code, root->name, root->price, root->stock, root->dateReceived, root->expirationDate);
        listAll(root->right);
    }
}

// Find minimum node (helper for delete)
Product* findMin(Product* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Delete a product by code
Product* deleteByCode(Product* root, int code) {
    if (root == NULL)
        return NULL;
    if (code < root->code) {
        root->left = deleteByCode(root->left, code);
    } else if (code > root->code) {
        root->right = deleteByCode(root->right, code);
    } else {
        // Node found
        if (root->left == NULL) {
            Product* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Product* temp = root->left;
            free(root);
            return temp;
        } else {
            Product* temp = findMin(root->right);
            root->code = temp->code;
            strcpy(root->name, temp->name);
            root->price = temp->price;
            root->stock = temp->stock;
            strcpy(root->dateReceived, temp->dateReceived);
            strcpy(root->expirationDate, temp->expirationDate);
            root->right = deleteByCode(root->right, temp->code);
        }
    }
    return root;
}

// Delete all expired products
Product* deleteExpired(Product* root, char* currentDate) {
    if (root == NULL)
        return NULL;
    root->left = deleteExpired(root->left, currentDate);
    root->right = deleteExpired(root->right, currentDate);
    if (isExpired(root->expirationDate, currentDate)) {
        root = deleteByCode(root, root->code);
    }
    return root;
}

// Free the tree
void freeTree(Product* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function
int main() {
    Product* root = NULL;
    int choice, code, stock;
    char name[50], dateReceived[11], expirationDate[11];
    float price;
    char currentDate[11];
    
    printf("Enter current date (YYYY-MM-DD): ");
    scanf("%s", currentDate);
    
    do {
        printf("\n1. Insert Product\n2. List Expired Products (Prefix Order)\n3. List All Products\n4. Delete Product by Code\n5. Delete All Expired Products\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter code: ");
                scanf("%d", &code);
                printf("Enter name: ");
                scanf(" %[^\n]", name);
                printf("Enter price: ");
                scanf("%f", &price);
                printf("Enter stock amount: ");
                scanf("%d", &stock);
                printf("Enter date received (YYYY-MM-DD): ");
                scanf("%s", dateReceived);
                printf("Enter expiration date (YYYY-MM-DD): ");
                scanf("%s", expirationDate);
                root = insert(root, code, name, price, stock, dateReceived, expirationDate);
                break;
            case 2:
                printf("Expired Products:\n");
                listExpiredPrefix(root, currentDate);
                break;
            case 3:
                printf("All Products:\n");
                listAll(root);
                break;
            case 4:
                printf("Enter code to delete: ");
                scanf("%d", &code);
                root = deleteByCode(root, code);
                break;
            case 5:
                root = deleteExpired(root, currentDate);
                printf("All expired products deleted.\n");
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
