#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next, *prev;
};

void FuncA(struct node **start, int value) {
    if (!*start) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data = value;
        new_node->next = new_node->prev = new_node;
        *start = new_node;
        return;
    }
    struct node *last = (*start)->prev;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = *start;
    (*start)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}

void FuncB(struct node **start, int value) {
    struct node *last = (*start)->prev;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = *start;
    new_node->prev = last;
    last->next = (*start)->prev = new_node;
    *start = new_node;
}

void FuncC(struct node **start, int value1, int value2) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value1;
    struct node *temp = *start;
    while (temp->data != value2)
        temp = temp->next;
    struct node *next = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
    new_node->next = next;
    next->prev = new_node;
}


void separate(struct node *start, struct node **left, struct node **right) {
    struct node *slow = start, *fast = start->next;
    if (fast == start) {
        *left = start;
        *right = NULL;
        return;
    }
    while (fast != start && fast->next != start) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *left = start;
    *right = slow->next;

    // Deal with *right
    (*right)->prev = start->prev;
    start->prev->next = *right;

    // Deal with *left
    start->prev = slow;
    slow->next = start;
}

struct node *pop_first_node(struct node **start) {
    if (!*start)
        return NULL;
    struct node *last = (*start)->prev;
    struct node *first = *start;
    if (first == last) {
        *start = NULL;
        return first;
    }
    *start = first->next;
    (*start)->prev = last;
    last->next = *start;
    return first;
}

void append_node(struct node **start, struct node *new_node) {
    if (!*start) {
        *start = new_node;
        new_node->prev = new_node->next = new_node;
        return;
    }
    struct node *last = (*start)->prev;
    new_node->next = *start;
    (*start)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}

struct node *merge_linked_list(struct node *left, struct node *right) {
    struct node *result = NULL;
    while (left != NULL && right != NULL) {
        struct node *temp;
        if (left->data <= right->data) {
            temp = pop_first_node(&left);
        } else {
            temp = pop_first_node(&right);
        }
        append_node(&result, temp);
    }

    struct node *remainder = left ? left : right;
    while (remainder) {
        struct node *temp = pop_first_node(&remainder);
        append_node(&result, temp);
    }

    return result;
}

void merge_sort(struct node **start) {
    if (!*start || (*start)->next == *start)
        return;
    struct node *left, *right;
    separate(*start, &left, &right);
    merge_sort(&left);
    merge_sort(&right);
    *start = merge_linked_list(left, right);
}

void display(struct node *start) {
    struct node *temp = start;
    printf("Traversal in forward direction \n");
    for (; temp->next != start; temp = temp->next)
        printf("%d ", temp->data);
    printf("%d ", temp->data);
    printf("\nTraversal in reverse direction \n");
    struct node *last = start->prev;
    for (temp = last; temp->prev != last; temp = temp->prev)
        printf("%d ", temp->data);
    printf("%d ", temp->data);
    printf("\n");
}

int main() {
    struct node *start = NULL;
    FuncA(&start, 51);
    FuncB(&start, 48);
    FuncA(&start, 72);
    FuncA(&start, 86);
    FuncC(&start, 63, 51);
    merge_sort(&start);
    display(start);
    return 0;
}
