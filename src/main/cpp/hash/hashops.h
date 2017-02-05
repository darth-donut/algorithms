#ifndef _HASHOPS_H_
#define _HASHOPS_H_

#include "list.h"

typedef struct bucket_t*    Bucket;
typedef struct hash_t*        Hash;

enum TYPES {DOUBLE, CHAIN, MTF};

struct hash_t {
    Bucket  *buckets;
    uint        size;
    uint           n;
    int         type;
    uint   (*hash1)(char *, uint);
    uint   (*hash2)(char *, uint);
    int    (*cmp)(void *, void *);

};


struct bucket_t {
    uint    size;
    void   *data;       // TODO: remove data, use pockets (0)?
    List pockets;
};

Hash Hcreate(uint n, int type, int (*cmp) (void *, void *));
/* note: do note use the same address for key if key changes
 * ie, no malloc happens within Hinsert */
void Hinsert(Hash H, char *key);
void *Hsearch(Hash H, char *key);
void *Hdel(Hash H, char *key);
void Htraverse(Hash H, void (*action)(void *));
uint Hsize(Hash H);
void Hfree(Hash H);
#endif
