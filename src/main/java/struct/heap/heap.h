#include <stdbool.h>

#ifndef __HEAP_
#define __HEAP_
typedef struct heap_t* Heap;

struct heap_t {
    void **data;
    int size;
    int max_capacity;
    int (*cmp) (void *, void *);
};

/**
 * Creates a new heap and returns a pointer to it
 *
 * numel: the number of elements that are estimated to be in this
 * heap
 * cmp: parent -> child */
Heap new_heap(size_t numel, int (*cmp) (void *, void *));
/**
 * Inserts an element into the heap, auto-resize if
 * elements are overbound
 *
 * h: the heap pointer
 * elem: the element that should go into the heap, in a pointer
 */
void Hinsert(Heap h, void *elem);
/**
 * Traverses the heap and calls action onto each element
 *
 * h: the heap pointer
 * elem: the action to call on each object in the heap
 */
void
Htraverse(Heap h, void (*action)(void *));
/**
 * Frees the heap from all memory
 *
 * h: heap pointer
 */
void
Hfree(Heap h);
/**
 * Pops the largest/smallest item from the head of the array and returns the pointer to it
 *
 * h: heap pointer
 */
void
*Hpop_head(Heap h);
/**
 * Returns the pointer to an item if found, null otherwise.
 *
 * h: heap pointer
 * key: pointer to object that needs to be found
 * index: pointer to number, returns an index of where item was found, -1 if not found
 */
void
*find(Heap h, void *key, int *index);
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
decrease_key(Heap h, void *key, void (*action) (void *));

void heapify(Heap h);
void sieve_down(Heap h, int parent);
void sieve_up(Heap h, int parent);
#endif
