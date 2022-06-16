#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#include "node.h"
#include "pq.h"

// Create ADT for priority Queue that includes head, tail, capacity and
// items. Items will be used for allocating the nodes to be represented
// in this priority queue while the count variable will be used for tracking
// the number of items currently in the priority queue.

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    uint32_t count;
    Node **items;
};

// This function serves as the constructor for the priority que. This
// function should return a pointer that points to the priority queue.

PriorityQueue *pq_create(uint32_t capacity) {
    // Dynamically allocate space for priority queue.
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    // Pass in the value of capacity to pointer q.
    q->capacity = capacity;

    //Initialize necessary variables to be used in Priority Queue.
    q->head = 0;
    q->tail = capacity + 1;
    q->count = 0;

    // Allocate memory to items.
    q->items = (Node **) calloc(capacity, sizeof(Node *));
    // Return the pointer to the Priority Queue
    return q;
}

// This function serves as the destructor for the priority queue and
// sets the pointer to NULL after freeing such memmory. It is a void typed
// function so it should not return anything.

void pq_delete(PriorityQueue **q) {
    // Free the dynamically allocated memmory to items from q and set items
    // to NULL before freeing q.
    free((*q)->items);
    (*q)->items = NULL;

    // Then, free the memory allocated in q and set q to NULL.
    free(*q);
    *q = NULL;
    return;
}

// The following function returns true if the priority queue is empty
// and false otherwise. As such, this function should return a boolean
// true or false depending on the condition.

bool pq_empty(PriorityQueue *q) {
    // Check if there are no elements in the Priority Queue then return true,
    // else return false.
    if (q->count != 0) {
        return false;
    }
    return true;
}

// The following function returns true if the priority queue is full
// and false otherwise. As such, this function should return a boolean
// true or false depending on the condition.

bool pq_full(PriorityQueue *q) {
    // Check if the number of elements in the priority queue are the same
    // as its capacity then return true, else return false.
    if (q->count != q->capacity) {
        return false;
    }
    return true;
}

// This function returns the size of the priority queue as a uint32_t
// integer.

uint32_t pq_size(PriorityQueue *q) {
    // Return the value stored in the count variable.
    return q->count;
}

// This function enqueues a node into the priority queue. Since it is bool
// type, it should return false if the priority queue is full and true
// otherwise indicating that enqueueing the node was succesful.

// Implementation of insertion sort for priority queue.

bool enqueue(PriorityQueue *q, Node *n) {
    // Return false if Priority Queue is full by default.
    if (q->count == q->capacity) {
        return false;
    }
    // Store node n within the dynamically allocated array of items
    // at index count.
    q->items[q->count] = n;

    // Enqueue a node will be succesful now so increment count.
    q->count = q->count + 1;

    // Perform insertion sort at this point.The array will be sorted in 
    // increasing order of node frequency so as to dequeue from the head 
    // where the lowest frequency nodes should be.

    // Start a while loop that iterates until the end of the current queue.
    for (uint32_t i = 1; i < q->count; i++) {
        // Set another variable j equal to i.
        uint32_t j = i;
        // Create a temp node pointer that stores the current value at index i.
        Node *temp = q->items[i];
        // Create another variable for comparing frequencies since
        // this should sort the array in ascending order of frequency.
        uint32_t freq = q->items[i]->frequency;

        // This while loop checks that j is not less than 0 and checks if
        // the current nodes frequency is less than the previos nodes
        // frequency.
        while (j > 0 && freq < q->items[j - 1]->frequency) {
            // If the current node's frequency is less than the previous
            // index, move the current node back one as done in insertion
            // sort and decrement j.

            q->items[j] = q->items[j - 1];

            // Decrement j in this case.
            j = j - 1;
        }
        // After the while loop ends, set the node at index j equal to the
        // temp pointer that was set at the beginning of the for loop.
        q->items[j] = temp;
    }

    // Return true upon succesful enqueue of a node in priority queue.
    return true;
}

// This function dequeues a node from the priority queue if is not empty.
// Since this is a boolean function it returns true if dequeue was succeful.

bool dequeue(PriorityQueue *q, Node **n) {
    // Declare an index i variable to be used when dequeueing next node.
    uint32_t i = 0;

    // Check that the priority queue isn't empty before dequeue and return
    // false otherwise.
    if (q->count == 0) {
        return false;
    }

    // Now that dequeue is succesful, remove the first element of the array.
    // The node double pointer n must return the node of highest priority
    // first and then remove it.

    *n = q->items[q->head];

    // Since the head will always be removed at index 0 shift the elements
    // of the queue back 1 where index i is now index i+1 until the count of
    // the queue.
    while (i < q->count) {
        q->items[i] = q->items[i + 1];
        i = i + 1;
    }

    // Decrement count at this point to avoid segfaults.
    q->count = q->count - 1;

    return true;
}

// This is a debug function that inputs checks if the priority queue is
// created and deleted correctly. In addition, it should check that the
// enqueue and dequeue of nodes work apropriately. Since this function is
// void type it should not return anything.

void pq_print(PriorityQueue *q) {
    printf("This is the priority queue after insertion sort:\n");
    for (uint32_t x = 0; x < q->count; x++) {
        printf("Element %u\n", x);
        node_print(q->items[x]);
    }
    return;
}
