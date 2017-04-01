#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

typedef struct node_t* Node;
typedef struct list_t* List;

/* struct for a doubly-linked list */
struct node_t {
    /* Pointer to data */
    void *data;
    /* Points to next node after this, NULL if there isn't any node after this */
    Node next;
    /* Points to node before this, NULL if there isn't any node before this */
    Node prev;
};

struct list_t {
    /* Points to the head of the list */
    Node head;
    /* Points to the tail of the list */
    Node tail;
    /* current list size */
    size_t size;
    /// comparision function that returns -1 , 0, or 1 (smaller, equals, and greater)
    /// \return -1 if first argument is smaller, 0 if they are equal, 1 otherwise
    int (*cmp)(const void *, const void *);

};

List Lnew(int (*cmp)(const void *, const void *));
void Linsert(List lst, const size_t index, void *data);
void* Lfind(List lst, const void *data);
void* Lremove(List lst, const void *data);
void Lfree(List lst, void (*cleanup)(void * data));
void* Lfront(List lst);
void* Lback(List lst);
Node Lfind_raw_node(List lst, const void *data);
size_t Lindex_of(List lst, const void *data);

#endif      // end of _LIST_H_ include guard
