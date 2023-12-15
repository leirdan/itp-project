#include "../../include/entities.h"
#include <stdlib.h>

Seat **initiliazeMatrix(int l, int c) {
    if (l > 26 || c > 99) {
        return NULL;
    } else {
        // Aloca espaço para as linhas.
        Seat **a = (Seat **) malloc(sizeof(Seat *) * l);

        for (int i = 0; i < l; i++) {
            // Aloca espaço para as colunas.
            a[i] = (Seat *) malloc(sizeof(Seat) * c);
        }
        return a;
    }
}