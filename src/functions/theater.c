#include "../../include/entities.h"
#include "../../include/seats.h"
#include <stdlib.h>
#include <stdio.h>

Teatro criarTeatro(int l, int c) {
    Teatro t;
    t.assento = NULL;
    t.assento = inicializarMatriz(l, c);
    while (t.assento == NULL) {
        printf("Forneça uma entrada válida: ");
        scanf("%d %d", &l, &c);
        t.assento = inicializarMatriz(l, c);
    }
    t.linha = l; t.coluna = c;
    return t;
}