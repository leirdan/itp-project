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
    for (int i = 0; i < l; i++) {
        for (int k = 0; k < c; k++) {
            t.seats[i][k].reserved = 0;
            t.seats[i][k].row = (char) (i + 49);
            t.seats[i][k].number = k + 1;
        }
    }
    t.qtdRows = l; 
    t.qtdColumns = c;
    return t;
}

void displayTheater(Theater t) {
    Seat s;
    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            s = t.seats[i][k]; // Assento atual.

            if (s.reserved == 0) {
                printf("| ]%c%d[ |", s.row, s.number);
            } 
            else {
                printf(" | [%c%d] |", s.row, s.number);
            }
        }
        printf("\n"); 
    }
}

int createReservation(Theater t, int r, int c, char *n) {
    Seat s = t.seats[r][c];
    if (s.reserved == 0) {
        s.name = n;
        s.reserved = 1;
        return 1;
    }
    return 0;
}