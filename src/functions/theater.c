#include "../../include/entities.h"
#include "../../include/seats.h"
#include <stdlib.h>
#include <stdio.h>

Theater createTheater(int l, int c) {
    Theater t;
    t.seats = NULL;
    t.seats = initiliazeMatrix(l, c);
    while (t.seats == NULL) {
        printf("Forneça uma entrada válida: ");
        scanf("%d %d", &l, &c);
        t.seats = initiliazeMatrix(l, c);
    }
    t.qtdRows = l; t.qtdColumns = c;
    return t;
}