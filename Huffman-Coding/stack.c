#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "stack.h"
#include "node.h"

// Create ADT for Stack as provided by the assignment 6 file. Capacity
// stores the capacity of the stack, top is used for top index and items
// store the number of items in the stack. The implementation of this function
// is very similar to that of the pq.c for the Priority Queue which is where
// the similarities of this implementation are.

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

// This function creates the stack and returns a pointer to the created
// stack.

Stack *stack_create(uint32_t capacity) {
    // Dynamically allocate space for Stack.
    Stack *s = (Stack *) malloc(sizeof(Stack));

    // Pass in the value of the capacity to pointer s.
    s->capacity = capacity;

    // Initialize necessary variables to be used in Stack.
    s->top = 0;

    // Allocate memmory to items.
    s->items = (Node **) calloc(capacity, sizeof(Node *));

    // return the pointer to the Stack.
    return s;
}

// This function serves as the destructor for the priority queue and
// sets the pointer to NULL after freeing such memory. Since this function
//

void stack_delete(Stack **s) {
    // Free the dynamically allocated memory to items from s and set
    // items to NULL before freeing s.

    free((*s)->items);
    (*s)->items = NULL;

    // Then, free the memory allocated in s and set s to NULL.
    free(*s);
    *s = NULL;

    // Return nothing since void function.
    return;
}

// The following function checks if the stack is empty. As such this function
// returns true if the function is empty and returns false if the function
// is not empty.

bool stack_empty(Stack *s) {
    // Check if the stack is empty using the top index.

    if (s->top != 0) {
        return false;
    }
    // Since it is empty, return true.
    return true;
}

// The following function checks if the stack is full. As such, this function
// returns true if the function is full and returns true if the function is
// empty.

bool stack_full(Stack *s) {
    // Check if the stack is full using the top index.

    if (s->top != s->capacity) {
        return false;
    }

    // Otherwise, return true if the stack is full.
    return true;
}

// This function returns the size of the stack as a uint32_t integer.

uint32_t stack_size(Stack *s) {
    // Return the value stored in the top variable.
    return s->top;
}

// This function pushes a node onto the stack and returns a pointer to the
// stack. This function returns false if the stack is false and true if it
// pushes succesfully.

bool stack_push(Stack *s, Node *n) {
    // Check if stack is full.
    if (s->top == s->capacity) {
        return false;
    }

    // Else, push the node into the stack at index top.
    s->items[s->top] = n;

    // Increment top by 1.
    s->top = s->top + 1;

    // Return true since pushing was succesful.
    return true;
}

// This function pops a node from the stack and returns a pointer to
// node popped from the stack. Since this function is of type Stack it
// returns a stack pointer. Note, the element of the array must be decremented
// first and then popped to get the right index to be popped. This is because
// of stack_push where to start at the 0th index, the node is pushed first
// and then increment it. This is also because the implementation of a stack
// is based on LIFO (last in first out) order which came from the Stacks and
// Queues lecture.

bool stack_pop(Stack *s, Node **n) {
    // Check if stack is empty.
    if (s->top == 0) {
        return false;
    }

    // Else, decrement top first and pop the node from the stack.
    s->top = s->top - 1;

    // Store the popped node to pointer n.
    *n = s->items[s->top];

    // Return true on successful pop.
    return true;
}

// This function is a debug function that shouldn't return anything.

void stack_print(Stack *s) {
    for (uint32_t x = 0; x < s->capacity; x++) {
        node_print(s->items[x]);
    }
    return;
}
