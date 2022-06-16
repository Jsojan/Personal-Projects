//-----------------------------------------------------------------------------//
// Joel Sojan, jsojan
// CSE101 Spring 2022 PA6
//
// BigInteger.cpp
// C file for implementation of BigInteger ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "BigInteger.h"

// define global constants base and power.

const int power = 9;

const long base  = 1000000000;

// Class Constructors and Destructors.

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum = 0, digits = ().

BigInteger::BigInteger() {
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least oone) base 10 digit.
// {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} and an optional sign {+,-} prefix.

BigInteger::BigInteger(std::string s) {
    // check if string s is empty.
    if (s.length() == 0) {
	throw std::invalid_argument("BigInteger: Constructor: empty string");		
    }

    if (s[0] == '-' && s.length() == 1) {
	throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    if (s[0] == '+' && s.length() == 1) {
	throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    // Set default signum to 1 if there is no sign given.
    signum = 1;

    // Check the first character and replace it with a 0 if its a sign.
    if (s[0] == '-') {
        signum = -1;

        s.erase(0, 1);
    }

    if (s[0] == '+') {
        signum = 1;

        s.erase(0, 1);
    }


    // Check if the string is non metric.
    
    for (char const &c : s) {
	// if First digit is a plus or minus sign skip it.

	if (isdigit(c) == 0) {
	    throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}
    }
    
    // Convert the string to a BigInteger at this point.

    int start = 0;
    int end = s.length() - 1;
    int index = s.length() - 1;
    long num = 0;
 
    while (index >= 0) {
	// change the current index value.
        index  = (end - power) + 1;
	if (end < power) {
	    start = 0;
            
	    if (end == 0) {
	        std::string r = s.substr(start, 1);
		num = std::stol(r, nullptr);
                digits.insertAfter(num);
	    }

	    else {
		std::string r = s.substr(start, end+1);
		num = std::stol(r, nullptr);
                digits.insertAfter(num);
	    }

	    break;
	    
	}

	// Normal case for when end is greater than power.

	start = index;
	std::string r  = s.substr(start, power);
	num = std::stol(r, nullptr);
	digits.insertAfter(num);
	end = index - 1;
    }

    // Now remove leading zeros.

    digits.moveFront();

    // For loop that continues the loop until there is either a non zero
    // front element or length is 0.

    while (digits.length() > 0) {
	if (digits.peekNext() != 0) {
	    break;
	}

	digits.moveNext();
	digits.eraseBefore();
    }

    // If input is all zeroes then sign needs to change to 0 at the end.

    if (digits.length() == 0) {
	signum = 0;
    }
}

// BigInteger()
// Constructor that creates a copy of N.

BigInteger::BigInteger(const BigInteger& N) {
    this->digits = N.digits;
    this->signum = N.signum;
}

// Access functions ----------------------------------------------------------

// sign()
// Returns -1, 1, 0 or according to whether this BigInteger is positive, 
// negative or 0, respectively.

int BigInteger::sign() const {
    return (signum);
}

// compare()
// Returns -1, 1, or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.

int BigInteger::compare(const BigInteger& N) const {
    // Create a copy of the digits.
    List temp = this->digits;
    List var = N.digits;

    // check the signs of both lists as initial comparison.

    if (this->signum < N.signum) {
        return -1;
    }

    if (this->signum > N.signum) {
	return 1;
    }

    // Check the length of both lists if both signs are equal.

    if (temp.length() < var.length()) {
	return -1;
    }

    if (temp.length() > var.length()) {
	return 1;
    }

    // moveFront() on both lists.
    temp.moveFront();
    var.moveFront();

    // Now check the equals condition is true as well.

    while (temp.position() < temp.length()) {
	// Check if the current Nodes data is not equal to 
	// current Node's data in List N.
	
        if (temp.peekNext() != var.peekNext()) {

	    // If they're not equal check which value is larger and return
	    // the correct value according to which node is larger in this
	    // or N list.

            if (temp.peekNext() < var.peekNext()) {
		return -1;
	    }

	    else {
		return 1;
	    }
	}
        
	// Call moveNext on both temp and var list for every iteration 
	// of the list.
	
	temp.moveNext();
	var.moveNext();
    }
    
    // Return 0 in this case since it must be equal at this point.
    return 0;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.

void BigInteger::makeZero() { 
    // Clear the List stored in digits and set signum back to 0.
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger <--> negative.

void BigInteger::negate() {
    // check if the sign is zero. If its zero then return since nothing can
    // be performed.

    if (signum == 0) {
	// Return since no operation can be performed.
	return;
    }

    // Condiiton if signum is positive then return signum as negative.

    if (signum == 1) {
	// Change the signum and return.
	signum = -1;
	return;
    }

    if (signum == -1) {
	// Change the signum and return.
	signum = 1;
	return;
    }
    
    // Return if signum is not accessed somehow.
    return;

}

// BigInteger Arithmetic operations -------------------------------------------

// Create helper functions to be used for sum, sub and mult.

// negateList()
// Changes the sign of each integer in List L. Used by sub().

void negateList(List& L) {
    // move Front on List L.
    L.moveFront();
    
    // Create a while loop that loops through the whole list starting
    // from position 0 until n-1.
    while (L.position() < L.length()) {
	// Overwrite the afterCursor and moveNext.
	long result = L.peekNext() * -1;
	L.setAfter(result);
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub()

void sumList(List& S, List A, List B, int sgn) {
    // Create a result variable to be used here.
    long result;
    // Move Front on both Lists A and B.
    A.moveBack();
    B.moveBack();

    // Define the needed List Element variables.
    ListElement a;
    ListElement b;
    
    // Initial loop to loop through lists A and B until shorter List ends.
    while (A.position() > 0 && B.position() > 0) {
        // If position of B reached the end of B.
	a = A.peekPrev();
	b = B.peekPrev();

	result = a + (sgn * b);
	S.insertAfter(result);
	// S.moveNext();

        A.movePrev();
	B.movePrev();
    }
    
    // While loop for if list B is finished.
    while (B.position() == 0 && A.position() > 0) {
	a = A.peekPrev();
	result = a;
	S.insertAfter(result);
	// S.moveNext();

	A.movePrev();
    }

    // While loop for if List A is finished.

    while (A.position() == 0 && B.position() > 0) {
	b = B.peekPrev();
	result = sgn * b;
	S.insertAfter(result);
	// S.moveNext();

	B.movePrev();
    }

    // Move Front on List S.
    S.moveFront();
}

// normalizeList()
// Performs carries from righ to left (least to most significant digits), then
// returns the sign of the resulting integer. Used by add(), sub() and
// mult().

int normalizeList(List& L) {
    // Create needed variables.
    ListElement n;
    int carry = 0;
    int borrow = 0;
    
    // Start from the back of List L.
    L.moveBack();
    
    // While loop that iterates over the List L from back to front.
    while (L.position() > 0) {
	// Obtain previous value.
	n = L.peekPrev();
        
	// Increment the value of carry and borrow before
	// performing operations on carry and borrow 
	// if they are not 0.
	
	n += carry;
	n -= borrow;

	carry = 0;
	borrow = 0;
        
	// If n is greater than or equal to base then 
	// calculate new carry and set n based on n - carry times base.
	if ( n >= base) {
	     carry = (n / base);
	     n = n - (carry * base);
	    
	}

	// If n is less than 0 then calculate the borrow 
	// and return the apropriate value since it is negative.

	if (n < 0) {
            n = n * -1;
	    borrow = (n / base) + 1;
	    n = n * -1;
	    n = n + (borrow * base);
	}

	// Call setBefore() to set the value of n
	// and movePrev on List L at this point.

	L.setBefore(n);
	L.movePrev();
    }

    // Check if carry is non zero and insert it at the front of the list
    // if its non-zero.
    if (carry != 0) {
	L.moveFront();
	L.insertAfter(carry);
    }
    
    // Check if borrow is non zero and insert it at the front of the list
    // if its non-zero.
    if (borrow != 0) {
	L.moveFront();
	L.insertAfter(-1 * borrow);
    }
    
    // Check if front is positive then return 1.
    if (L.front() > 0 ) {
	return 1;
    }
    
    // Check if front is negative then return 1.
    if (L.front() < 0) {
	return -1;
    }
    
    // Otherwise return 0 in this case.
    return 0;

}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().

void shiftList(List& L, int p) {
    // Move back on List L.
    L.moveBack();
    
    // Loop through the List L p times.
    for (int x = 0; x < p; x++) {
	// Insert a 0 before the end of the List.
        L.insertBefore(0); 
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().

void scalarMultList(List& L, ListElement m) {
    // move Front on List L.
    L.moveFront();

    // Create a while loop that loops through the whole list starting
    // from position 0 until n-1.
    while (L.position() < L.length()) {
        long result = L.peekNext() * m;
	L.setAfter(result);
	L.moveNext();
    }
}

// add()
// Returns a BigInteger representing the sum of this and N.

BigInteger BigInteger::add(const BigInteger& N) const{
    // Create BigInteger C to be returned and create
    // a copy of BigInteger this and N since they are constants.
    BigInteger C;
    BigInteger temp = *this;
    BigInteger var = N;
    List result;

    // Check first case if both this and N have the same sign.

    if (this->signum == N.signum) {
	// Call sumList and normalize the summed list.
	// Then store the result into C.digits and the signum
	// is equal to this and N so set that as well.
	
	sumList(result, this->digits, N.digits, 1);
	normalizeList(result);
	if (result.front() < 0) {
	    negateList(result);
	    normalizeList(result);
            if (result.front() == 0) {
		result.moveFront();
		result.eraseAfter();
	    }
	}
	C.digits = result;
	C.signum  = this->signum;
    }

    else {
	
	// Otherwise the signs are different and they need to be considered.
	// Call sumList without normalize in this case.
	sumList(result, this->digits, N.digits, -1);
	normalizeList(result);
	if (result.front() < 0) {
	    negateList(result);
	    normalizeList(result);
	    if (result.front() == 0) {
		result.moveFront();
		result.eraseAfter();
	    }
	}
	C.digits = result;

	// Create a helper boolean variable so as to not overide C's sign.
	bool check = true;
        
	// Negate var to be used in the comparison check.
	var.negate();
        
	// If this < N then C's signum is equal to N's signum.
	if (temp.compare(var) == -1) {
	    if (check) {
		check = false;
	    }
	    C.signum = N.signum;
	}
	
	// If this > N then C's signum is equal to this signum.
	if (temp.compare(var) == 1) {
	    if (check) {
		check = false;
	    }
	    C.signum = this->signum;
	}
        
	// If this and N are equal and have different signs then
	// signum must be 0 in this case.
	if (temp.compare(var) == 0) {
	    C.signum = 0;
	}
    }
    
    // Return C in this case.
    return C;
}

// sub()
// Returns a BigInteger representing the difference of this and N.

BigInteger BigInteger::sub(const BigInteger& N) const{
    // Create BigInteger C and copies of this and N.
    BigInteger C;
    List check;
    BigInteger temp = *this;
    BigInteger var = N;
    
    // Negate N list and call A function since
    // A - B = A + (-B)

    var.negate();
    C = temp.add(var);

    check = C.digits;

    if (check.front() == 0) {
	check.moveFront();
	check.eraseAfter();
    }

    C.digits = check;
    
    // Return the result
    return C;   
}

// mult()
// Returns a BigInteger representing the product of this and N.

BigInteger BigInteger::mult(const BigInteger& N) const {
    // Create much needed variables here.
    BigInteger C;
    BigInteger temp = *this;
    List var = N.digits;
    BigInteger varo = N;
    int counter = 0;
    
    // Check if either list is empty or 0. If they are return 
    // a BigInteger of 0 and set its signum to 0.
    if (this->signum == 0 || N.signum  == 0) {
	C.signum = 0;
	return C;
    }
    
    // MoveBack on the second List.
    var.moveBack();
    
    // While loop that iterates over the length of the second List.
    while (var.position() > 0) {
	// Call scalarMult on copy of this  List with the scalar
	// being the current digit of the second List. Then
	// normalize the result and return it.
	
        scalarMultList(temp.digits, var.peekPrev());
        normalizeList(temp.digits);
        
	// Shift the List accordingly using shiftList function 
	// if counter is non zero.
	if (counter != 0) {
	    shiftList(temp.digits, counter);
	}
        
	// Then add the result into BigInteger C.
	C = C.add(temp); 
        
	// Set the C only if first iteration of the Loop.
	// Otherwise all recurring iterations follow with same sign.
	
	if (counter == 0) {
	    C.signum = temp.signum;
	}
	
	// Reset the temp List to that of this since scalarMult
	// and normalize directly modify the List it passes in.
	
	temp.digits = this->digits;
        
	// Increment counter and movePrevious in the loop.
	counter += 1;
	var.movePrev();
    }
    
    // This is a following check to assign the correct sign to C
    // depending on the two input BigIntegers.

    // If this and N have same sign.

    if (this->signum == N.signum) {
	// Set the C.signum to 1 if both signs are the same.
	// This is because + * + = + and - * - = +.
	C.signum = 1;
	return C;
    }

    // If this and N have different signs.

    if (this->signum != N.signum) {
	// Set the C.signum to -1 if both signs are different
	// since - * + = - and + * - = -.
	C.signum = -1;
	return C;
    }
    
    // Return C as a failsafe.
    return C;
}

// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string will
// begin with a negative sign '-'. If this BigInteger is zero, the returned 
// string will consist of the character '0' only.

std::string BigInteger::to_string() {
    // Create an empty string to be used.
    std::string s = "";
    std::string so = "";
    std::string zer = "";
    
    // If the BigInteger sign is 0 then the string should return 0.
    if (signum == 0) {
        s = "0\n";
	return s;
    }
    
    // Create a List copy of this digits to iterate the cursor.
    List temp = this->digits;
    
    // If this BigInteger is negative then its sign is negative and it needs
    // to have a "-" in the front of the digits.
    if (signum == -1) {
	temp.moveFront();
	s = "-";
	
	// Create while loop to add digits.
	while (temp.position() < temp.length()) {
	    long value = temp.peekNext();
	    if (value < 0) {
		value = value * -1;
	    }
            so = std::to_string(value);

            // Check the length and position is not front of the list.
            if (so.length() < power && temp.position() != 0) {
                long r = power - so.length();
                for (long x = 0; x < r; x++) {
                    zer += '0';
                }

                // Increment so and reset the zero string.

                so = zer + so;
                zer = "";

            }

            // Increment string s and move Next.

            s += so;
            temp.moveNext();
        }
        
	// Add newline character and return the string.
	s += "\n";

	return s;
    }

    // If this BigInteger is positive then no additional sign is needed.

    if (signum == 1) {
        temp.moveFront();
        
	// Add the digits to string s.
	while (temp.position() < temp.length()) {
	    long val = temp.peekNext();
	    if (val < 0) {
		val = val * -1;
	    }
	    so = std::to_string(val);
	    
	    // Check the length and position is not front of the list.
	    if (so.length() < power && temp.position() != 0) {
		long r = power - so.length();
	        for (long x = 0; x < r; x++) {
		    zer += '0';
		}

		// Increment so and reset the zero string.

		so = zer + so;
		zer = "";

	    }

	    // Increment string s and move Next.

	    s += so;
	    temp.moveNext();
	}

	// Add newline character at the end and return string s.

	s += "\n";

	return s;
    }

    // Failsafe return newline and empty string is signum is not 0, 1, or -1 
    // somehow.

    s += "\n";

    return s;
}

// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    // Return the result.
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.

bool operator==(const BigInteger& A, const BigInteger& B) {
    // Check if BigInteger A and B are equal using the compare function.
    if (A.BigInteger::compare(B) == 0) {
        return true;
    }
    
    // Otherwise return false.
    return false;    
}

// operator<()
// Returns true if and only if A is less than B.

bool operator<(const BigInteger& A, const BigInteger& B) {
    // Check if BigInteger A is less than BigInteger B.
    if (A.BigInteger::compare(B) == -1) {
    	return true;
    }

    // Otherwise return false.
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.

bool operator<=(const BigInteger& A, const BigInteger& B) {
    // Check if BigInteger A is less than or equal to BigInteger B.
    if (A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0) {
	return true;
    }

    // Otherwise return false.
    return false;
}

// operator>()
// Returns true if and only if A is greater than B.

bool operator>(const BigInteger& A, const BigInteger& B) {
    // Check if BigInteger A is greater than BigInteger B.
    if (A.BigInteger::compare(B) == 1) {
	return true;
    }

    // Otherwise return false.
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.

bool operator>=(const BigInteger& A, const BigInteger& B) {
    // Check if BigInteger A is greater than or equal to BigInteger B.
    if (A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0) {
	return true;
    }

    // Otherwise return false.
    return false;
}

// operator+()
// Returns the sum A+B

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    // Define result as A + B.
    BigInteger result = A.BigInteger::add(B);
    
    // return result.
    return result;
}

// operator+=()
// Overwrites A with the sum A+B.

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    // Define result as A + B.
    BigInteger result =  A.BigInteger::add(B);

    // Set A equal to result.
    A = result;

    // return A
    return A;
}

// operator-()
// Returns the difference A-B.

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    // Define result as A - B.
    BigInteger result = A.BigInteger::sub(B);

    // Return result.
    return result;
}

// operator -=()
// Overwrites A with the difference A-B.

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    // Define result as A-B.
    BigInteger result = A.BigInteger::sub(B);

    // Overwrite A with the result.
    A = result;

    // Return A at this point.
    return A;
}

// operator*()
// Returns the product A*B.

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    // Define result as A*B.
    BigInteger result = A.BigInteger::mult(B);

    // return the result.
    return result;
}

// operator*=()
// Overwrites A with the product A*B.

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    // Define result as A*B.
    BigInteger result = A.BigInteger::mult(B);

    // Overwrite A with result.
    A = result;

    // Return A at this point.
    return A;
}
