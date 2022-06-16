#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include <gmp.h>

#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"

// This is function creates certain parts of the RSA public key
// using two large primes p and q. Since this function is void it
// should return nothing.

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    // Create needed results.
    mpz_t result;
    mpz_t pm;
    mpz_t qm;
    mpz_t g;
    mpz_t s;
    mpz_t res;
    mpz_t t;
    mpz_t mov;

    // Initialize variables

    mpz_init(result);
    mpz_init(pm);
    mpz_init(qm);
    mpz_init(g);
    mpz_init(s);
    mpz_init(res);
    mpz_init(t);
    mpz_init(mov);

    // Create random seed using time(NULL)

    bool check = true;
    unsigned seed;
    uint64_t x;
    uint64_t y;
    uint64_t off;

    //Initialize mpz_t result to be used for lcm.

    seed = time(NULL);
    srandom(seed);

    // Use random seed to allocate bits for p and q.
    // to get the random numbers in range (n/4, 3n/4).
    x = random() % (nbits / 2) + (nbits / 4);
    y = nbits - x;

    // Create primes p and q.

    make_prime(p, x, iters);
    make_prime(q, y, iters);

    // Evaluate the product of primes p and q.
    mpz_mul(n, p, q);

    // Set p-1 and q-1 for variables.
    mpz_sub_ui(pm, p, 1);
    mpz_sub_ui(qm, q, 1);

    // Set result = abs(p-1 * q-1).

    mpz_mul(result, pm, qm);
    mpz_abs(result, result);

    // Find the gcd of p-1 and q-1.

    gcd(g, pm, qm);

    // Then divide result and g to get lcm of p-1 and q-1.

    mpz_tdiv_q(res, result, g);

    // Stire the value of res in a different variable.

    mpz_set(mov, res);

    // Create offset equal to nbits.

    off = 1 << nbits;

    // Make while loop for seeting public exponent

    while (check) {
        // Generate random numbers around nbits.
        mpz_urandomb(s, state, nbits);

        // Add offset to randomly generated number.

        mpz_add_ui(s, s, off);

        // Calculate gcd of this number with lcm number.

        gcd(t, s, mov);

        // Check if the gcd of the random number and
        // lcm equals 1.

        if (mpz_cmp_ui(t, 1) == 0) {
            // If this case is true set e equal to s.
            mpz_set(e, s);
            //Clear variables and end loop.
            mpz_clears(result, pm, qm, g, res, t, mov, s, NULL);
            return;
        }
    }

    mpz_clears(result, pm, qm, g, res, t, mov, s, NULL);
    return;
}

// This is the rsa write pub file which writes, the n, public exponent e,
// signature s, and username to a file in hex string. Since this function is
// void type it should not return anything.

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    // use gmp fprintf to write each part to the file.
    gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
    return;
}

// This is the rsa read pub file which reads from a file: the product n,
// public exponent e, signature s and username. Since the function is void
// type it should not return anything.

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    // use gmp fscanf to read each part of the file.
    gmp_fscanf(pbfile, "%Zx\n%Zx\n%Zx\n", n, e, s);
    fscanf(pbfile, "%s\n", username);
    return;
}

// This function makes a new RSA private key d given primes p and q and
// public exponent e. This function is also void type and should not return
// anything.

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t result;
    mpz_t pm;
    mpz_t qm;
    mpz_t g;
    mpz_t res;

    // Initialize needed variables.

    mpz_init(result);
    mpz_init(pm);
    mpz_init(qm);
    mpz_init(g);
    mpz_init(res);

    // Assign variables for p-1 and q-1.

    mpz_sub_ui(pm, p, 1);
    mpz_sub_ui(qm, q, 1);

    // Multiply p-1 and q-1 and abs value the result.

    mpz_mul(result, pm, qm);
    mpz_abs(result, result);

    // Also find the gcd of p-1 and q-1.

    gcd(g, pm, qm);

    // Then divide result and gcd of p-1 and q-1 for lcm.

    mpz_tdiv_q(res, result, g);

    // Perform inverse mod of e modulo lcm result and set it to d.

    mod_inverse(d, e, res);
    mpz_clears(result, pm, qm, g, res, NULL);
    return;
}

