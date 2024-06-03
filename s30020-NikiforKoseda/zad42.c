#include <stdio.h>
#include <stdlib.h>

struct list_element {
    int data;
    struct list_element *next;
    struct list_element *prev;
};

void printList(struct list_element *n) {
    while (n != NULL) {
         printf(" %d ", n->data);
         n = n->next;
    }
}

int main() {
    
    int numElements;
    printf("Enter the number of list elements: ");
    scanf("%d", &numElements);

    struct list_element *head = NULL;
    struct list_element *tail = NULL;

    for (int i = 0; i < numElements; i++) {
        struct list_element *newNode = (struct list_element *)malloc(sizeof(struct list_element));

        printf("Enter data for element %d: ", i+1);
        scanf("%d", &(newNode->data));

        newNode->next = NULL;
        newNode->prev = tail;

        if (head == NULL) {
            head = newNode;
        } else {
            tail->next = newNode;
        }

        tail = newNode;
    }

    printList(head);

    return 0;
}
