#include "../../include/entities.h"
#include "../../include/seats.h"
#include "../../include/theater.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Theater createTheater(int l, int c) {
    Theater t;
    char row;
    t.seats = NULL;
    t.seats = initiliazeMatrix(l, c);
    while (t.seats == NULL) {
        printf("Forneça uma entrada válida: ");
        scanf("%d %d", &l, &c);
        t.seats = initiliazeMatrix(l, c);
    }
    for (int i = 0; i < l; i++) {
        for (int k = 0; k < c; k++) {
            row = 'A' + i;
            t.seats[i][k].reserved = 0;
            t.seats[i][k].row = row;
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

            if (s.number == 1) { 
                if (s.reserved == 0) {
                    printf("| ]%c%d[ ", s.row, s.number);
                } 
                else {
                    printf("| [%c%d] ", s.row, s.number);
                }
            }
            else if (s.number == t.qtdColumns) {
                 if (s.reserved == 0) {
                    printf("| ]%c%d[ | ", s.row, s.number);
                } 
                else {
                    printf("| [%c%d] | ", s.row, s.number);
                }
            }
            else {
                if (s.reserved == 0) {
                    printf("| ]%c%d[ ", s.row, s.number);
                } 
                else {
                    printf("| [%c%d] ", s.row, s.number);
                }    
            }
        }
        printf("\n"); 
    }
}

int createReservation(Theater t, int r, int c, char *n) {
    Seat *s = &(t.seats[r-1][c-1]);
    if (isSeatFree(t, r-1, c-1) == 1){
        s->name = strdup(n);
        s->reserved = 1;
        return 1;
    }
    return 0;
}

int isSeatFree(Theater t, int r, int c) {
    if (t.seats[r][c].reserved == 0) {
        return 1;
    }
    return 0;
}

int cancelReservation(Theater t, int r, int c){
    Seat *s = &(t.seats[r-1][c-1]);
    if (isSeatFree(t, r-1, c-1) == 0){
        s->name = "";
        s->reserved = 0;
        return 1;
    }
    return 0; 
}

int saveState(Theater t, char *argv){
    Seat s;
    FILE *archive = fopen(argv, "w");
    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    // {colocar diretório dps}
    }

    fprintf(archive, "%d\n", t.qtdRows);
    fprintf(archive, "%d\n", t.qtdColumns);

    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            s = t.seats[i][k];
            fprintf(archive, "%c\n", s.row);
            fprintf(archive, "%d\n", s.number);
            fprintf(archive, "%s\n", s.name);
            fprintf(archive, "%d\n", s.reserved);
        }
    }
    fclose(archive);
    return 0;
}
