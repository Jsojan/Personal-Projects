#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <gmp.h>

#include "randstate.h"

// Initialize state and generate numbers with input seed
// using this function. Since this function is void typed,
// it should return nothing.

gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    // Initialize state with Mersene Twister.
    gmp_randinit_mt(state);
    // Use seed for random seed generator,
    gmp_randseed_ui(state, seed);
    return;
}

// Clear and frees all memory used by the initialized
// global random state with this function. Since this
// function is also a void typed function then it should
// return nothing.

void randstate_clear(void) {
    // Call rand clear to clear memory allocated in state.
    gmp_randclear(state);
    return;
}
