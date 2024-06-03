#include <stdio.h>
#include <stdlib.h>

struct list_element {
    int data;
    struct list_element *next;
};

void printList(struct list_element *n) {
    while (n != NULL) {
         printf(" %d ", n->data);
         n = n->next;
    }
}

int main() {
    struct list_element* head = (struct list_element*)malloc(sizeof(struct list_element));
    struct list_element* second = (struct list_element*)malloc(sizeof(struct list_element));
    struct list_element* third = (struct list_element*)malloc(sizeof(struct list_element));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printList(head);

    return 0;
}
