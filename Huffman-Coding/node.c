#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#include "node.h"

// This function is the constructor for a node. Since the function is of type
// Node *node it should return a pointer to Node.

Node *node_create(uint8_t symbol, uint64_t frequency) {
    // Dynamically allocate memory to n.
    Node *n = (Node *) malloc(sizeof(Node));

    // Set the nodes symbol as symbol and frequency as frequency.
    n->symbol = symbol;
    n->frequency = frequency;

    n->left = NULL;
    n->right = NULL;

    // Return the value of n.
    return n;
}

// This function serves as the destructor for the node. It's purpose is to
// delete nodes and since it is void type it should not return anything.

void node_delete(Node **n) {
    // Free n, set n equal to NULL and return nothing.
    free(*n);
    *n = NULL;
    return;
}

// The purpose of this function is to join a left and right child of the
// node. It should return a pointer to the created parent node.

Node *node_join(Node *left, Node *right) {
    // Find the sum of the left child and right child frequency.
    uint64_t sumf;
    sumf = left->frequency + right->frequency;

    // Assign the parent symbol as $ and create parent node.
    Node *p = node_create('$', sumf);

    // left and right nodes of parent.
    p->left = left;
    p->right = right;

    return p;
}

// The purpose of this function is to verify the nodes are created and
// joined correctly. Since this function is void typed, it should not return
// anything.

void node_print(Node *n) {
    // Debug and check if nodes are printed correctly.
    printf("This is the current node n: %lu\n", n->frequency);
    return;
}