// This writes a private RSA key to pvfile. The format of the write should
// be n followed by d. Since this function is void, it does not return anything

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    // Writes to private key file.
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", n, d);
    return;
}

// This function reads a file for the private RSA key. Since this function
// is void it should not return anything.

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    // Reads from a private key file.
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", n, d);
    return;
}

// This function performs RSA encryption by computing the cypher text c
// and encrypting the message m using the public exponent. Since this
// function is void it should return nothing/

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    // Perform  m^e mod n using pow_mod function.
    pow_mod(c, m, e, n);
    return;
}

// The purpose of this function is to encrypt the contents of infile and
// save it to outfile. This function is also void type and should not return anything.

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    // Initialize needed variable.
    mpz_t m;
    mpz_t c;

    size_t k;
    size_t j;

    //Initialize mpz_t m;
    mpz_init(m);
    mpz_init(c);

    // Calculate the block size k where k = floor((log base 2 of (n)-1)/8)
    // perform log base 2 of n minus 1.
    k = mpz_sizeinbase(n, 2);
    k -= 1;

    // Perform floor division by 8 to get k block size.
    k = k / 8;

    // Dynamically allocate space for the array
    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t));

    // Set the 0th byte to 0xFF;
    arr[0] = 0xFF;

    // Create loop for reading in bytes from infile.

    while (!feof(infile)) {
        // Read in file input using fread.
        j = fread(&(arr[1]), sizeof(uint8_t), k - 1, infile);

        // Use mpz_import to store the read input to m.
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, arr);

        // Encrypt m using rsa_encrypt function.
        rsa_encrypt(c, m, e, n);

        // Set the cypher text c to OUTFILE as a hex string with new line.
        gmp_fprintf(outfile, "%Zx\n", c);
    }

    mpz_clears(m, c, NULL);
    free(arr);
    return;
}

// The purpose of this function is to perform RSA decryption. Since this
// function is void type it should not return anything.

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    // Perform RSA decryption as c ^ d mod n.
    pow_mod(m, c, d, n);
    return;
}

// This function implements the RSA decryption process of a file. This
// function is also void type and should not return anything.

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    // Initialize needed variables.
    mpz_t c;
    mpz_t m;

    size_t k;
    size_t j;

    // Initialize mpz_t variable c.
    mpz_init(c);
    mpz_init(m);

    // Calculate the block size k where k = floor(log base 2 of n -1 / 8).
    k = mpz_sizeinbase(n, 2);
    k -= 1;

    // Perform floor division on k by 8.
    k = k / 8;

    // Create an  array to store each byte
    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t));

    // Create while loop until end of the file.

    while (!feof(infile)) {
        // Scan the infile with the hexstring.
        gmp_fscanf(infile, "%Zx\n", c);

        // Decrypt c using rsa_decrypt function.
        rsa_decrypt(m, c, d, n);

        // Use mpz_export
        mpz_export(arr, &j, 1, sizeof(uint8_t), 1, 0, m);

        // Write from file to output
        fwrite(&(arr[1]), sizeof(uint8_t), j - 1, outfile);
    }

    mpz_clears(c, m, NULL);
    free(arr);
    return;
}

// This function perform RSA signing by producing a signature s to be verified
// in a later program. This function is also void typed so it should not return
// anything.

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    // Signing RSA using pow_mod.
    pow_mod(s, m, d, n);
    return;
}

// This function returns RSA verification where it returns true if the signature
// s is verified and false otherwise.

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    // Create and initialize a new variable t.
    mpz_t t;
    mpz_init(t);

    // Perform verification using pow_mod;
    pow_mod(t, s, e, n);

    // Check if the signature is the same as m and return true if equal.
    // Clear t when returning the boolean value.
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }

    mpz_clear(t);
    return false;
}
