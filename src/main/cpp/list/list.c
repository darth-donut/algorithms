#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "list.h"
#include "util.h"


List
Lnew(int (*cmp)(const void *, const void *)) {
    List lst = smalloc(sizeof(*lst) * 1);
    lst->cmp = cmp;
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
    return lst;
}

void
Lfree(List lst, void (*cleanup)(void * data)) {
    Node root = lst->head;
    Node prev;
    while (root) {
        if (cleanup)
            cleanup(root->data);
        prev = root;
        root = root->next;
        free(prev);
    }
    free(lst);
}

void
Linsert(List lst, const size_t index, void *data) {
    // create node and assign data
    Node node = smalloc(sizeof(*node));
    node->data = data;

    // CASE 1: trying to insert in head
    if (index == 0) {
        node->prev = NULL;
        if (lst->head) {
            // head's no longer head, it has a prev
            lst->head->prev = node;
        } else { // was empty list
            lst->tail = node;
        }
        node->next = lst->head;
        lst->head = node;
    } else {
        Node candidate = lst->head;

        if (candidate == NULL) {
            // SPECIAL CASE: empty list
            error_msg("Logic error: trying to add with index in an empty list", 1);
        } else {
            /* if we're here, it means we're supposed to add in the middle of the list, or by the tail,
             * depending on parameter index::size_t, raise error and exit as fatal otherwise */
            size_t i = 0;
            for (; candidate && i < index; ++i)
                candidate = candidate->next;
            if (i != index) {
                /* if we're here it means for loop failed with candidate == NULL but i != index
                 * It means user tried to insert at index past tail, exit as fatal */
                error_msg("Trying to insert past tail in list, fatal error", 1);
            } else if (candidate != NULL) {
                // CASE 2: trying to insert somewhere in the middle of the list

                // update prev node's next
                candidate->prev->next = node;
                // update new node's prev
                node->prev = candidate->prev;
                // update new node's next
                node->next = candidate;
                // update candidate's prev node
                candidate->prev = node;

            } else {
                // CASE 3: trying to insert in tail

                node->next = NULL;
                if (lst->tail) {
                    // old tail is no longer a tail, it has a next, i.e. new node
                    lst->tail->next = node;
                    node->prev = lst->tail;
                    lst->tail = node;
                } else {
                    lst->head = lst->tail = node;
                    node->prev = NULL;
                }
            }

        }
    }
    // increase list size by 1
    ++lst->size;
}

void *
Lfind(List lst, const void *data) {
    Node n;
    return (n = Lfind_raw_node(lst, data)) ? n->data : NULL;
}

void *
Lremove(List lst, const void *data) {
    Node node = Lfind_raw_node(lst, data);
    if (!node) return NULL;

    --lst->size;
    // update list's head and tail respectively
    if (lst->head && lst->cmp(lst->head->data, data) == 0) {
        lst->head = node->next;
        if (lst->head == NULL) {
            assert(lst->size == 0);
            lst->tail = NULL;
        }
    }
    if (lst->tail && lst->cmp(lst->tail->data, data) == 0) {
        lst->tail = node->prev;
    }

    assert(lst->tail != NULL || lst->size == 0);

    // update node's neighbours
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }

    // release resources
    void *out_data = node->data;
    free(node);

    // decrease size by 1
    return out_data;
}

void *
Lfront(List lst) {
    return lst->size == 0 ? NULL : Lremove(lst, lst->head->data);
}

void *
Lback(List lst) {
    return lst->size == 0 ? NULL : Lremove(lst, lst->tail->data);
}

Node
Lfind_raw_node(List lst, const void *data) {
    Node node = lst->head;
    while (node) {
        if (lst->cmp(node->data, data) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}


size_t
Lindex_of(List lst, const void *data) {
    Node node = lst->head;
    size_t index = 0;
    while (node) {
        if (lst->cmp(data, node->data) == 0) {
            return index;
        }
        node = node->next;
        ++index;
    }
    return SIZE_MAX;
}
