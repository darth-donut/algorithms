#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "treeops.h"
#include "input.h"

#define STREAM_IN   stdin
#define STREAM_OUT  stdout
#define INITSIZE    10         /* initial size for string buffer */

typedef struct word_t* Word;

struct word_t {
    int     freq;
    char    *str;
};

int cmp(void *aa, void *bb);
void *smalloc(size_t size);
void print_then_free(void *aa);
void print_only(void *aa);

int
main(int argc, char *argv[]) {
    argc+= 0;       // silence harmless alert
    FILE *fp        = argv[1]? fopen(argv[1], "r"): STREAM_IN;
    Tree T          = newTree(cmp);
    int  bufflen,
         size       = INITSIZE;
    char *buffer    = smalloc(sizeof(*buffer)*INITSIZE);
    Word word, locn;

    /* grab each word, if it doesn't exist in the BST, add it
     * increase freq count otherwise */
    while ((bufflen = get_word(fp, &buffer, &size)) != EOF) {
        word        = smalloc(sizeof(*word)) ;
        word->str   = buffer;
        if ((locn = Tsearch(T, word)) == NULL) {
            word->str   = smalloc((bufflen+1)*sizeof(char));
            word->freq  = 1;
            strcpy(word->str, buffer);
            Tinsert(T, word);
        } else {
            locn->freq += 1;
            free(word);
        }
    }
    /*
     * word        = smalloc(sizeof(*word));
     * word->str   = smalloc(10);
     * strcpy(word->str, "The");
     * Tdelete(T, word);
     * strcpy(word->str, "the");
     * Tdelete(T, word);
     * strcpy(word->str, "a");
     * Tdelete(T, word);
     * strcpy(word->str, "A");
     * Tdelete(T, word);
     */

    Ttraverse(T, print_then_free);
    Tfree(T);
    free(buffer);
    free(word);
    return 0;
}


void
print_only(void *aa) {
    Word word = aa;
    fprintf(STREAM_OUT, "%15s %8d\n", word->str, word->freq);

}

void
print_then_free(void *aa) {
    Word word = aa;
    fprintf(STREAM_OUT, "%8d %15s \n", word->freq, word->str);
    free(word->str);
}

int
cmp(void *aa, void *bb) {
    return strcmp(((Word)aa)->str, ((Word)bb)->str);
}


void
*smalloc(size_t size) {
    void *buffer = malloc(size);
    assert(buffer);
    return buffer;
}
