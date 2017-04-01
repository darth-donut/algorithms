#include <stdio.h>
#include <assert.h>



#include "list.h"
#include "hashops.h"

int cmp(void *aa, void *bb);
void print(void *data);

int
main() {
    int A[] = {
        1,2,3,4,5,6,7,8,9,10
    };
    int n = sizeof(A)/sizeof(*A);
    List L = NULL;
    for (int i = 0; i < n; i++) {
        L = Lpush(L, A+i);
        L = Lappend(L, A+i);
    }

    printf("%d items inserted\n", Lsize(L));
    Ltraversel(L, print);
    printf("\n");

    printf("pop first item\n");
    Lpop(L);
    printf("%d items inserted\n", Lsize(L));
    printf("\n");

    printf("Traverse right\n");
    Ltraverser(L, print);
    printf("\n");

    printf("Traverse left\n");
    Ltraversel(L, print);
    printf("\n");

    printf("delete 5\n");
    assert(*(int *)Ldel(L, A+4, cmp) == 5);
    Ltraversel(L, print);
    printf("\n");

    printf("find 2 :");
    printf("%d\n", *(int *)Lfind(L, A+1, cmp));

    printf("dequeue\n");
    Ldequeue(L);
    Ltraversel(L, print);
    printf("\n");

    printf("dequeue\n");
    Ldequeue(L);
    Ltraversel(L, print);
    printf("\n");


    Lfree(L);

    Hash H = Hcreate(10, DOUBLE, cmp);
    Hinsert(H, "Apples");
    Hinsert(H, "Apples");
    Hinsert(H, "Apples");
    Hinsert(H, "Ringo");
    Hinsert(H, "Epal");
    Hinsert(H, "ping guo");
    printf("searching for \"Apples\": %s\n", (char *)Hsearch(H, "Apples"));


    return 0;
}


int
cmp(void *aa, void *bb) {
    return (*(int *)aa - *(int *)bb);
}

void
print(void *data) {
    printf("%d ", *(int *)data);
}
