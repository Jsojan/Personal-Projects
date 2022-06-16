#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include <gmp.h>

#include "randstate.h"

// This is the numtheory c file where the numtheory functions
// will be implemented.

// This is the gcd function which takes in input of two numbers a
// and b, and stores the greatest common denominator of both numbers
// in variable d. This function should not return anything since it
// is a void type function.

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t t;
    mpz_t r;
    mpz_t s;

    mpz_init(r);
    mpz_init(s);

    mpz_set(r, b);
    mpz_set(s, a);

    mpz_init(t);
    while (mpz_cmp_ui(r, 0) > 0) {
        // Set t = b.
        mpz_set(t, r);
        // Set r = a % b
        mpz_mod(r, s, r);
        // Set s = t.
        mpz_set(s, t);
    }
    // Set d = s.
    mpz_set(d, s);
    mpz_clears(t, r, s, NULL);
    return;
}

// This is the lcd function to be used in the rsa function. This function is
// void type and should not return anything.

// This function stores the modulo inverse of values a and n in
// inverse i. This function is also a void type so it should not return
// anything.

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r;
    mpz_t rp;
    mpz_t t;
    mpz_t tp;
    mpz_t q;
    mpz_t p;
    mpz_t temp;
    mpz_t tempo;

    mpz_init(r);
    mpz_init(rp);
    mpz_init(t);
    mpz_init(tp);
    mpz_init(q);
    mpz_init(p);
    mpz_init(temp);
    mpz_init(tempo);
    // Set r = n.
    mpz_set(r, n);
    // Set rp = a.
    mpz_set(rp, a);
    // Set t = 0.
    mpz_set_si(t, 0);
    // Set tp = 1.
    mpz_set_si(tp, 1);

    while (mpz_cmp_ui(rp, 0) > 0) {
        // Find q and store temp variables for r and t.
        // Set q = r / rp.
        mpz_tdiv_q(q, r, rp);
        mpz_set(p, q);
        // Set tempo = t and temp = r.
        mpz_set(temp, r);
        mpz_set(tempo, t);
        // Set r = rp.
        mpz_set(r, rp);
        // Set rp = temp - (q * rp).
        mpz_mul(q, q, rp);
        mpz_sub(temp, temp, q);
        mpz_set(rp, temp);
        // Set t = tp.
        mpz_set(t, tp);
        // Set tp = tempo - (q * tp).
        mpz_mul(p, p, tp);
        mpz_sub(tempo, tempo, p);
        mpz_set(tp, tempo);
    }
    // if (r > 1).
    if (mpz_cmp_ui(r, 1) > 0) {
        // Return no inverse.
        // Set i = 0;
        mpz_set_si(i, 0);
        return;
    }
    // if (t < 0).
    if (mpz_cmp_ui(t, 0) < 0) {
        // Set t = t + n.
        mpz_add(t, t, n);
    }
    // Set inverse to t.
    // Set i = t.
    mpz_set(i, t);
    mpz_clears(r, rp, t, tp, q, p, temp, tempo, NULL);
    return;
}

// This function stores the power mod of base a, exponent d,
// and modulus n as the output out. Since this function is a void
// type it should not return anything.

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    // Initialize v and p.
    mpz_t v;
    mpz_t p;
    mpz_t d;

    mpz_init(v);
    mpz_init(p);
    mpz_init(d);

    // Set v = 1.
    mpz_set_si(v, 1);
    // Set p = base.
    mpz_set(p, base);
    mpz_set(d, exponent);

    // While condition for exponent > 0.
    while (mpz_cmp_ui(d, 0) > 0) {
        // Check if exponent is odd.
        // If (exponent % 2 == 1)

        if (mpz_odd_p(d) > 0) {
            // Set v = (v * p) % modulus.
            mpz_mul(v, v, p);
            mpz_mod(v, v, modulus);
        }
        // Set p = (p * p) % modulus.
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);
        // Floor division of exponent.
        // Set exponent = exponent / 2.
        mpz_tdiv_q_ui(d, d, 2);
    }
    // Set out = v.
    mpz_set(out, v);
    mpz_clears(v, p, d, NULL);
    return;
}

