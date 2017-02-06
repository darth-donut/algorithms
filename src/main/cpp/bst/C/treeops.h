#ifndef _TREEOPS_H_
#define _TREEOPS_H_

typedef struct node_t* Node;
typedef struct tree_t* Tree;

struct node_t {
    Node    parent;
    Node    left;
    Node    right;
    void    *data;
};


struct tree_t {
    Node        root;
    int         (*cmp) (void *, void *);
    unsigned    size;
};

/* returns a new empty tree O(1) */
Tree newTree(int (*cmp)(void *, void *));

/* inserts an item into the tree O(logn)*/
void Tinsert(Tree T, void *key);

/* searches an item in the tree O(logn)*/
void *Tsearch(Tree T, void *key);

/* deletes an item in the tree O(logn)*/
void *Tdelete(Tree T, void *key);

/* finds the smallest item in the tree O(logn) */
void *Tsmallest(Tree T);

/* finds the largest item in the tree O(logn) */
void *Tlargest(Tree T);

/* traverse the tree with action applied to each item in the tree
 * action can be: printing, freeing, mallocing, comparing and other
 * operations on the data directly O(n) */
void Ttraverse(Tree T, void (*action)(void *));

/* frees the tree O(log n) */
void Tfree(Tree T);

/* returns the size of the tree currently, O(1) */
unsigned Tsize(Tree T);

#endif
