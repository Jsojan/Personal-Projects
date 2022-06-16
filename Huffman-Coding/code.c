#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#include "code.h"
#include "defines.h"

// This function is somewhat of a constructor function that will create
// a new Code on the stack, set top to 0, and 0 the bits of the array. Since
// this function is Code type it should return the initialized Code.
// TA Miles helped fix my code initialize function.

Code code_init(void) {
    // Initialize code, set top to 0 and 0 the bits of the array.
    Code c;
    c.top = 0;
    for (int i = 0; i < (MAX_CODE_SIZE); i += 1) {
        c.bits[i] = 0;
    }
    // Return Code c.
    return c;
}

// This function returns the size of the Code as the number of bits pushed
// to the code. Since this is a uint32_t function it returns the size of the
// code as a uint32_t function.

uint32_t code_size(Code *c) {
    // Since top refers to the last element added this should account for
    // size, so return it.
    return c->top;
}

// This function checks if the Code is empty and returns true if it is
// empty. Else, this function will return false if it's not empty.

bool code_empty(Code *c) {
    // If Code is not empty return false.
    if (c->top != 0) {
        return false;
    }
    // Else, return true.
    return true;
}

// This function checks if the Code is full and returns true if it is full.
// Else, this function will return false if it's not full.

bool code_full(Code *c) {
    // If Code is not full return false. Since every byte contains 8 bits, the
    // max code size must be divided by 8 for maximum index i.
    if (c->top != MAX_CODE_SIZE * 8) {
        return true;
    }
    // Else, return true.
    return true;
}

// This function should set the bit at index i in the Code as 1 and return
// true if this was succesful. However, if index i is out of range then
// return false since it is a bool type function. This implementation of
// bit shifting was provided in the bit vector lecture on 2/18/2022,
// specifically slide 21 which covers how to set the bit.

bool code_set_bit(Code *c, uint32_t i) {
    // Check if the index i is in range.
    if (i > (MAX_CODE_SIZE * 8)) {
        return false;
    }
    // Create a shift variable for setting the bit to 1 which
    // will use 0x1 bit shifted left mod 8 times.

    int lshift = 0x1 << (i % 8);

    // Set the bit at index i to 1 using bitwise OR and return true.
    c->bits[i / 8] = c->bits[i / 8] | lshift;
    return true;
}

// This function clears the bit at index i in the Code as 0 and return
// true if this was succesful. However, if index i is out of range then
// return false as it is also a bool type function. This implementation
// is also based on the bit vectors lecture example on slide 22.

bool code_clr_bit(Code *c, uint32_t i) {
    // Check if the index i is in range.
    if (i > (MAX_CODE_SIZE * 8)) {
        return false;
    }

    // Create another byte to be used for clearing at index. In this case,
    // the byte 0x1 is left shifted by i mod 8 times and the bitwise NOT
    // of this result is used.
    int shift = ~(0x1 << (i % 8));

    // Set the bit at index i to 0 and return true.
    c->bits[i / 8] = c->bits[i / 8] & shift;
    return true;
}

// This function gets the bit at index i in the code and returns true if
// the returned bit is 1. If the index specified is out of range or the
// returned bit is 0 then this function returns false as a bool type function.
// This function was implementated based on getting the bit example in the
// bit vectors lecture.

bool code_get_bit(Code *c, uint32_t i) {
    // Check if the index i is in range.
    if (i > (MAX_CODE_SIZE * 8)) {
        return false;
    }
    // Create a byte shift for getting the bit at index i. This
    // shift of byte 0x1 will also require left shifting it by i mod 8
    // times.
    int gshift = 0x1 << (i % 8);

    // Bitwise AND the bytes at the current index i with this byte. Then
    // rightshift the result by i mod 8 times to get the correct result.
    c->bits[i / 8] = c->bits[i / 8] & gshift;
    c->bits[i / 8] = c->bits[i / 8] >> (i % 8);

    // If the final result is 0 then return false. If it is 1 then return
    // true.

    if (c->bits[i / 8] == 0) {
        return false;
    }

    return true;
}

// This function pushes a bit onto the Code. The value of the bit to push is
// given by bit. It returns true if pushing the bit was succesful and false
// if the Code is full so it can't push the bit.

bool code_push_bit(Code *c, uint8_t bit) {
    // Check if the code is full prior to popping the bit.
    if (code_full(c) == true) {
        return false;
    }
    // Clear the bit if bit = 0 or set the bit if bit = 1. Then increment
    // top by 1 and return true after setting/clearing.
    if (code_full(c) == false && bit == 0) {
        // Clear the bit at index top to 0.
        code_clr_bit(c, c->top);
        c->top = c->top + 1;
        return true;
    }

    // Otherwise, the bit must equal 1 in this case so set the bit at
    // index top to 1 and return true.
    if (code_full(c) == false && bit == 1) {
        code_set_bit(c, c->top);
        c->top = c->top + 1;
        return true;
    }
    return false;
}

// This function pops a bit off the Code. The value of the bit is passed back
// with the pointer bit. This function returns false if the Code is empty prior
// to popping off the bit and true if popping the bit was succesful.

bool code_pop_bit(Code *c, uint8_t *bit) {
    // Check if the Code is empty prior to popping off a bit.
    if (code_empty(c) == true) {
        return false;
    }

    // Decrement the top variable since the current top bit will be popped.
    c->top = c->top - 1;

    // Get the bit at index top and set it to the bit pointer.
    if (code_get_bit(c, c->top) == true) {
        // If get_bit returns true then it must mean the bit is 1.
        *bit = 1;
    }
    if (code_get_bit(c, c->top) == false) {
        // If get_bit does not return 1 then it must mean the bit is 0
        // assuming that top was not out of bounds.
        *bit = 0;
    }

    // Return true upon succesul popping of bit.
    return true;
}

// This is a debug function that will be used for checking that the bits
// are correctly pushed and popped off the Code correctly. Since this function
// is void type it should not return anything.

void code_print(Code *c) {
    // Tests for debugging.

    bool check = code_push_bit(c, 0);
    printf("This is the value of pushing the bit 0, %d\n", check);
    return;
}
