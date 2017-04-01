#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "input.h"

static void *srealloc(void *buffer, size_t size);

int
get_word(FILE *fp, char **buffer, int *size) {
    int ch, i=0;
    while ((ch = getc(fp)) != EOF &&
            (isalpha(ch) || (ch == '\'' && i > 0))) {
        if (i >= *size-1) {
            *size *= 2;
            (*buffer) = (char *)srealloc(*buffer, sizeof(**buffer)*(*size));
        }
        (*buffer)[i++] = ch;
    }
    (*buffer)[i++] = '\0';
    return ch == EOF ? EOF : i;
}



static void
*srealloc(void *buffer, size_t size) {
    assert(buffer);
    buffer = realloc(buffer, size);
    assert(buffer);
    return buffer;
}
