#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "heap.h"

typedef struct {
    int integer;
} obj_t ;

static void swap(void **aa, void **bb);

/**
 * Creates a new heap and returns a pointer to it
 *
 * numel: the number of elements that are estimated to be in this
 * heap
 * cmp: parent -> child
 */
Heap
new_heap(size_t numel, int (*cmp) (void *, void *)) {
    Heap h = (Heap)malloc(sizeof(*h));
    assert(h);
    h->data = malloc(numel*sizeof(void *));
    h->size = 0;
    h->max_capacity = numel;
    h->cmp = cmp;
    return h;
}

/**
 * Inserts an element into the heap, auto-resize if
 * elements are overbound
 *
 * h: the heap pointer
 * elem: the element that should go into the heap, in a pointer
 */
void
Hinsert(Heap h, void *elem) {
    if (h->size >= h->max_capacity-1) {
        h->max_capacity *= 2;
        h->data = (void **)realloc(h->data, sizeof(*(h->data)) * (h->max_capacity));
        assert(h->data);
    }
    h->data[h->size++] = elem;
    sieve_up(h, h->size-1);
}


void
heapify(Heap h) {
    for (int i = h->size/2-1; i >= 0; i--)
        sieve_down(h, i);
}

/**
 * Traverses the heap and calls action onto each element
 *
 * h: the heap pointer
 * elem: the action to call on each object in the heap
 */
void
Htraverse(Heap h, void (*action)(void *)) {
    for (int i = 0; i < h->size; i++) {
        action(h->data[i]);
    }
}

/**
 * Frees the heap from all memory
 *
 * h: heap pointer
 */
void
Hfree(Heap h) {
    free(h->data);
    h->data         = NULL;
    h->max_capacity = 0;
    h->size         = 0;
    h->cmp          = NULL;
}


/**
 * Pops the largest/smallest item from the head of the array and returns the pointer to it
 *
 * h: heap pointer
 */
void
*Hpop_head(Heap h) {
    int size = h->size--;
    void **inarr = h->data;
    void *out_data = inarr[0];
    
    swap(inarr[0], inarr[size-1]);
    sieve_down(h, 0);

    return out_data;
}

/**
 * Returns the pointer to an item if found, null otherwise.
 *
 * h: heap pointer
 * key: pointer to object that needs to be found
 * index: pointer to number, returns an index of where item was found, -1 if not found
 */
void
*find(Heap h, void *key, int *index) {
    void **inarr = h->data;
    for (int i = 0; i < h->size; i++) {
        if (h->cmp(inarr[i], key) == 0) {
            *index = i;
            return inarr[i];
        }
    }
    *index = -1;
    return NULL;
}

/**
 * Decreases the key, needs an action that deals with the logic on data. Requires
 * user to provide a key (pointer) that will be used to compare against other data in heap.
 * Will automatically decrease (ie. reheap)
 *
 * h: heap pointer
 * key: pointer to object stored in heap
 * action: function pointer that implements decrease key on the data
 */
bool
decrease_key(Heap h, void *key, void (*action) (void *)) {
    int index;
    void *item = find(h, key, &index);
    if (index == -1) {
        assert(item == NULL);
        return false;
    }
    action(item);
    sieve_down(h, index);
    return true;
}

/*
 * note; max heap by default, sent in a diff cmp function
 * (negated) if min is neeed 
 */
void
sieve_down(Heap h, int parent) {
    int (*cmp)(void *, void *) = h->cmp;
    void **inarr= h->data;
    int child;
    if ((child = parent*2+1) < h->size) {
        // the other child is greater than this
        if (child+1 < h->size &&
                cmp(inarr[child+1], inarr[child]) > 0)
            child++;
        // if the parent is smaller than the child, swap
        if (cmp(inarr[parent], inarr[child]) < 0) {
            swap(inarr[parent], inarr[child]);
            // then check if the new pos of the child is correct
            sieve_down(h, child);
        }
    }
}

void
sieve_up(Heap h, int child) {
    int parent = (child - 1)/2;
    void **inarr = h->data;
    int (*cmp)(void*, void*) = h->cmp;
    assert(child < h->size);
    if (parent >= 0 && cmp(inarr[child], inarr[parent]) > 0) {
        // if the current child is greater than parent, we need to change
        // but check if the sibling is higher
        int sibling = child % 2 == 0 ? child -1 : child + 1;
        if (sibling < h->size && cmp(inarr[sibling], inarr[child]) > 0)
            child = sibling;
        swap(inarr[child], inarr[parent]);
        sieve_up(h, parent);
    }

}

/*
 * swaps data in a void void arr
 */
static void
swap(void **aa, void **bb) {
    void *tmp = *aa;
    *aa = *bb;
    *bb = tmp;
}
