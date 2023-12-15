#include "../../include/entities.h"
#include <stdlib.h>

Assento **inicializarMatriz(int l, int c) {
    if (l > 26 || c > 99) {
        return NULL;
    } else {
        // Aloca espaço para as linhas.
        Assento **a = (Assento **) malloc(sizeof(Assento *) * l);

        for (int i = 0; i < l; i++) {
            // Aloca espaço para as colunas.
            a[i] = (Assento *) malloc(sizeof(Assento) * c);
        }
        return a;
    }
}