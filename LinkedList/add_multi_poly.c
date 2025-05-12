#include <stdio.h>
#include <stdlib.h>
// Structure for a polynomial term
struct node
{
    float coeff;
    int expo;
    struct node *next;
};
// Function to insert a term into a polynomial in sorted order (descending
// exponent)
struct node *insertNode(struct node *head, float co, int ex)
{
    struct node *newP = (struct node *)malloc(sizeof(struct node));
    newP->coeff = co;
    newP->expo = ex;
    newP->next = NULL;
    if (head == NULL || head->expo < ex) {

        newP->next = head;
        return newP;
    }

    struct node *temp = head;
    while (temp->next != NULL && temp->next->expo > ex){
        temp = temp->next;
    }

    if (temp->next != NULL && temp->next->expo == ex){
        temp->next->coeff += co; // Combine like terms
    }
    else{
        newP->next = temp->next;
        temp->next = newP;
    }
    return head;
}


// Function to create a polynomial by taking user input
struct node *createNode(struct node *head)
{
    int n;
    float coeff;
    int expo;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%f %d", &coeff, &expo);
        head = insertNode(head, coeff, expo);
    }
    return head;
}


// Function to display a polynomial
void displayList(struct node *head)
{
    struct node *temp = head;

    if (head == NULL)
    {
        printf("0\n");
        return;
    }
    while (temp != NULL)
    {
        printf("%.1fx^%d", temp->coeff, temp->expo);
        temp = temp->next;
        if (temp != NULL)
        {
            printf(" + ");
        }
    }
    printf("\n");
}


// Function to add two polynomials
struct node *addPolynomials(struct node *p1, struct node *p2)
{
    struct node *result = NULL;
    while (p1 != NULL || p2 != NULL)
    {
        if (p2 == NULL || (p1 != NULL && p1->expo > p2->expo))
        {
            result = insertNode(result, p1->coeff, p1->expo);
            p1 = p1->next;
        }
        else if (p1 == NULL || (p2 != NULL && p2->expo > p1->expo))
        {
            result = insertNode(result, p2->coeff, p2->expo);
            p2 = p2->next;
        }
        else
        {
            result = insertNode(result, p1->coeff + p2->coeff, p1->expo);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return result;
}


// Function to multiply two polynomials
struct node *multiplyPolynomials(struct node *p1, struct node *p2)
{
    struct node *result = NULL;

    struct node *tempP2 = p2;
    while (p1 != NULL)
    {
        while (p2 != NULL)
        {
            result = insertNode(result, p1->coeff * p2->coeff, p1->expo + p2->expo);
            p2 = p2->next;
        }
        p2 = tempP2;
        p1 = p1->next;
    }
    return result;
}


// Main function
int main()
{
    struct node *head1 = NULL;
    struct node *head2 = NULL;
    struct node *sum = NULL;
    struct node *product = NULL;

    printf("Enter the first polynomial:\n");
    head1 = createNode(head1);

    printf("First Polynomial: ");
    displayList(head1);

    printf("\nEnter the second polynomial:\n");
    head2 = createNode(head2);

    printf("Second Polynomial: ");
    displayList(head2);

    // Polynomial Addition
    sum = addPolynomials(head1, head2);
    printf("\nSum of Polynomials: ");
    displayList(sum);

    // Polynomial Multiplication
    product = multiplyPolynomials(head1, head2);

    printf("\nProduct of Polynomials: ");
    displayList(product);
    return 0;
}
