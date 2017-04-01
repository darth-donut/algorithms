#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "list.h"
#include "process.h"
#include "ram.h"


void *
smalloc(const size_t n) {
    void *buffer = malloc(n);
    if (!buffer) {
        perror("Malloc failed, error: ");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void *
scalloc(const size_t nmemb, const size_t size) {
    void *buffer = calloc(nmemb, size);
    if (!buffer)  {
        perror("Calloc failed, error: ");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void *
srealloc(void *old, const size_t new_size) {
    void *buffer = realloc(old, new_size);
    if (!buffer) {
        perror("Realloc failed, error: ");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void
error_msg(const char *msg, int exit_b) {
    fprintf(ERR_CHN, "Error encountered: %s\n", msg);
    if (exit_b)
        exit(EXIT_FAILURE);
}

void
print_debug_pid(List lst, const char *msg) {
    puts(msg);
    Node n = lst->head;
    while(n) {
        printf("(%d)", ((Process)n->data)->pid);
        n = n->next;
        if (n) {
            printf("-");
        } else {
            printf("\n");
        }

    }
}

void
disp_ram(Ram ram) {
    Node n = ram->queue->head;
    while (n) {
        Process proc = n->data;
        if (Proc_is_null_proc(proc)) {
            printf("-(%d:%u)", proc->pid, proc->size);
        } else {
            printf("+(%d:%u)", proc->pid, proc->size);
        }
        n = n->next;
    }
    printf("\n");
}

void
print(unsigned time, int pid, unsigned num_procs, unsigned num_holes, unsigned mem_usage) {
    printf("time %u, %d loaded, numprocesses=%u, numholes=%u, memusage=%u%%\n", time, pid,
           num_procs, num_holes, mem_usage);
}

void
assert_100(Ram ram) {
    // asserts 100% ram usage (holes + processes)
    unsigned sum = 0;
    Node n = ram->queue->head;
    while (n) {
        sum += ((Process)n->data)->size;
        n = n->next;
    }
    if (sum != ram->ram_limit) {
        error_msg("Expected ram to sum to ram_limit, but that's not the case, logic error!", 1);
    }
    assert(sum == ram->ram_limit);
}
