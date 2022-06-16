#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "node.h"
#include "code.h"
#include "stack.h"
#include "pq.h"
#include "huffman.h"
#include "io.h"
#include "defines.h"
#include "header.h"

// Create usage function for printing the programs usage and synopsis. This
// function is void type and should not return anything.

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  This program performs Huffman decoding."
        "\n"
        " %s [hvi:o:] [-i input file] [-o output file] [-v verbose]\n"
        "\n"
        "OPTIONS\n"
        "   -i Specifies the input file to be used.\n"
        "   -o Specifies the output file to be used.\n"
        "   -v Prints compressions statistics to stderr.\n"
        "   -h Prints the programs usage and synopsis.\n",
        exec);
}

// Create main function with getopt loop to parse in user input commands.
// This function is not void typed and should return an int.

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "hvi:o:")) != -1) {
        switch (opt) {
        case 'v': {
            break;
        }
        case 'i': {
            break;
        }
        case 'o': {
            break;
        }
        case 'h': {
            usage(argv[0]);
            break;
        }
        default: {
            usage(argv[0]);
            break;
        }
        }
    }

    return 0;
}
