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
            t.seats[i][k].name = "null";
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
        s->name = n;
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
        s->name = "null";
        s->reserved = 0;
        return 1;
    }
    return 0; 
}

int saveState(Theater t, char *file){
    Seat s;
    FILE *archive = fopen(file, "w");
    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fprintf(archive, "%d\n", t.qtdRows);
    fprintf(archive, "%d\n", t.qtdColumns);

    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            s = t.seats[i][k];
            fprintf(archive, "%c\n", s.row);
            fprintf(archive, "%d\n", s.number);
            fprintf(archive, "%s\n", s.name);
        }
    }
    fclose(archive);
    return 1;
}

int createMultipleReservation(Theater t, int r, int c, char *n, int x) {
    int result, check = checkSeatsInline(t, r, c, x);

    if (check == 0) {
        // Não há disponibilidade de assentos.
        return -1;
    }
    else {
        // Há disponibilidade de assentos.
        for (int i = 0; i < x; i++) {
            result = createReservation(t, r, c, n);
            if (result == 0) {
                // Algo errado aconteceu.
                return 0;
            }
            c++;
        }
        return 1;
    }
}

int checkSeatsInline(Theater t, int r, int c, int x) {
    for (int i = 0; i < x; i++) {
        if(isSeatFree(t, r-1, c-1) == 0) {
            return 0;
        }
        c++; // Avança para a próxima coluna.
    }
    return 1;
}