#include "../../include/entities.h"
#include "../../include/seats.h"
#include <stdlib.h>

Teatro criarTeatro(int l, int c) {
    Teatro *t;
    t->assento = inicializarMatriz(l, c);
    t->linha = l; t->coluna = c;
    
    return *t;
}
