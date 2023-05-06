#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

list *sort(list *start) {
    if (!start || start->next == start)
        return start;
    list *left = start;
    list *right = left->next;

    left->next = start;
    list *current = right;
    while (current->next != start)
        current = current->next;
    current->next = right;

    left = sort(left);
    right = sort(right);

    current = left;
    while (current->next != left)
        current = current->next;
    current->next = NULL;

    current = right;
    while (current->next != right)
        current = current->next;
    current->next = NULL;

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
        merge->next = start;
    }
    return start;
}

void append_node(list **start, int data) {
    list *new_node = malloc(sizeof(list));
    new_node->data = data;
    if (!*start) {
        *start = new_node;
        new_node->next = new_node;
        return;
    }
    list *current = *start;
    while (current->next != *start)
        current = current->next;
    current->next = new_node;
    new_node->next = *start;
}

void print_list(list *start) {
    printf("%d ", start->data);
    for (list *current = start->next; current != start; current = current->next)
        printf("%d ", current->data);
    printf("\n");
}

int main() {
    const int MAX = 10;

    list *start = NULL;
    for (int i = 0; i < MAX; i++)
        append_node(&start, MAX - i);

    print_list(start);

    start = sort(start);

    print_list(start);

    list *current = start;
    for (int i = 0; i < MAX; i++) {
        list *next = current->next;
        free(current);
        current = next;
    }
    return 0;
}
