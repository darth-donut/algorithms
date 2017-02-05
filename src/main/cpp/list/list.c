#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

static void *smalloc(size_t size);
static void foldl(Node n, void (*action) (void *), void (*action2)(void *));
static void foldr(Node n, void (*action) (void *), void (*action2)(void *));
static void *find(Node n, void *key, int (*cmp) (void *, void *));

List
Lcreate(void) {
    List L = smalloc(sizeof(*L));
    assert(L);
    L-> head    = NULL;
    L-> tail    = NULL;
    L-> size    =    0;
    return L;
}


/* a push to the head
 * can create a list by calling Linsert(NULL, data)*/
List
Lpush(List L, void *data) {
    if (!L)
        L = Lcreate();

    Node n  = (Node)smalloc(sizeof(*n));
    n->data = data;
    n->next = L->head;
    n->prev = NULL;
    if (!L->tail)
        L->tail       = n;
    else
        L->head->prev = n;

    L->head = n;
    L->size++;
    return L;
}


/* appending to tail of list
 * also can create by calling Lappend(NULL, data) */
List
Lappend(List L, void *data) {
    if (!L)
        L = Lcreate();

    Node n          = (Node)smalloc(sizeof(*n));
    n->data         = data;
    n->next         = NULL;
    n->prev         = L->tail;

    if (!L->tail)
        L->head         = n;
    else
        L->tail->next   = n;
    L->tail             = n;
    L->size++;
    return L;
}


/* deletes the last item out of the list */
void
*Lpop(List L) {
    assert(L && "Empty list provided");
    Node buff           = L->tail;
    assert(buff);
    void *data          = buff->data;
    L->tail             = buff->prev;
    if (!L->tail)
        L->head         = NULL;
    else
        L->tail->next   = NULL;
    L->size--;
    free(buff);
    return data;
}

void
*Ldequeue(List L) {
    assert(L && "Empty list provided");
    Node buff           = L->head;
    assert(buff);
    void *data          = buff->data;
    L->head             = buff->next;
    if (!L->head)
        L->tail         = NULL;
    else
        L->head->prev   = NULL;
    free(buff);
    L->size--;
    return data;
}

void
Lfree(List L) {
    foldl(L->head, NULL, free);
    free(L);
}

uint
Lsize(List L) {
    assert(L && "Empty list provided");
    return L->size;
}


void
Ltraversel(List L, void (*action) (void *)) {
    foldl(L->head, action, NULL);
}

void
Ltraverser(List L, void (*action) (void *)) {
    foldr(L->tail, action, NULL);
}

void
*Lfind(List L, void *key, int (*cmp) (void *, void *)) {
    assert(L && "Empty list provided");
    Node n;
    return (n = find(L->head, key, cmp))
        ? n->data
        : NULL;

}

void
*Ldel(List L, void *key, int (*cmp) (void *, void *)) {
    Node n      = find(L->head, key, cmp);
    void *data  = n ? n->data : NULL;
    if (n) {

        if (n->prev)
            n->prev->next = n->next;
        else
            L->head       = n->next;

        if (n->next)
            n->next->prev = n->prev;
        else
            L->tail       = n->prev;

        L->size--;
    }
    return data;
}


static void
foldr(Node n, void (*action) (void *), void (*action2)(void *)) {
    if (n) {
        Node node = n;
        if (action) action(n->data);
        if (action2) action2(n);
        foldr(node->prev, action, action2);
    }
}
static void
foldl(Node n, void (*action) (void *), void (*action2)(void *)) {
    if (n) {
        Node node = n;
        if (action) action(n->data);
        if (action2) action2(n);
        foldl(node->next, action, action2);
    }

}

static void
*find(Node n, void *key, int (*cmp) (void *, void *)) {
    return !n
        ? NULL
        : cmp(n->data, key) == 0
            ? n
            : find(n->next, key, cmp);
}

static void
*smalloc(size_t size) {
    void *buffer = malloc(size);
    assert(buffer && "Malloc failed");
    return buffer;
}

