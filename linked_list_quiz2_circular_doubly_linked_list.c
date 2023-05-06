#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
    struct __list *prev;
} list;

list *pop_first_node(list **start) {
    if (!*start)
        return NULL;
    list *first = *start;
    if (first->next == first) {
        *start = NULL;
        return first;
    }
    list *last = first->prev;
    *start = first->next;
    first->next->prev = last;
    last->next = first->next;
    return first;
}

void append_node(list **start, list *new_node) {
    if (!*start) {
        *start = new_node;
        new_node->prev = new_node->next = new_node;
        return;
    }
    list *last = (*start)->prev;
    new_node->next = *start;
    (*start)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}

list *sort(list *start) {
    if (!start || start->next == start)
        return start;
    list *left = start;
    list *right = left->next;
    right->prev = start->prev;
    start->prev->next = right;
    left->next = start;
    left->prev = start;

    left = sort(left);
    right = sort(right);

    list *result = NULL;
    while (left && right) {
        list *node;
        if (left->data < right->data) {
            node = pop_first_node(&left);
        } else {
            node = pop_first_node(&right);
        }
        append_node(&result, node);
    }

    list *remaining = left ? left : right;

    if (remaining) {
        list *last = remaining->prev;
        result->prev->next = remaining;
        remaining->prev = result->prev;

        result->prev = last;
        result->prev->next = result;
    }

    return result;
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
    for (int i = 0; i < MAX; i++) {
        list *new_node = malloc(sizeof(list));
        new_node->data = MAX - i;
        append_node(&start, new_node);
    }

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
