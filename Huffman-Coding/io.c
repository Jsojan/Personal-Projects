#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "io.h"
#include "defines.h"

// Initialize extern variables and the static buffer needed. Create
// a static index variable to be used for read_bit. 

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

static uint8_t buffer[BLOCK] = { 0 };

// Index will be used for read bits while top will be used for write_code
// and flush codes.

static int index = 0;
static int top = 0;

// -1 refers to the last element in the buffer as the default value.

static int end = -1;

// This function performs reads and returns the number of bytes read
// if it was succesful as an integer.

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    // Create needed variables.
    int byread = 1;
    int bytes_left = 0;
    // Read until no more bytes can be read as the condition is while byread is    // greater than 0.
    while (byread > 0) {
        // Read from infile the number of bytes.
        byread = read(infile, buf, nbytes);
        // Increment bytes left, check, bytes read. Then increment the buf
        // pointer to move its position in the buffer and the nbytes left to
        // read if not all bytes are written on first read.

        bytes_left = bytes_left + byread;
        buf = buf + bytes_left;
        nbytes = nbytes - bytes_left;

        // This break statement checks if bytes_left is now equal to nbytes.
        if (bytes_left == nbytes) {
            break;
        }
    }

    // Return check at end of function.
    bytes_read = bytes_read + bytes_left;
    return bytes_left;
}

// This function performs writes and returns the number of bytes written if
// it was succesful as an integer.

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bywrite = 1;
    int bytes_left = 0;
    // Write until no more bytes can be written as denoted by greater than 0.
    while (bywrite > 0) {
        // Write bytes to outfile.
        bywrite = write(outfile, buf, nbytes);
        // Increment bytes_left to write. Then increment the bytes in
        // buf and nbytes.

        bytes_left = bytes_left + bywrite;
        buf = buf + bytes_left;
        nbytes = nbytes - bytes_left;

        // If write returns 0 then there are no more bits to write so return 0.
        if (bywrite == nbytes) {
            break;
        }
    }

    bytes_written = bytes_written + bytes_left;
    // Return statement for returning the bytes.
    return bytes_left;
}

// This function reads a bit from the input file by reading in a byte first
// and doling out all the bits of the byte. Since this function is bool
// type, this function returns false if no more bits can be read, and true if
// there are more.

bool read_bit(int infile, uint8_t *bit) {
    // If index is 0 assume that the buffer needs to be filled with bytes
    // so read bytes from the file.
    if (index == 0) {
        int check = read_bytes(infile, buffer, 4096);
        if (check < 4096) {
            // Set the maximum end count to count plus one.
            end = (check * 8) + 1;
        }
    }
    // If index is within the range then get the specified bit at the current
    // index and set the bit pointer to the bit retreived.

    if (index >= 0) {
        int gshift = 0x1 << (index % 8);
        gshift = buffer[index / 8] & gshift;

        // Shift the result using a right shift index mod 8 times.
        gshift = gshift >> (index % 8);

        // Then AND the result of gshift with 1.
        gshift = gshift & 1;

        // Set the bit pointer equal to the bit retrieved.
        *bit = gshift;

        // Increment index by 1.
        index = index + 1;
    }

    // Check if the buffer index is at the last bit. 32768 is equivalent to
    // BLOCK SIZE 4096 * 8. If it is the last index of the buffer then reset
    // index to 0.
    if (index == 32768) {
        index = 0;
    }

    // Check if the index has reached the end of the file and return false.
    // This if condition works since end has a default value of -1. However,
    // if the read bytes are less than the 4096 bytes allocated to buffer,
    // then this indicates the end of file and so there are no more bytes to
    // read.
    if (index == end) {
        return false;
    }

    // Return true if this is the end of the file since there are more bytes
    // to read.
    return true;
}

// This function works similarly to read_bit in the fact that it requires
// the static buffer and index. Each bit in code c will be buffered into
// the buffer and the bits will be buffered starting from the 0th bit in c.

void write_code(int outfile, Code *c) {
    // Initialize shift implementation borrowed from get bit from code.c
    for (uint32_t i = 0; i < code_size(c); i++) {
        int gshift = 0x1 << (i % 8);
        gshift = c->bits[i / 8] & gshift;
        gshift = gshift >> (i % 8);

        // Borrow code set bit and clear bit implementation from code.c
        // Check if gshift bit is 0 and implement clearig the bit like
        // in code.c
        if (gshift == 0) {
            int shift = ~(0x1 << (top % 8));
            buffer[top / 8] = buffer[top / 8] & shift;
        }
        // Check if gshift bit is 1 and implement setting bit to 1 like
        // in code.c
        if (gshift == 1) {
            int lshift = 0x1 << (top % 8);
            buffer[top / 8] = buffer[top / 8] | lshift;
        }

        // Increment top by 1.
        top = top + 1;

        // Check if the top index is the last byte or 32768 and flush out
        // necessary bits since block is 4096 bytes times 8 which is 32768.

        if (top == 32768) {
            flush_codes(outfile);
        }
    }

    // Return nothing since void function.
    return;
}

// This function performs code flush in which it adds extra bits to ensure
// full bytes of data and then flushes it. Since this function is void
// typed it should not return anything.

void flush_codes(int outfile) {
    // The adding of 7 to top performs a pseudo floor for rounding up the
    // flush bytes.

    if (top > 0) {
        int flush = (top + 7) / 8;

        // write the extra flushed bytes using the write_bytes function.
        write_bytes(outfile, buffer, flush);

        // Set the buffer to 0 after writing out the flushed bits.
        for (int x = 0; x < BLOCK; x++) {
            buffer[x] = 0;
        }

        // Reset top to 0 to signify flush is complete.
        top = 0;
    }

    // Return nothing since void type function.
    return;
}
