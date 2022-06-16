/*****************************************************************************
*
* Joel Sojan, jsojan
* 2022 Spring CSE101 PA3
* List.c
* C file for List ADT
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// Note this implementation followed the example provided from  the Queue.c 
// example given on the CSE101 website course examples for a Queue which I 
// followed for my own implementation of building the List and the ADTs needed.
// Furthermore, the pa1 file stated that following the example provided in
// the Queue.c example was permitted which is why my implementation of the
// List is similar to that example.

// Private Node type for List operations.

typedef struct NodeObj* Node;

// Create the Private NodeObj type.

typedef struct NodeObj{
    int data;
    Node next;
    Node prev;
} NodeObj;

// Include needed typedef statement for List implementation.
// This utilizes a private struct.

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors and Destructors

// This function creates a new List object and initializes the next and 
// data fields.

// Returns reference to new Node object and initializes the next and 

Node newNode(int data) {
    Node n = malloc(sizeof(NodeObj));

    if (n != NULL) {
        n->data = data;
        n->next = NULL;
	n->prev = NULL;
        return(n);
    }
    
    // Return n as NULL.
    return(n);
}

// Frees the heap memory pointed to by *np and sets *np to NULL.

void freeNode(Node* np) {
    if (np != NULL && *np != NULL) {
        free(*np);
	*np = NULL;
    }
    return;
}

// Create a new List which works as a bi-directional queue.

List newList(void) {
    List L = malloc(sizeof(ListObj));

    if (L != NULL) {
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length = 0;

	return(L);
    }
    
    // Else, return L as NULL.
    return(L);
}

// Frees all memory used by List pointer and sets *pL to NULL.

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
	while (length(*pL) > 0) {
	    deleteFront(*pL);
	}
        free(*pL);
	*pL = NULL;
    }

    return;
}

// Access functions

// Returns the number of elements in L.

int length(List L) {
    if (L == NULL) {
    	printf("List Error: Called length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}

// Returns the index of the cursor element if defined. Default value is -1.

int index(List L) {
    if (L == NULL) {
        printf("List Error: Called index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->index);
}

// Returns the front element of L. Precondition is length() > 0.

int front(List L) {
    if (L == NULL) {
	printf("List Error: Called front() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
	printf("List Error: Called front() on an empty List\n");
	exit(EXIT_FAILURE);
    }
    return(L->front->data);
}

// Returns the back element of L. Precondition is length() > 0.

int back(List L) {
    if (L == NULL) {
        printf("List Error: Called back() on NULL List refence\n");
	exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
	printf("List Error: Called back() on an empty List\n");
	exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

// Returns the cursor element of L. Precondition is length() > 0 and 
// index() > 0.

int get(List L) {
    if (L == NULL) {
	printf("List Error: Called get() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
	printf("List Error: Called get() on an empty List\n");
	exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
	printf("List Error: Called get() with cursor index less than 0\n");
	exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
	L->index = -1;
    }
    return L->cursor->data;
}

// Returns true if List A and B are in the same state, else return false.

bool equals(List A, List B) {
    bool check = false;
    Node N = NULL;
    Node M = NULL;

    if (A == NULL || B == NULL) {
	printf("List Error: Called equals() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }

    check = ( A->length == B->length);
   
    N = A->front;
    M = B->front;

    while (check && N != NULL) {
	check = (N->data == M->data);
	
	N = N->next;
	M = M->next;
    }

    return check;
}

// Manipulation procedures 

// Resets L to its original empty state.

void clear(List L) {
    if (L == NULL) {
        printf("List error: Called clear() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        return;
    }

    while (length(L) > 0) {
	deleteFront(L);
    }

    return;

}

// Overwrites the cursor element's data with x.
// Preconditions are length() > 0 and index() >= 0.

void set(List L, int x) {
    if (L == NULL) {
        printf("List Error: Called set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: Called set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: Called set() with cursor index less than 0\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;

    return;
}

// If L is non-empty sets cursor under the front element else returns nothing.

void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: Called moveFront() on NULL List refence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        return;
    }

    L->cursor = L->front;

    L->index = 0;

    return;
}

// If L is non-empty sets cursor under the back element else returns nothing.

void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: Called moveBack() on NULL List refence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: Called moveBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    L->cursor = L->back;

    L->index = length(L) - 1;

    return;
}

// If cursor is defined and not at front, move cursor one step toward the
// front of L. If cursor is defined and at front cursor becomes undefined.
// If cursor is undefined do nothing.

void movePrev(List L) {
    if (L == NULL) {
	printf("List Error: Called movePrev() on NULL List reference\n");
	exit(EXIT_FAILURE);
    } 
    if (length(L) <= 0) {
        printf("List Error: Called movePrev() on an empty List\n");
	exit(EXIT_FAILURE);
    }

    // If cursor is defined, check if its at the front.

    if (L->cursor != NULL && L->cursor != L->front) {
        L->cursor = L->cursor->prev;
	L->index -= 1;
	return;
    }
    if (L->cursor != NULL && L->cursor == L->front) {
	L->cursor = NULL;
	L->index = -1;
	return;
    }
    if (L->cursor == NULL) {
	L->index = -1;
	return;
    }
    
    // If cursor is already undefined, do nothing.
    return;
}

// Moves cursor one step toward the back of L if the cursor is defined and not
// at the back. If cursor is defined and at back then cursor becomes undefined.
// If cursor is undefined then do nothing.

void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: Called moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: Called moveNext() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    // If cursor is defined check if its at the back.

    if (L->cursor != NULL && L->cursor != L->back) {
	L->cursor = L->cursor->next;
	L->index += 1;
	return;
    }

    if (L->cursor != NULL && L->cursor == L->back) {
	L->cursor = NULL;
	L->index = -1;
	return;
    }

    if (L->index >= length(L)) {
	L->index = -1;
	return;
    }

    // If cursor is undefined, do nothing.
    return;    
}

// Insert new element into L. If L is non-empty insertion takes place before 
// front element.

void prepend(List L, int x) {
    if (L == NULL) {
	printf("List error: Called prepend() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }
    if (length(L) < 0) {
	printf("List error: Called prepend() on negative empty list\n");
	exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    
    // If List empty set Front and back to new Node.
    if (length(L) == 0) {
	L->front = N;
	L->back = N;
    }
    
    // Prepending the node before the front of the List. Update front
    // to new Node and next should point to the original front Node to fix
    // List.
    else {
	Node M  = L->front;
	L->front = N;
	L->front->next = M;

	// Define previous of this node.
	L->front->next->prev = N;
    }
    if (index(L) != -1) {
	L->index += 1;
    }
    L->length += 1;
    return;
}

// Insert new element into L. If L is non-empty insertion takes place after
// back element.

void append(List L, int x) {
    if (L == NULL) {
        printf("List error: Called append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) < 0) {
        printf("List error: Called append() on negative empty list\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);

    // If List empty set Front and back to new Node.
    if (L->front == NULL && L->back == NULL) {
        L->front = N;
        L->back = N;
    }
    if (L->back != NULL) {
	L->back->next = N;

	// Define previous element
        N->prev = L->back;
        N->next = NULL;
	L->back = N;
    }
    L->length += 1;
    return;
}

// Insert new element before cursor. Preconditions are length() > 0
// and index() >= 0.

void insertBefore(List L, int x) {
    if (L == NULL) {
        printf("List error: Called insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List error: Called insertBefore() on negative empty list\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
	printf("List error: Called insertBefore() with negative index\n");
    }

    Node M = L->cursor;

    Node O = L->cursor->prev;

    if (L->cursor != L->front) {
	Node N = newNode(x);
	L->cursor->prev->next = N;
	L->cursor->prev->next->prev = O;
	L->cursor->prev->next->next = M;
	L->cursor->prev->next->next->prev = N;
	L->length += 1;
	L->index += 1;
    }
    else {
	prepend(L, x);
    }

    return;
}

// Insert new element after cursor. Preconditions are length() > 0 and
// index() >= 0.

void insertAfter(List L, int x) {
    if (L == NULL) {
        printf("List error: Called insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List error: Called insertAfter() on negative empty list\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List error: Called insertAfter() with negative index\n");
    }

    Node N = newNode(x);

    Node M = L->cursor;

    Node O = L->cursor->next;

    if (L->cursor != L->back) {
	L->cursor->next = N;
	L->cursor->next->prev = M;
	L->cursor->next->next = O;
	L->cursor->next->next->prev = N;
    }
    else {
      	L->cursor->next = N;
	L->cursor->next->prev = M;
	L->cursor->next->next = NULL;
	L->back = N;
	
    }
    L->length += 1;

    return;
}

// This function deletes the front element. Precondition is length() > 0.

void deleteFront(List L) {
    Node N = NULL;
    bool check = false;
    if (L == NULL) {
        printf("List error: Called deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List error: Called deleteFront() on negative empty list\n");
        exit(EXIT_FAILURE);
    }

    N = L->front;

    if (length(L) > 1) {
	if (L->front == L->cursor) {
            L->cursor = NULL;
            L->index = -1;
	    check = true;
        }
	if (check == false) {
            L->index -= 1;
        }

	L->front = L->front->next;
	L->front->prev = NULL;
    }
    else {
	L->index = -1;
    	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	
    }

    L->length -= 1;
    freeNode(&N);
    return;
}

// This function deletes the back element. Precondition is length() > 0.

void deleteBack(List L) {
    if (L == NULL) {
        printf("List error: Called deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List error: Called deleteBack() on negative empty list\n");
        exit(EXIT_FAILURE);
    }
    Node M = L->back;

    if (length(L) > 1) {
	if (L->back == L->cursor) {
	    L->cursor = NULL;
	    L->index = -1;
	}
	L->back = L->back->prev;
	L->back->next = NULL;
    }
    else {
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
    }
    L->length -= 1;
    freeNode(&M);

    return;
}

// This function deletes the cursor element making the cursor element
// undefined. Precondition is length() > 0 and index() >= 0.

void delete(List L) {
    if (L == NULL) {
        printf("List error: Called delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List error: Called delete() on negative empty list\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List error: Called delete() with negative index\n");
    }
    
    Node M = L->cursor;

    if (L->cursor != NULL && L->cursor == L->front) {
	deleteFront(L);
	L->cursor = NULL;
	L->index = -1;
    }
    if (L->cursor != NULL && L->cursor == L->back) {
	deleteBack(L);
	L->cursor = NULL;
	L->index = -1;
    }

    if (L->cursor != NULL && (L->cursor != L->front || L->cursor != L->back)) {
	L->cursor->prev->next = L->cursor->next;
	L->cursor->next->prev = L->cursor->prev;

	freeNode(&M);
	L->cursor = NULL;
	L->index = -1;
	L->length -= 1;
    }
    
    return;
}

// Prints to the file pointed to by out, a string representation of L 
// consisting of space seperated sequence of integers, with front on left.

void printList(FILE* out, List L) {
    Node N = NULL;

    if (L == NULL) {
	printf("List Error: called printList() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }

    for (N = L->front; N != NULL; N = N->next) {
	fprintf(out, "%d ", N->data);
    }
    printf("\n");
    return;
}

// Returns a new List which represents the same integer sequence as L.
// The cursor of the new List will be undefined but the state of L will be
// unchanged.

List copyList(List L) {
    if (L == NULL) {
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = NULL;
    
    List O = newList();
    O->cursor = L->cursor;
    O->index = L->index;

    for (N = L->front; N != NULL; N = N->next) {
	append(O, N->data);
    }
    
    return(O);
}
