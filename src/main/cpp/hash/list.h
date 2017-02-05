#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_t* List;
typedef struct node_t* Node;
typedef unsigned       uint;


struct node_t {
    Node  prev;
    Node  next;
    void *data;
};



struct list_t {
    Node    head;
    Node    tail;
    uint    size;
};

/* creates an empty list */
List Lcreate(void);
/* pops the first item out of list */
void *Lpop(List L);
/* deletes the last item out of list */
void *Ldequeue(List L);
/* appends item to tail of list */
List Lappend(List L, void *data);
/* pushes item to head of list */
List Lpush(List L, void *data);
/* returns size of list */
uint Lsize(List L);
/* deletes item from List, also returns item, NULL if not found */
void *Ldel(List L, void *key, int (*cmp) (void *, void *));
/* returns item, null otherwise */
void *Lfind(List L, void *key, int (*cmp) (void *, void *));
/* allows an action to be called on data from right to left of list */
void Ltraverser(List L, void (*action) (void *));
/* allows an action to be called on data from left to right of list */
void Ltraversel(List L, void (*action) (void *));
/* frees the list */
void Lfree(List L);

#endif
