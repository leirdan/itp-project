#include "../../include/entities.h"
#include <stdlib.h>

Seat **initiliazeMatrix(int l, int c) {
    if ((l > 26 || l == 0) || (c > 99 || c ==0)) {
        return NULL;
    } else {
        Seat **a = (Seat **) calloc(l, sizeof(Seat *) * l); // Aloca espaço para as linhas.

        for (int i = 0; i < l; i++) {
            a[i] = (Seat *) calloc(c, sizeof(Seat) * c); // Aloca espaço para as colunas.
        }
        return a;
    }
}

void deallocateMatrix(Seat **a, int r) {
    for (int i = 0; i < r; i++) {
        free(a[i]);
    }
    free(a);
}