// This function returns a boolean true or false value depending on
// whether the input value is a prime or not. This functions also
// repeats over multiple iterations of an unsigned 64 bit number of
// iterations. The primality test is based off the Miller-Rabin primality
// probability checker.

bool is_prime(mpz_t n, uint64_t iters) {
    // Initialize needed variables.
    mpz_t r;
    mpz_t s;
    mpz_t a;
    mpz_t y;
    mpz_t j;
    mpz_t var;
    mpz_t varo;
    mpz_t nt;
    mpz_t two;
    mpz_t no;
    mpz_t so;

    mpz_init(r);
    mpz_init(s);
    mpz_init(a);
    mpz_init(y);
    mpz_init(j);
    mpz_init(var);
    mpz_init(varo);
    mpz_init(nt);
    mpz_init(two);
    mpz_init(no);
    mpz_init(so);

    // Set mpz_t two = 2 to be used later.
    mpz_set_ui(two, 2);
    mpz_set_ui(r, 0);
    mpz_set_ui(nt, 0);

    // Set r = n-1.
    mpz_sub_ui(r, n, 1);
    // Set s = 0;
    mpz_set_ui(s, 0);
    // Set var = 0;
    mpz_set_ui(var, 0);
    // Set varo = 0;
    mpz_set_ui(varo, 0);

    //Check for negative input;
    // If (n <= 0) return false.

    if (mpz_cmp_ui(n, 0) <= 0) {
        return false;
    }

    // while r % 2 != 1.

    while (mpz_even_p(r) > 0) {
        // r = r / 2;
        mpz_tdiv_q_ui(r, r, 2);
        // s = s + 1;
        mpz_add_ui(s, s, 1);
    }

    mpz_sub_ui(no, n, 1);
    mpz_sub_ui(so, s, 1);

    // Perform multiple iterations.
    for (uint64_t i = 1; i < iters; i++) {
        // a = mpz_urandom % (n-4) + 2.
        mpz_sub_ui(nt, n, 4);
        mpz_urandomm(a, state, n);
        mpz_mod(a, a, nt);
        mpz_add_ui(a, a, 2);

        // Store power mod result in temp variable.
        pow_mod(var, a, r, n);
        // Store y = var;
        mpz_set(y, var);
        // if (y != 1 && y != n-1).
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, no) != 0) {
            // Initialize j as 1 before starting while loop.
            mpz_set_ui(j, 1);
            // while (j <= s-1 && y != n-1).
            while (mpz_cmp(j, so) <= 0 && mpz_cmp(y, no) != 0) {
                // Store power mod result in another temp variable.
                pow_mod(varo, y, two, n);
                // y = varo;
                mpz_set(y, varo);
                // Return False if y equals one.
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(r, s, a, y, j, var, varo, nt, two, no, so, NULL);
                    return false;
                }
                // j = j + 1;
                mpz_add_ui(j, j, 1);
            }
            // if (y != n-1)
            if (mpz_cmp(y, no) != 0) {
                // Return False if y does not equal n minus one.
                mpz_clears(r, s, a, y, j, var, varo, nt, two, no, so, NULL);
                return false;
            }
        }
    }
    // Return True if loop ends with no return value.
    mpz_clears(r, s, a, y, j, var, varo, nt, two, no, so, NULL);
    return true;
}

// This is the make prime function that generates a new prime and is
// stored in p. The primality of the generated prime should be tested using
// is_prime() wither iters number of iterations. Since this is a void type
// function it should return nothing.

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    // Create a boolean variable for while loop
    bool check = true;
    uint64_t off;
    // Initialize variable x.
    mpz_t x;

    mpz_init(x);

    // Make offset equal to 2^bits.
    off = 1 << bits;

    while (check) {
        // Call mpz_urandomb function with specified bits.
        mpz_urandomb(x, state, bits);
        // Add offset to this function to ensure minimum prime is 2^b.
        mpz_add_ui(x, x, off);
        // Check if the number is odd and prime.
        if (mpz_odd_p(x) > 0 && is_prime(x, iters) > 0) {
            // If true, set p equal to x and clear x.
            mpz_set(p, x);
            mpz_clear(x);
            return;
        }
    }
    // Clear x here just in case.
    mpz_clear(x);
    return;
}
