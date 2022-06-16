/******************************************************************************
*
* Joel Sojan, jsojan
* CSE101 Spring 2022 PA6
* List.cpp
* This is the main C++ file that contains the implementation of the List ADT.
******************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

// Private Constructor --------------------------------------------------------

// Node Constructor

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Create a new List in the empty state.

List::List() {
    frontDummy = new Node(-1);
    backDummy = new Node(0);

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor.

List::List(const List& L){
    // Make this an empty List
    frontDummy = new Node(-1);
    backDummy = new Node(0);

    
    beforeCursor = frontDummy;
    afterCursor = backDummy;

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    pos_cursor = 0;
    num_elements = 0;

    // Load elements of L into this List.
    Node *N = L.frontDummy->next;
    while (N != L.backDummy) {
	insertBefore(N->data);
	N = N->next;
    }

    moveFront();
}

// Destructor
List::~List(){
    moveBack();
    while(num_elements > 0) {
        eraseBefore();
    }
 
    Node* N = frontDummy;
    Node* M = backDummy;
    
    // Free the front and back dummy nodes for destructor.
    delete N;
    delete M;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return(num_elements);
}

// front()
// Returns the front element of this List.
// precondition: length() > 0.

ListElement List::front() const{
    if (num_elements <= 0) {
	throw std::length_error("List: front() empty List.");
    }
    return(frontDummy->next->data);
}

// back()
// Returns the back element of this List.
// precondiiton: length() > 0.

ListElement List::back() const{
    if (num_elements <= 0) {
	throw std::length_error("List: back() empty List.");
    }
    return(backDummy->prev->data);
}

// position()
// Returns the position of the cursor in the List.
// Returns the position of cursor in this List: 0 <= position() <= length().

int List::position() const{
    if (pos_cursor > num_elements || pos_cursor < 0) {
	throw std::range_error("List: position(); cursor position greater than number of elements or less than 0");

    }
    return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// precondition: position() < length().

ListElement List::peekNext() const{
    if (pos_cursor >= num_elements) {
	throw std::range_error("List: peekNext(); cursor position greater than number of elements or less than 0.\n");

    }
    return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// precondition: position() > 0.

ListElement List::peekPrev() const{
    if (pos_cursor <= 0) {
	throw std::range_error("List: peekPrev(); cursor position less than or equal to 0.");


    }
    return(beforeCursor->data);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.

void List::clear() {
    moveBack();
    while(num_elements > 0) {
        eraseBefore();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.

void List::moveFront() {
    pos_cursor = 0;

    // Set before cursor to Front Dummy and after cursor to Front Dummy next.
    
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.

void List::moveBack() {
    pos_cursor = num_elements;

    // Set After cursor to back Dummy and before cursor to back Dummy prev.
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// Precondition is position() < length().

ListElement List::moveNext() {
    
    if (pos_cursor >= num_elements) {
	throw std::range_error("List: moveNext(); cursor position greater than number of elements.");

    }
    
    // Store the afterCursor element.
    Node *N = afterCursor;
    
    // MoveNext moves the cursor so the before becomes the afterCursor.
    // Likewise the afterCursor points to its next node.
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;

    pos_cursor += 1;
    
    // Return the List element that was passed over.
    return(N->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. Precondition is position() > 0.

ListElement List::movePrev() {

    if (pos_cursor <= 0) {
	throw std::range_error("List: movePrev(): cursor position less than or equal to 0.");

    }

    // Store the beforeCursor element.
    Node *M = beforeCursor;
    
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev; 

    pos_cursor -= 1;
    
    // Return the List element that was passed over.
    return(M->data);
}

// insertAfter()
// Inserts x after cursor.

void List::insertAfter(ListElement x) {
    
    // Create the new Node to be inserted.
    Node* N = new Node(x);

    // Set the beforeCursor next to N and N's previous to beforeCursor.
    beforeCursor->next = N;
    N->prev = beforeCursor;

    // Set the afterCursor prev to N and N's next to afterCUrsor.

    afterCursor->prev = N;
    N->next = afterCursor;

    // Set the afterCursor to N.
    afterCursor = N;
    
    // Increment the number of elements.
    num_elements += 1;

}

// insertBefore()
// Inserts x before cursor.

void List::insertBefore(ListElement x) {
    
    // Create the new Node to be inserted.
    Node* N = new Node(x);
    
    // Set the beforeCursor next to N and N's previous to beforeCursor.
    beforeCursor->next = N;
    N->prev = beforeCursor;
    
    // Set the afterCursor prev to N and N's next to afterCursor.
    afterCursor->prev = N;
    N->next = afterCursor;
    
    // Set the beforeCursor equals to N.
    beforeCursor = N;
    
    // Increment the cursor and the num of elements by 1.
    pos_cursor += 1;
    num_elements += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// precondition: position() < length()

void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements) {
	throw std::range_error("List: setAfter(): cursor position greater than or equal to length.");

    }

    // Set the afterCursor data to x.
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// precondition is position() > 0.

void List::setBefore(ListElement x) {
    if (pos_cursor <= 0) {
	throw std::range_error("List: setBefore(); cursor position less than or equal to 0.");

    }

    // Set the beforeCursor data to x.
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// precondition is position() < length().

void List::eraseAfter() {
    if (pos_cursor >= num_elements) {
	throw std::range_error("List: eraseAfter(); cursor position greater than or equal to length.");

    }

    Node* N = afterCursor->next;

    // Link the current before cursor to the next of afterCursor.
    beforeCursor->next = N;
    N->prev = beforeCursor;

    // Decrement the number of elements.
    num_elements -= 1;

    // Free the memory allocated to the afterCursor.
    delete(afterCursor);

    afterCursor = N;
}

// eraseBefore()
// Deletes element before cursor.
// precondition is position() > 0.

void List::eraseBefore() {
    if (pos_cursor <= 0) {
	throw std::range_error("List: setBefore(); cursor position less than orequal to 0.");

    }

    Node* N = beforeCursor->prev;

    // Link the current afterCursor to the previous of beforeCursor.
    afterCursor->prev = N;
    N->next = afterCursor;

    // Decrement the number of elements and position of cursor.
    num_elements -= 1;
    pos_cursor -= 1;

    // Free the memory allocated to the beforeCursor.
    delete(beforeCursor);
    
    beforeCursor = N;
}

// Other Functions ------------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in the
// direction front-to-back) for the first occurence of element x. If x is found
// places the cursor immediately after the found element, then returns the 
// final cursor position. If x is not found, places the cursor at position
// length(), and returns -1.

int List::findNext(ListElement x) {
    // Loop through the remaining elements.
    while (pos_cursor < num_elements) {
        // check if the after cursor data equals x.
        if (afterCursor->data == x) {
	    // Call moveNext and return the cursor position since 
	    // x was found.
            moveNext();
	    return(pos_cursor);
	}
	// moveNext if the x was not found.
	moveNext();
    }

    // If x is not found place cursor at position length() by calling moveBack.    // Then returns -1.

    moveBack();
    return(-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurence of element x. If x
// is found, places the cursor immediately before the found element, then 
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.

int List::findPrev(ListElement x) {
    // Loop through the remaining elements.
    
    while (pos_cursor > 0) {
	// Check if beforeCursor data equals x.

        if (beforeCursor->data == x) {
            // Move the cursor before the found element x and return
	    // this cursor's position.
	    movePrev();
	    return(pos_cursor);
	}
        
	// Regardless of the iteration movePrev().
	movePrev();
   
    }

    // If x is not found, places the cursor at position 0 and returns -1.
    moveFront();
    return(-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurance of each element, and removing all other occurances. The cursor is
// not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.

// Note TA Andrew Gavgavian and TA Aaron helped me fix my cleanup function
// during their section on Friday 5/6/22 from 9 am to 11 am. They 
// specifically  helped with the cleanup cursor position function since I was 
// struggling to fix this function's cursor position after cleanup was called 
// until they both helped me fix my afterCursor and beforeCursor. Thus I am
// citing them for fixing my cleanup code so that it works correctly without
// segfaulting.

void List::cleanup() {
    // Create a Node that represents the frontDummy node.
    Node* N = nullptr;
    
    // Create cursor and check variables to be used in this program.
    int cursor = 0;
    int check;

    // Create a diff counter variable which only increments
    // for repeats less than the cursor position.
    int diff = 0;
    
    // Define an increment function to be used for simplicity.
    int inc = 1;

    // While loop for looping through the whole list.
    for (N = frontDummy->next; N != backDummy; N = N->next, cursor += inc) {
       
       // Create a node temp and a counter.
       // Set the check equal to the cursor.
       Node* temp = N;
       
       // Create an integer which stores the temp's data which is what
       // the current iteration is looking for repeats of.

       int value = temp->data;

       // Counter will be the looping variable for checking if there
       // are any repeat elements in the current iteration of the loop.
       Node* counter = temp;
       
       check = cursor;

       // While loop for looping through the counter until it 
       // equals the backDummy.

       while (check != num_elements) {
           counter = counter->next;
           
	   // Create a count to store the counter->data every iteration.
	   int count = counter->data;

	   // Increment the current cursor (check) by 1 since counter
	   // needs to move next.

	   check += inc;

	   // Check if the current counter is equal to temp.
	   if (count == value) {
	       // Erase After logic is used here.
	       Node* M = counter->next;
	       Node* L = counter->prev;
               
	       L->next = M;
               M->prev = L;
               
	       // check if the current position is less than the cursor's 
	       // position then increment the diff counter variable.

	       if (check < pos_cursor + 1) {
	           diff += inc;
	       }
               
	       // Check if the counter variable is equal to the beforeCursor.
	       // Then set the after and beforeCursor accordingly for
	       // the cleanup before and afterCursor functions to be defined
	       // correctly.
	       
	       if (counter == beforeCursor && counter != afterCursor) {
		   Node *X = backDummy;

                   afterCursor = X;
		   beforeCursor = X->prev;
	       }

	       // Check if the counter variable is equal to the afterCursor.
	       // Then set the before and afterCursor accordingly for the 
	       // cleanup before afterCursor functions to be defined
	       // correctly.

	       if (counter == afterCursor && counter != beforeCursor) {
                   Node *Y = frontDummy;

                   beforeCursor = Y;
		   afterCursor = Y->next;
	       }

               // Decrease num of elements and delete the actual counter value.               // Then set the counter to M.

	       num_elements -= inc;
               delete(counter);	
	       
	       // Set the counter equal to M which was set at the
	       // beginning of the list.
	       counter = M;       
	   }
       }
    }

    // Subtract the difference from pos_cursor.

    pos_cursor -= diff; 
}


// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at position 0.

List List::concat(const List& L) const {
    // Create new List to be returned.
    List C;
    
    // Node N will be the front of this List and Node M will be 
    // the front of the List Q.
    Node* N = this->frontDummy->next;
    Node* M = (L.frontDummy)->next;
    
    // Create a while loop for looping through the elements of this List.
    while (N != this->backDummy) {
        C.insertAfter(N->data);
	C.moveNext();
        N = N->next;
    }
    
    // Create a while loop for looping through the elements of the List L.
    while (M != L.backDummy) {
	C.insertAfter(M->data);
	C.moveNext();
        M = M->next;
    }
    
    // Move Front on List C.
    C.moveFront();

    // Return the list C.
    return(C);
}

// to_string()
// Returns a string representation of the List consisting of a comma
// seperated sequence of elements, surrounded by parantheses.

std::string List::to_string() const {
    // Create Node N will be set to nullptr;
    Node* N = nullptr;
    std::string s = "(";
    
    // Create a for loop for printing the string List.
    for(N = frontDummy->next; N != backDummy; N = N->next) {
	if (N == backDummy->prev) {
	    s += std::to_string(N->data);
	    break;
	}
	s += std::to_string(N->data) + ", ";
    }
    
    // Add closing paranthesis 
    s += ")\n";

    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.

bool List::equals(const List&R) const {
    // Create a boolean equals function and set two Nodes N and M
    // to nullptr by default.
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;


    // Define the eq boolean by checking if the num of elements of both
    // Lists are equal.
    eq = (this->num_elements == R.num_elements);
    
    // Set both Nodes to the front of their respective List.
    N = this->frontDummy->next;
    M = (R.frontDummy)->next;


    // If eq returns true and N is not the backDummy
    // then loop until either eq is false or N becomes backDummy.
    while (eq && N != backDummy) {
        eq = (N->data == M->data);
	N = N->next;
	M = M->next;
    }
    
    // Return eq value whether its true or false.
    return eq;
}

// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.

std::ostream& operator<< ( std::ostream& stream, const List& L ) {
    // Return the result.
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.

bool operator== (const List& A, const List& B) {
    // Return the result.
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.

List& List::operator=( const List& L ) {
    if (this != &L) {
        // Creating  a copy of Q.
	List temp = L;

	// Swap the copy's fields with fields of this.
        std::swap(frontDummy, (temp.frontDummy));
	std::swap(backDummy, (temp.backDummy));
        std::swap(beforeCursor, temp.beforeCursor);
	std::swap(afterCursor, temp.afterCursor);
	std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }

    // Return this with the new data and the copy (if it exits)
    // is deleted upon return.
    return *this;
}


