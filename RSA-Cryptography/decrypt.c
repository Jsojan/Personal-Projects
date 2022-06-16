#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <getopt.h>
#include <time.h>
#include <gmp.h>

#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"

// This is the usage function that prints the programs usage and synopsis.
// Since this function is void type it should not return anything.

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This program performs RSA decryption.\n"
        "\n"
        "USAGE\n"
        "  %s [hvi:o:n:] [-i input] [-o output] [-n specifies the file]\n"
        "\n"
        "OPTIONS\n"
        "   -i Specify the input file to encrypt. \n"
        "   -o Specifies the output file to encrypt. \n"
        "   -n Specifies the file containing the public key.\n"
        "   -v Enables verbose output\n"
        "   -h Displays the program's usage and synopsis. \n",
        exec);
}

// Create main function with getopt loop to parse in user input commands.
// This function is not void typed and should return something.

int main(int argc, char **argv) {
    // Declare needed variables for default values here.
    int opt = 0;

    // Include necessary header variables.
    FILE *in = stdin;
    FILE *out = stdout;
    FILE *pvfile = fopen("rsa.priv", "r");

    // Boolean flag for verbose input.
    bool verbose = false;

    // Set mpz_t variables.
    mpz_t n;
    mpz_t d;

    // Initialize mpz_t variables.
    mpz_init(n);
    mpz_init(d);

    // Create getopt loop.
    while ((opt = getopt(argc, argv, "hvi:o:n:")) != -1) {
        switch (opt) {
        case 'v': {
            verbose = true;
            break;
        }
        case 'i': {
            in = fopen(optarg, "r");
            break;
        }
        case 'o': {
            out = fopen(optarg, "w");
            break;
        }
        case 'n': {
            fclose(pvfile);
            pvfile = fopen(optarg, "r");
            break;
        }
        case 'h': {
            usage(argv[0]);
            return 0;
        }
        default: {
            usage(argv[0]);
            break;
        }
        }
    }

    // Check if user input for files are valid.

    if (pvfile == NULL) {
        perror("Failed to read from specified private key file.");
        return 0;
    }

    // Read the private key from the opened private key file.

    rsa_read_priv(n, d, pvfile);

    // Check if verbose output is enabled and print accordingly.

    if (verbose) {
        int no = mpz_sizeinbase(n, 2);
        int dp = mpz_sizeinbase(d, 2);

        gmp_printf("n (%d bits) = %Zd\n", no, n);
        gmp_printf("d (%d bits) = %Zd\n", dp, d);
    }

    // Decrypt file using rsa_decrypt_file.
    rsa_decrypt_file(in, out, n, d);

    // Close the private key files and clear all mpz_t variables.
    fclose(in);
    fclose(out);
    fclose(pvfile);

    mpz_clears(n, d, NULL);
    return 0;
}
