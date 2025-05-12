#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

// Create a new node
struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Insert node at the end
void insertEnd(struct Node **head, int value)
{
    struct Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

// Print the list
void printList(struct Node *head)
{
    while (head != NULL)
    {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Merge two sorted doubly linked lists
struct Node *mergeSortedLists(struct Node *head1, struct Node *head2)
{
    struct Node *mergedHead = NULL;
    struct Node *tail = NULL;

    while (head1 && head2)
    {
        struct Node *temp;
        if (head1->data < head2->data)
        {
            temp = head1;
            head1 = head1->next;
        }
        else
        {
            temp = head2;
            head2 = head2->next;
        }
        temp->next = temp->prev = NULL;

        if (!mergedHead)
        {
            mergedHead = tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    struct Node *remaining;
    if (head1 != NULL)
        remaining = head1;
    else
        remaining = head2;

    while (remaining)
    {
        struct Node *temp = remaining;
        remaining = remaining->next;
        temp->next = temp->prev = NULL;

        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }

    return mergedHead;
}

// Input list from user
void inputList(struct Node **head, int listNumber)
{
    int n, value;
    printf("Enter number of elements in List %d: ", listNumber);
    scanf("%d", &n);

    printf("Enter %d sorted elements for List %d:\n", n, listNumber);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value);
        insertEnd(head, value);
    }
}

// Main function
int main()
{
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;

    inputList(&list1, 1);
    inputList(&list2, 2);

    printf("\nList 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);

    struct Node *mergedList = mergeSortedLists(list1, list2);

    printf("\nMerged Sorted List: ");
    printList(mergedList);

    return 0;
}
