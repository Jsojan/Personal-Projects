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

// Create usage function for printing the programs usage and synopsis. This
// function is void and should not return anything.

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This program performs RSA encryption.\n"
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
    char u[256];

    // Include necessary header variables.
    FILE *in = stdin;
    FILE *out = stdout;
    FILE *pbfile = fopen("rsa.pub", "r");

    // Boolean flag for verbose input.
    bool verbose = false;

    // Set mpz_t variables.
    mpz_t n;
    mpz_t e;
    mpz_t s;
    mpz_t user;

    // Initialize variables.
    mpz_init(n);
    mpz_init(e);
    mpz_init(s);
    mpz_init(user);

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
            fclose(pbfile);
            pbfile = fopen(optarg, "r");
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

    // Check if user input for reading and writing file input is valid.

    if (pbfile == NULL) {
        perror("Failed to read from specified public key file.");
        return 0;
    }

    // Read the public key from the opened public key file.
    rsa_read_pub(n, e, s, u, pbfile);

    // Print out verbose version if specified.
    if (verbose) {
        int so = mpz_sizeinbase(s, 2);
        int no = mpz_sizeinbase(n, 2);
        int eo = mpz_sizeinbase(e, 2);

        gmp_printf("user = %s\n", u);
        gmp_printf("s (%d bits) = %Zd\n", so, s);
        gmp_printf("n (%d bits) = %Zd\n", no, n);
        gmp_printf("e (%d bits) = %Zd\n", eo, e);
    }

    // Convert username that was read into an mpz_t.

    mpz_set_str(user, u, 62);

    // Verfiy the signature with rsa_verify.

    rsa_verify(user, s, e, n);

    // Encrypt the file using rsa_encrypt_file()
    rsa_encrypt_file(in, out, n, e);

    // Close all files and clear any mpz_t variables.
    fclose(in);
    fclose(out);
    fclose(pbfile);

    mpz_clears(n, e, s, user, NULL);
    return 0;
}
