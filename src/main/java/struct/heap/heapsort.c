#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

static void print(void* data);
void heapsort(Heap h);
static int check(Heap h);

typedef struct {
    int integer;
} obj_t;

int
cmp(void *aa, void *bb) {
    return ((obj_t*)aa)->integer - ((obj_t*)bb)->integer;
}


int
main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "specify number of elements\n");
        exit(EXIT_FAILURE);
    }
    int numel = atoi(argv[1]);
    Heap h = new_heap(numel, cmp);
    for (int i = 0 ; i < numel; i++) {
        obj_t *target = malloc(sizeof(obj_t));
        target->integer = (rand() + 1)%1000;
        h->data[i] = target;
        h->size++;
    }
    heapsort(h);
    h->size = h->max_capacity; // cheating, but nesessary
    /* Htraverse(h, print); puts("\n"); */
    if (!check(h)) {
        fprintf(stderr,"Check failed, array not sorted\n");
    } else {
        fprintf(stderr, "Check went successfully\n");
    }
    Hfree(h);
    return 0;
}

static
int check(Heap h) {
    for (int i = 1; i < h->size; i++) {
        if (cmp(h->data[i], h->data[i-1]) < 0) {
            return 0;
        }
    }
    return 1;
}


static
void swap(void **aa, void **bb) {
    void *temp = *aa;
    *aa = *bb;
    *bb = temp;
}

static void
print(void* data) {
    printf("%d ", ((obj_t*)data)->integer);
}

void
heapsort(Heap h) {
    heapify(h);
    for (int i = h->size-1; i > 0; i--) {
        swap(h->data[0], h->data[i]);
        h->size--;
        sieve_down(h, 0);
    }
}
