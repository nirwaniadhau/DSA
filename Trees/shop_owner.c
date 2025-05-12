#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Product node
typedef struct Product {
    int code;
    char name[50];
    float price;
    int stock;
    char expiry[11];
    struct Product *left, *right;
} Product;

// Create a product node
Product* createProduct(int code, char name[], float price, int stock, char expiry[]) {
    Product* p = (Product*)malloc(sizeof(Product));
    p->code = code;
    strcpy(p->name, name);
    p->price = price;
    p->stock = stock;
    strcpy(p->expiry, expiry);
    p->left = p->right = NULL;
    return p;
}

// Insert product into BST
Product* insert(Product* root, Product* p) {
    if (!root) return p;
    if (p->code < root->code) root->left = insert(root->left, p);
    else if (p->code > root->code) root->right = insert(root->right, p);
    else printf("Product code exists.\n");
    return root;
}

// Find product by code
Product* find(Product* root, int code) {
    if (!root || root->code == code) return root;
    if (code < root->code) return find(root->left, code);
    return find(root->right, code);
}

// Check if expired
int isExpired(char expiry[]) {
    struct tm tm = {0};
    strptime(expiry, "%Y-%m-%d", &tm);
    time_t expTime = mktime(&tm);
    return difftime(expTime, time(NULL)) < 0;
}

// Show valid products (in-order)
void showValid(Product* root) {
    if (!root) return;
    showValid(root->left);
    if (!isExpired(root->expiry)) {
        printf("Code: %d | Name: %s | Price: %.2f | Stock: %d | Exp: %s\n",
               root->code, root->name, root->price, root->stock, root->expiry);
    }
    showValid(root->right);
}

int main() {
    Product* root = NULL;
    int choice;

    while (1) {
        printf("\n1. Insert\n2. Find & Update\n3. List Valid\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int code, stock;
            float price;
            char name[50], expiry[11];
            printf("Code: "); scanf("%d", &code);
            printf("Name: "); scanf(" %[^\n]", name);
            printf("Price: "); scanf("%f", &price);
            printf("Stock: "); scanf("%d", &stock);
            printf("Expiry (YYYY-MM-DD): "); scanf("%s", expiry);
            root = insert(root, createProduct(code, name, price, stock, expiry));
        }
        else if (choice == 2) {
            int code;
            printf("Code to find: ");
            scanf("%d", &code);
            Product* p = find(root, code);
            if (p) {
                printf("Found %s. Price: %.2f, Stock: %d\n", p->name, p->price, p->stock);
                printf("New price: "); scanf("%f", &p->price);
                printf("New stock: "); scanf("%d", &p->stock);
                printf("Updated.\n");
            } else {
                printf("Not found.\n");
            }
        }
        else if (choice == 3) {
            printf("\nValid Products:\n");
            showValid(root);
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
