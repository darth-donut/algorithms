/* TODO: cuckoo hashing, murmur hashing */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hashops.h"
#include "hashfunc.h"

#define COEFF_LEN   256  /* length of array of coefficients */

static uint *randnums(uint len, uint size);
static void *smalloc(size_t size);

/* Universal hashing implementation */

uint
unihash1(char *key, uint size) {
    assert(key && "Empty key when attempting to hash");
    static uint *arr = NULL;
    uint keylen = strlen(key);
    uint total  = 0;
    if (!arr)
        arr = randnums(COEFF_LEN, size);
    for (uint i = 0; i < keylen; i++)
        total += (arr[i%COEFF_LEN] * key[i]) % size;
    return total % size;
}

uint
unihash2(char *key, uint size) {
    assert(key && "Empty key when attempting to hash");
    static uint *arr = NULL;
    uint keylen = strlen(key);
    uint total  = 0;
    if (!arr)
        arr = randnums(COEFF_LEN, size);
    for (uint i = 0; i < keylen; i++)
        total += (arr[i%COEFF_LEN] * key[i]) % size;
    return total % size;
}


static uint
*randnums(uint len, uint size) {
    uint *buffer = smalloc(len*sizeof(uint));
    for (uint i = 0; i < len; i++)
        buffer[i] = rand() % size;
    return buffer;
}


static void
*smalloc(size_t size) {
    void *buffer = malloc(size);
    assert(buffer && "Buffer malloc failed\n");
    return buffer;
}
