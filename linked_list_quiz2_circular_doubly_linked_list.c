#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

list *sort(list *start) {
    if (!start || !start->next)
        return start;
    list *left = start;
    list *right = left->next;
    left->next = NULL;

    left = sort(left);
    right = sort(right);

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
    }
    return start;
}

void append_node(list **start, int data) {
    list *new_node = malloc(sizeof(list));
    new_node->data = data;
    new_node->next = NULL;
    if (!*start) {
        *start = new_node;
        return;
    }
    list *current = *start;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

void print_list(list *start) {
    for (list *current = start; current; current = current->next)
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
