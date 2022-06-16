//-----------------------------------------------------------------------------
//
// Joel Sojan, jsojan
// CSE101 Spring 2022 PA6
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=25;
   List A, B, C, D;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(26-i);
      C.insertBefore(i);
      D.insertBefore(26-i);
   }
   
   // Start printing out all the Lists together.
   cout << endl;

   // Print out the position, length, front and back of lists A, B, C, and D
   // in this case.

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "A.length() = " << A.length() << endl;
   cout << "A.front() = " << A.front() << endl;
   cout << "A.back() = " << A.back() << endl;

   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "B.length() = " << B.length() << endl;
   cout << "B.front() = " << B.front() << endl;
   cout << "B.back() = " << B.back() << endl;

   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "C.length() = " << C.length() << endl;
   cout << "C.front() = " << C.front() << endl;
   cout << "C.back() = " << C.back() << endl;

   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << "D.length() = " << D.length() << endl;
   cout << "D.front() = " << D.front() << endl;
   cout << "D.back() = " << D.back() << endl;
   cout << endl;

   // Call moveBack and moveFront on all the Lists.

   A.moveBack();
   cout << "A.peekPrev() = " << A.peekPrev() << endl;
   
   B.moveBack();
   cout << "B.peekPrev() = " << B.peekPrev() << endl;
   
   C.moveFront();
   cout << "C.peekNext() = " << C.peekNext() << endl;

   D.moveFront();
   cout << "D.peekNext() = " << D.peekNext() << endl;
   
   // Clear C and copy into A.
   C.clear();
   C = A;

   if (A == C) {
	cout << "List C is now equal to List A." << endl;
   }

   cout << "C" << endl;
   cout << C << endl;

   cout << "Modifying C to use insertBefore and insertAfter." << endl;

   C.moveFront();

   int length = C.length();

   // Check insertBefore and insertAfter functions work as intended.

   for (int x = 0; x < length; x++){
	if (x % 2 == 0) {
	    C.insertBefore(x);
	}
 
	if (x % 3 == 0) {
            C.insertAfter(x);
	}
   }

   cout << endl;

   cout << "C.moveNext()" << C.moveNext() << endl;

   cout << "This is the new C List." << endl;
   
   cout << C << endl;

   cout << endl;

   C.moveFront();

   // Check that eraseBefore and erase After work by removing the newly
   // inserted elements from C.
   
   int size = C.length();

   // Check EraseAfter function works.
   
   for (int x = 0; x < size; x++) {

       if (x % 2 == 0) {
           C.eraseAfter();
       }

   }
   
   C.moveBack();

   int sizeo = C.length();

   // Check EraseBefore function works.
   
   for (int x = 0; x < sizeo; x++) {
       if (x % 3 == 0) {
           C.eraseBefore();
       }   
   }
  

   cout << "This is the new C list after eraseAfter." << endl;
   cout << C << endl;

   // Check the concat and cleanup functions work as intended.
    
   cout << endl;

   List E = C.concat(A);

   cout << "C.concat(A) = " << E << endl;
   cout << "C.concat(A) = " << E.position() << endl;

   cout << endl;

   cout << "Call cleanup on List C" << endl;

   C.cleanup();

   cout << "C.cleanup() = " << endl;
   cout << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << endl;

   // Expiriment with List D and B.
   
   cout << "D" << endl;
   cout << D << endl;
   cout << "D.position" << endl;
   cout << D.position() << endl;

   cout << "D.findNext(11)" << D.findNext(11) << endl;

   cout << "D.findPrev(21)" << D.findPrev(21) << endl;

   if (A == D) {
       cout << "List A and List D are equal as expected in this case." << endl;
   }

   // Tests to check equals and setBefore and setAfter function works 
   // for functionality of this program.

   cout << "This is D before setBefore and setAfter were called." << endl;
   cout << D << endl;
   
   D.movePrev();
   D.setBefore(29);
   D.setAfter(58);

   D.moveFront();
   D.setAfter(100);
   D.moveBack();
   D.setBefore(101);

   // Now that D has been altered using the setBefore and setAfter functions
   // then calling the equals function on A and D should return false since
   // they are no longer the same integer sequence.
   
   if (A == D) {
       cout << "This should not be printed as A does not equal D." << endl;
   }

   cout << "In this case List A does not equal List D as expected." << endl;

   // Check to_string List printing function if List is empty when calling
   // the clear function.
   
   cout << "This is D before clear function was called." << endl;
   cout << D << endl;

   D.clear();

   cout << "This is D after clear function was called." << endl;
   cout << D << endl;
   
   // Return 0 and end program at this point.
   return 0;
}


