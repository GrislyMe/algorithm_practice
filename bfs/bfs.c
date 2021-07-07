#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct node {
    int value;
    node *left;
    node *right;
};

typedef struct stack stack;
typedef struct stack{
    node *value;
    stack *pre;
};
stack *current = NULL;

void push(node *p) {
    stack *temp;
    if(current) {
        temp = malloc(sizeof(stack));
        temp->pre = current;
        current = temp;
        current->value = p;
    } else {
        current = malloc(sizeof(stack));
        current->pre = NULL;
        current->value = p;
    }
}

node pop() {
    stack *temp;
    node *p;
    temp = current;
    p = temp->value;
    current = current->pre;
    free(temp);
    return p;
}

int main() {
    while(ndoe->left || node->right) {
        if(node->left) {
            push(node->left);
        }
        if(node->right) {
            push(node->right);
        }
        printf("%d ", node->value);
        node = pop();
    }
}
