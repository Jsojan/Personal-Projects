#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/stat.h>
#include <time.h>
#include <gmp.h>

#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"

// This is the usage function that will be printed in the event of no
// input or the user inputs an incorrect input. Since this function is void
// typed it should not return anything.

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This program generates the necessary keys for RSA encryption.\n"
        "\n"
        "USAGE\n"
        "  %s [hvb:i:n:d:s:] [-b bits] [-i iterations] [-n public key file]\n"
        "\n"
        "OPTIONS\n"
        "   -b Specify the minimum bits needed for the public modulus n. \n"
        "   -i Specifies the number of Miller-Rabin iterations. \n"
        "   -n Specifies the public key file.\n"
        "   -d Specifies the private key file.\n"
        "   -s Specify the random seed for the random state. \n"
        "   -v Enables verbose output. \n"
        "   -h Displays the program's usage and synopsis. \n",
        exec);
}

// Define main function for using getopt loop to parse in command line options
// from the users. This function is not void type so it should return
// something.

int main(int argc, char **argv) {
    // Declare needed variables for default values here.
    int opt = 0;

    uint64_t nbits = 256;
    uint64_t iters = 50;
    unsigned seed = time(NULL);

    FILE *pbfile = fopen("rsa.pub", "w");
    FILE *pvfile = fopen("rsa.priv", "w");

    // Boolean flag for verbose input.
    bool verbose = false;

    // Create mpz_t variables needed for making public and private keys.
    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t e;
    mpz_t d;
    mpz_t r;
    mpz_t s;

    // Initialize the mpz_t variabes.

    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    mpz_init(r);
    mpz_init(s);

    // Create getopt loop.
    while ((opt = getopt(argc, argv, "hvb:i:n:d:s:")) != -1) {
        switch (opt) {
        case 'v': {
            verbose = true;
            break;
        }
        case 'b': {
            nbits = strtoul(optarg, NULL, 10);
            break;
        }
        case 'i': {
            iters = strtoul(optarg, NULL, 10);
            break;
        }
        case 'n': {
            fclose(pbfile);
            pbfile = fopen(optarg, "w");
            break;
        }
        case 'd': {
            fclose(pvfile);
            pvfile = fopen(optarg, "w");
            break;
        }
        case 's': {
            seed = strtoul(optarg, NULL, 10);
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

    // Check if user input for pvfile and pbfile are valid.

    if (pbfile == NULL) {
        perror("Failed to write to public key file, nonexistant file specified.");
        return 0;
    }

    if (pvfile == NULL) {
        perror("Failed to write to private key file, nonexistant file specified.");
        return 0;
    }

    // Using fchmod() and fileno(), set private key permissions to 0600.
    fchmod(fileno(pvfile), 0600);

    // Initialize randstate.
    randstate_init(seed);

    // Make public and private keys.

    rsa_make_pub(p, q, n, e, nbits + 1, iters);
    rsa_make_priv(d, e, p, q);

    // Get the username using getenv().
    char *u = getenv("USER");

    // Convert the username into an mpz_t with mpz_set_str();
    mpz_set_str(r, u, 62);

    // Sign using username with rsa_sign.
    rsa_sign(s, r, d, n);

    // Write the computed public and private key.
    rsa_write_pub(n, e, s, u, pbfile);
    rsa_write_priv(n, d, pvfile);

    // Check if verbose output is provided and return verbose.

    if (verbose) {
        int so = mpz_sizeinbase(s, 2);
        int po = mpz_sizeinbase(p, 2);
        int qo = mpz_sizeinbase(q, 2);
        int no = mpz_sizeinbase(n, 2);
        int eo = mpz_sizeinbase(e, 2);
        int dp = mpz_sizeinbase(d, 2);

        gmp_printf("user = %s\n", u);
        gmp_printf("s (%d  bits) = %Zd\n", so, s);
        gmp_printf("p (%d  bits) = %Zd\n", po, p);
        gmp_printf("q (%d  bits) = %Zd\n", qo, q);
        gmp_printf("n (%d  bits) = %Zd\n", no, n);
        gmp_printf("e (%d  bits) = %Zd\n", eo, e);
        gmp_printf("d (%d  bits) = %Zd\n", dp, d);
    }

    // Close the public and private files at the end of the program.
    fclose(pbfile);
    fclose(pvfile);

    //Clear mpz_t variables to prevent memory leaks.
    mpz_clears(p, q, n, e, d, r, s, NULL);

    // Clear randstate to prevent memory leaks.
    randstate_clear();
    return 0;
}
