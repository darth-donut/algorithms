#include <stdlib.h>
#include "gcd.h"


void
exEuclid(int a, int b, int A[]) {
    if (b == 0) {
        A[X] = 1;
        A[Y] = 0;
        A[D] = a;
    } else {
        exEuclid(b, a%b, A);
        int tmp_x = A[X];
        A[X] = A[Y];
        A[Y] = tmp_x - (a/b)*A[Y];
    }
}
