/*
    This C program implements a stack using a linked list.
*/

#include<stdio.h>
#include<stdlib.h>

// Struct to hold the data and the pointer to the next element.
struct element
{ 
    char data; 
    struct element* next; 
};
// Append the new element to the start of the stack
void push(char data, struct element** stack)
{
    struct element* Element = (struct element*)malloc(sizeof(struct element)); 
    Element -> data = data; 
    Element -> next = *stack;  
    (*stack) = Element;  
}
// Remove element from the top of the stack
void pop(struct element** stack)
{
    if(*stack != NULL){
        printf("Element popped: %c\n",(*stack) -> data);
        struct element* tempPtr = *stack;
        *stack = (*stack) -> next;
        free(tempPtr);
    }
    else{
        printf("The stack is empty.\n");
    }
}

// Display the element at the top of the stack
void top(struct element* stack)
{
    if(stack != NULL){
    printf("Element on top: %c\n", stack -> data);
    }
    else{
        printf("The stack is empty.\n");
    }
}

int main() 
{
    struct element* root = (struct element*)malloc(sizeof(struct element));
    root -> data = 'a';
    root -> next = NULL;
    top(root);
    push('b',&root);
    top(root);
    push('c',&root);
    top(root);
    pop(&root);
    top(root);
    pop(&root);
    top(root);
    pop(&root);
    top(root);
    pop(&root);
    return 0;
}