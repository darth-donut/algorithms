#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hashops.h"
#include "hashfunc.h"           /* Auxillary hashing functions */

static void *scalloc(uint n, size_t size);
static void *smalloc(size_t size);
static bool isprime(uint n);
static uint nextprime(uint n);
static bool doubl_ins(Hash H, char *key);
static bool chain_ins(Hash H, char *key);
static bool mtf_ins(Hash H, char *key);
static void *doubl_search(Hash H, char *key);
static void *chain_search(Hash H, char *key);
static void *mtf_search(Hash H, char *key);
static void *doubl_del(Hash H, char *key);
static void *chain_del(Hash H, char *key);


/* Using universal hashing, with table size = nextprime(expected size*2) */
Hash
Hcreate(uint n, int type, int (*cmp) (void *, void *)) {
    uint size   = nextprime(n*2);
    Hash H      = (Hash)smalloc(sizeof(*H));
    H->buckets  = (Bucket *)scalloc(size, sizeof(*(H->buckets)));
    H->size     = size;
    H->n        = 0;
    H->hash1    = unihash1;
    H->hash2    = unihash2;
    H->type     = type;
    H->cmp      = cmp;
    return H;
}


void
Hinsert(Hash H, char *key) {
    H->n++;
    switch (H->type) {
        case DOUBLE:
            assert(doubl_ins(H, key));
            break;
        case CHAIN:
            assert(chain_ins(H, key));
            break;
        case MTF:
            assert(mtf_ins(H, key));
            break;
    }
}

uint
Hsize(Hash H) {
    return H->n;
}

void
Hfree(Hash H) {
    switch(H->type) {
        case CHAIN:
        case MTF:
            for (int i = 0; i < H->size; i++)
                if (H->buckets[i]) {
                    Lfree(H->buckets[i]->pockets);
                    free(H->buckets[i]);
                }
            break;
        case DOUBLE:
            for (int i = 0; i < H->size; i++)
                if (H->buckets[i])
                    free(H->buckets[i]);
            break;
    }
}

void
*Hsearch(Hash H, char *key) {
    switch (H->type) {
        case DOUBLE:
            return doubl_search(H, key);
        case CHAIN:
            return chain_search(H, key);
        case MTF:
            return mtf_search(H, key);
    }
}

void
Htraverse(Hash H, void (*action)(void *)) {
    switch (H->type) {
        case DOUBLE:
            for (int i = 0; i < H->n; i++)
                if (H->buckets[i])
                    action(H->buckets[i]->data);
            break;
        case CHAIN:
        case MTF:
            for (int i = 0; i < H->n; i++)
                if (H->buckets[i])
                    Ltraversel(H->buckets[i]->pockets, action);
            break;
    }
}

void
*Hdel(Hash H, char *key) {
    void *data;
    switch (H->type) {
        case DOUBLE:
            if (data = doubl_del(H, key))
                H->n--;
            return data;
        case CHAIN:
        case MTF:
            if (data = chain_del(H, key))
                H->n--;
            return data;
    }
}

/* by deleting, essentially finding, if that data exists, move it
 * to front because we are expecting that data to be skewed, hence
 * almost always accessed (searched for or deleted), especially since
 * Lfind() from list.c uses a linear search from the head on */
static void
*mtf_search(Hash H, char *key) {
    assert(H && key && "Hash or key missing");
    uint index      = H->hash1(key, H->size);
    void *data;
    if (H->buckets[index]) {
        data        = Ldel(H->buckets[index]->pockets, key, H->cmp);
        if (data) {
            Lpush(H->buckets[index]->pockets, data);
            return data;
        }
    }
    return NULL;
}

static void
*chain_del(Hash H, char *key) {
    assert(H && key && "Hash or key missing");
    uint index      = H->hash1(key, H->size);
    return H->buckets[index]
        ? Ldel(H->buckets[index]->pockets, key, H->cmp)
        : NULL;
}

static void
*doubl_del(Hash H, char *key) {
    assert(H && key && "Hash or key missing");
    uint index   = H->hash1(key, H->size), i;
    for (i = 0;
            H->cmp(H->buckets[index]->data, key) != 0
            && i < H->size; i++)
        index    = (i*H->hash2(key, H->size) + index) % H->size;
    if (i >= H->size)
        return NULL;
    else {
        void *data          = H->buckets[index]->data;
        H->buckets[index]   = NULL;
        return data;
    }
}


static bool
chain_ins(Hash H, char *key) {
    assert(H && key && "Hash or key missing");
    uint index      = H->hash1(key, H->size);
    if (!H->buckets[index]) {
        H->buckets[index]          = (Bucket)smalloc(sizeof(*(H->buckets[index])));
        H->buckets[index]->size    += 1;
        H->buckets[index]->pockets = Lpush(NULL, key);
    } else {
        Lappend(H->buckets[index]->pockets, key);
    }
    return true;
}

static bool
mtf_ins(Hash H, char *key) {
    assert(H && key && "Hash or key missing");
    uint index      = H->hash1(key, H->size);
    if (!H->buckets[index]) {
        H->buckets[index]          = (Bucket)smalloc(sizeof(*(H->buckets[index])));
        H->buckets[index]->size    += 1;
        H->buckets[index]->pockets = Lpush(NULL, key);
    } else {
        Lpush(H->buckets[index]->pockets, key);
    }
    return true;
}

static void
*chain_search(Hash H, char *key) {
    assert(H && key && "Hash or key missing");
    uint index      = H->hash1(key, H->size);
    return !H->buckets[index]
        ? NULL
        : Lfind(H->buckets[index]->pockets, key, H->cmp);

}


static void
*doubl_search(Hash H, char *key) {
    assert(H && key && "Hash or key missing");
    uint index   = H->hash1(key, H->size), i;
    for (i = 0;
            H->cmp(H->buckets[index]->data, key) != 0
            && i < H->size; i++)
        index    = (i*H->hash2(key, H->size) + index) % H->size;
    if (i >= H->size)
        return NULL;
    else
        return H->buckets[index]->data;
}


static bool
doubl_ins(Hash H, char *key) {
    assert(H && key && "Hash table or key missing");
    uint index  = H->hash1(key, H->size), i;
    for (i = 0; H->buckets[index] && i < H->size; i++)
        index   = (index + i*H->hash2(key, H->size)) % H->size;
    if (i >= H->size) {
        assert(H->buckets[index]);
        fprintf(stderr, "Hash table full (double hashing)\n");
        exit(EXIT_FAILURE);
    } else {
        H->buckets[index]        = (Bucket)smalloc(sizeof(**(H->buckets)));
        H->buckets[index]->data  = key;
        H->buckets[index]->size++;
    }
}



static uint
nextprime(uint n) {
    do
        n++;
    while (!isprime(n));
    return n;
}


static bool
isprime(uint n) {
    /* TODO: how to deal with overflowing numbers
     * TODO: use fermat's little theorem for prime checking */
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n%2 == 0) {
        assert(!(n&1));
        return false;
    }
    for (uint i = 3; i * i <= n; i++)
        if (n%i == 0)
            return false;
    return true;
}




static void
*smalloc(size_t size) {
    void *buffer = malloc(size);
    assert(buffer && "Malloc failed\n");
    return buffer;
}

static void
*scalloc(uint n, size_t size) {
    void *buffer = calloc(n, size);
    assert(buffer && "Calloc failed");
    return buffer;
}
