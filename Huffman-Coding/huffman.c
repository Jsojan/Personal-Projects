#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include "pq.h"
#include "node.h"
#include "huffman.h"
#include "stack.h"
#include "io.h"
#include "defines.h"

// This function builds the huffman tree based on a computer histogram where
// the histogram will have ALPHABET number of indices. Since this function is
// of type Node it returns the root of the constructed Huffman Tree as the
// greatest parent Node.

Node *build_tree(uint64_t hist[static ALPHABET]) {
    // Build the priority queue by calling pq_create with size of
    // ALPHABET.
    PriorityQueue *h = pq_create(ALPHABET);

    // Initialize needed node pointers for enqueue and dequeue node.
    Node *left;
    Node *right;
    Node *root;
    Node *temp;

    // Create and Enqueue all nodes from the histogram.

    for (int i = 0; i < ALPHABET; i++) {
        // Create each node from the histogram where the symbol is
        // the current index i and the frequency is the actual element
        // associated with that index in the histogram.

        // Check if the node's frequency is greater than 0. If it is less
        // than there is no point in creating a node since it did not
        // appear in the file.

        if (hist[i] > 0) {
            // Create a node if frequency is greater than 0.
            temp = node_create(i, hist[i]);

            // Enqueue the created nodes to the priority queue.
            enqueue(h, temp);
        }
    }

    // Check that the queue is greater than 1.

    while (pq_size(h) > 1) {
        // Dequeue two elements at a time.
        dequeue(h, &left);
        dequeue(h, &right);

        // Then join the two nodes together and enqueue this parent node.
        Node *parent = node_join(left, right);

        enqueue(h, parent);
    }

    // When only one parent remains in the Priority Queue this must be the
    // root of the Huffman tree so return this.
    dequeue(h, &root);

    // Delete priority queue when done in build tree.
    pq_delete(&h);

    // Return the found root.
    return root;
}

// This function populates a code table, building a code for each symbol
// in the Huffman Tree. Since this is a void typed function it should not
// return anything.

void build_codes(Node *root, Code table[static ALPHABET]) {
    // Initialize code c and bit to be used.
    Code c = code_init();
    uint8_t bit;

    // Check if valid root exists. Then check if it is the left or right
    // of the root node. If both of these conditions are met then set
    // the table at the node's symbol equal to code c.
    if (root != NULL) {
        if (!(root->left != NULL && root->right != NULL)) {
            table[root->symbol] = c;
        }

    }

    // Otherwise, push bits 0 and 1, call the function again recursively
    // and pop the bit.

    else {
        code_push_bit(&c, 0);
        build_codes(root->left, table);
        code_pop_bit(&c, &bit);

        code_push_bit(&c, 1);
        build_codes(root->right, table);
        code_pop_bit(&c, &bit);
    }

    // Since this is a void typed function return nothing.
    return;
}

// This function dumps a tree through a post-order traversal of the
// Huffman Tree and writing it to outfile. For each leaf, it should write
// an 'L' while for each interior node it should write an 'I'. 

void dump_tree(int outfile, Node *root) {

    // Create two buffers to be used for writing L or I to outfile.
    char buffer[1];
    char buf[1];

    buffer[0] = 'L';
    buf[0] = 'I';

    // Check if root and dump the left and right node if they are not null.
    // If the left and right node are NULL then it implies that it is a leaf
    // node so write 'L'  and the symbol to the outfile.

    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (!(root->left != NULL && root->right != NULL)) {
            write(outfile, buffer, 1);
            write(outfile, &root->symbol, 1);

        }
        // If none of those conditions were met then it must be an interior
        // node so write 'I' to outfile.

        else {
            write(outfile, buf, 1);
        }
    }
    // Return nothing since this is a void function.
    return;
}

// Reconstructs a Huffman tree given its post-order tree dump stored
// in the tree dump. Since this function is a node pointer it returns a
// pointer to the root node of the constructed tree.

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    // Create the stack with size of Stack.
    Stack *s = stack_create(nbytes);

    // Initialize needed Node pointers for stack.
    Node *left;
    Node *right;
    Node *root;

    // Check every index from 0 to nbytes.
    for (uint16_t i = 0; i < nbytes; i++) {
        // Check if tree dump is at an 'L' or an 'I'.
        // If it is at an L increment once, push and increment again
        // to skip the symbol.
        if (tree_dump[i] == 'L') {
            Node *l = node_create(tree_dump[i + 1], 0);
            stack_push(s, l);
            i = i + 1;
        }

        // If it an I pop twice, create parent node of popped children and
        // then push the parent on to the stack. This should only increment
        // once since the symbol of 'I' was not included in build codes.

        if (tree_dump[i] == 'I') {
            stack_pop(s, &right);
            stack_pop(s, &left);
            Node *parent = node_join(left, right);
            stack_push(s, parent);
        }
    }

    // Finally pop the root and return this.
    stack_pop(s, &root);

    // Delete the stack once the root has been found.
    stack_delete(&s);
    return root;
}

// This function is the destructor for the Huffman tree. Similar to dump
// tree, this function requires a post-order traversal of the tree to free
// the nodes. It should also set the pointer to NULL and since this a void
// type function it should not return anything. 

void delete_tree(Node **root) {
    // Perform a similar post order traversal from tree dump.
    if (root != NULL) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);

        // Delete the nodes at the leafs. Interior nodes becomes leaves
        // when their leaves are deleted first so the other condition
        // does not need to be checked.
        if (!((*root)->left != NULL && (*root)->right != NULL)) {
            node_delete(root);
        }

        else {
            node_delete(root);
        }
    }

    // Delete the main root at the end of the program.
    node_delete(root);

    return;
}
