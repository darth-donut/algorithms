#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "treeops.h"

static void *safe_malloc(size_t size);
static void *recursive_insert(Node root,
        int (*cmp)(void *, void *), Node key);
static void *recursive_search(Node root,
        int (*cmp) (void *, void *), void *key);
static void *recur_search_non_data(Node root,
        int  (*cmp) (void *, void *), void *key);
static void *recursive_smallest(Node root);
static void *recursive_largest(Node root);
static void *recursive_delete(Tree T, Node root,
        int (*cmp) (void *, void *), void *key);
static void recursive_traverse(Node node, void (*action)(void *));
static void recursive_free(Node node);

Tree
newTree(int (*cmp)(void *, void *)) {
    Tree T  = (Tree)safe_malloc(sizeof(*T));
    T->size = 0;
    T->root = NULL;
    T->cmp  = cmp;
    return T;
}

void
Tinsert(Tree T, void *key) {
    assert(T);
    Node new_node   = (Node)safe_malloc(sizeof(*new_node));
    new_node->data  = key;
    new_node->left  = new_node->right
                    = new_node->parent
                    = NULL;
    T->root         = recursive_insert(T->root, T->cmp, new_node);
    T->size         += 1;
}

void
*Tsearch(Tree T, void *key) {
    assert(T);
    return recursive_search(T->root, T->cmp, key);
}

void
*Tdelete(Tree T, void *key) {
    assert(T);
    void *data = recursive_delete(T, T->root, T->cmp, key);
    if (data)
        T->size -= 1;
    return data;
}

unsigned
Tsize(Tree T) {
    return T->size;
}

static void
*recursive_delete(Tree T, Node root, int (*cmp) (void *, void *), void *key) {
    Node buffer = recur_search_non_data(root, cmp, key),
         successor,
         parent;
    int right   = 0;
    if (!buffer)
        return NULL;
    /* found what you want to delete, buffer */
    parent      = buffer->parent; // record its parent;
    /* if buffer has right child, take the min of right, else take
     * the max of left if right child == NULL */
    if (buffer->right) {
        successor   = recursive_smallest(buffer->right);
        right       = 1;
    } else if (buffer->left)
        successor   = recursive_largest(buffer->left);
    else
        successor = NULL;

    /* if successor == null, then buffer is a leaf node, just remove it */
    if (!successor) {
        if (buffer->parent->left &&
                cmp(buffer->parent->left->data, key) == 0)
            buffer->parent->left    = NULL;
        else
            buffer->parent->right   = NULL;
        return buffer->data;
    }

    /* RESET SUCCESSOR'S OLD PARENTS
     * note: successor isn't necessarily a leaf,
     * hence rmb to assign their(successor's) children to their(successor's) parents,
     * if it's a leaf, then let it be null, else let it be the child of the successor */
    if (successor->parent->left &&
            cmp(successor->parent->left->data, successor->data) == 0)
        successor->parent->left     = right == 1? successor->right : successor->left;
    else
        successor->parent->right    = right == 1? successor->right : successor->left;

    /* RESET THE SUCCESSOR'S NEW PARENT AND CHILD */
    successor->parent   = parent;
    successor->left     = buffer->left;
    successor->right    = buffer->right;

    /* RESET THE DELETED NODE'S CHILDREN
     * let the deleted node's child know they have a new parent */
    if (buffer->left)
        buffer->left->parent  = successor;
    if (buffer->right)
        buffer->right->parent = successor;

    /* RESET THE DELETED NODE'S PARENT POINTER
     * st it is now pointing to the new successor */
    if (parent) {
        // parent is null if buffer/ deleted node was a root
        if (parent->left &&
                cmp(parent->left->data, key) == 0)
            parent->left    = successor;
        else
            parent->right   = successor;
    } else
        // T has a new root!
        T->root = successor;
    return buffer->data;
}

void
*Tsmallest(Tree T) {
    assert(T);
    return recursive_smallest(T->root);
}

void
*Tlargest(Tree T) {
    assert(T);
    return recursive_largest(T->root);
}

void
Ttraverse(Tree T, void (*action)(void *)) {
    assert(T);
    recursive_traverse(T->root, action);
}

void
Tfree(Tree T) {
    recursive_free(T->root);
    free(T);
}


static void
recursive_free(Node node) {
    if (node) {
        recursive_free(node->left);
        recursive_free(node->right);
        free(node);
    }
}

static void
recursive_traverse(Node node, void (*action)(void *)) {
    if (node) {
        recursive_traverse(node->left, action);
        action(node->data);
        recursive_traverse(node->right, action);
    }

}

static void
*recursive_largest(Node root) {
    if (root->right) {
        root = recursive_largest(root->right);
    }
    return root;
}

static void
*recursive_smallest(Node root) {
    if (root->left) {
        root = recursive_smallest(root->left);
    }
    return root;
}



static void
*recur_search_non_data(Node root, int  (*cmp) (void *, void *), void *key) {
    if (!root)
        return NULL;
    int outcome;
    if ((outcome = cmp(root->data, key)) < 0)
        return recur_search_non_data(root->right, cmp,  key);
    else if (outcome > 0)
        return recur_search_non_data(root->left, cmp,  key);
    else
        return root;
}

static void
*recursive_search(Node root, int (*cmp) (void *, void *), void *key) {
    if (!root)
        return NULL;
    int outcome;
    if ((outcome = cmp(key, root->data)) > 0)
        return recursive_search(root->right, cmp, key);
    else if (outcome < 0)
        return recursive_search(root->left, cmp, key);
    else
        return root->data;
}

static void
*recursive_insert(Node root, int (*cmp)(void *, void *), Node key) {
    if (!root)
        return key;
    else if (cmp(key->data, root->data) > 0)
        root->right = recursive_insert(root->right, cmp, key);
    else
        root->left  = recursive_insert(root->left, cmp, key);
    if (!key->parent)
        key->parent = root;
    return root;
}


static void
*safe_malloc(size_t size) {
    void *buffer    = malloc(size);
    assert(buffer && "Malloc failed");
    return buffer;
}
