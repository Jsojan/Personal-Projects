/******************************************************************************
* Joel Sojan, jsojan
* 
* List.h
* Header file for List ADT
******************************************************************************/

#pragma once

#include <stdbool.h>
#include <stdint.h>

// List ADT creation and exported types
typedef int ListElement;
typedef struct ListObj* List;

// Constructors-Destructors

// Creates and returns a new empty List.
List newList(void);

// Frees all heap memory associated with *pL and sets *pL to NULL.
void freeList(List* pL); 

// Access functions

// Returns the number of elements in n.
int length(List L);

// Returns the index of cursor elements else -1.
int index(List L);

// Returns the front element of L. Pre: length() > 0.
int front(List L); 

// Returns the back element of L. Pre: length() > 0.
int back(List L);

// Returns cursor element of L. Pre: length() > 0 and index() > 0.
int get(List L);

// Returns true if List A and List B are in the same state.
bool equals(List A, List B);

// Manipulation procedures

// Reset L to the empty state.
void clear(List L);

// Overwrite cursor element data with x, Pre: length() > 0, index() >= 0.
void set(List L, int x);

// Sets cursor under the first element if List not empty else does nothing.
void moveFront(List L);

// Sets cursor under back element if List not empty else does nothing.
void moveBack(List L);

// Move cursor one step towards Front if cursor is defined and not already
// at Front. If cursor is defined and already at front the cursor becomes
// undefined and the function should do nothing if cursor is undefined.

void movePrev(List L);

// Move cursor one step towards Back of L if cursor is defined and not already
// at the back of L. If cursor is defined and already at the back the cursor becomes undefined and the function should do nothing if cursor is undefined.
void moveNext(List L);

// Insert new element into L. If L is non empty, insertion occurs before front
// element.
void prepend(List L, int x);

// Insert new element into L. If L is non empty, insertion occurs after back
// element.
void append(List L, int x);

// Insert new element before cursor. Pre: length() > 0, index() >= 0.
void insertBefore(List L, int x);

// Insert new element after cursor. Pre: length() > 0, index() >= 0.
void insertAfter(List L, int x);

// Delete the front element. Pre: length() > 0.
void deleteFront(List L);

// Delete back element. Pre: length() > 0.
void deleteBack(List L);

// Delete cursor element, making cursor undefined. Pre: length() > 0,
// index() >= 0.

void delete(List L);

// Other operations

// Prints to the file pointed by out as a string representation of L consisting
// of a space seperated sequence of integers with front on left.

void printList(FILE *out, List L);

// Returns a new List representing the same integer sequence as L. The cursor 
// in the new List is undefined, regardless of the state of cursor in L. The 
// state of L is unchanged.

List copyList(List L);
