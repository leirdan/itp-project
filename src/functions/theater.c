#include "../../include/entities.h"
#include "../../include/seats.h"
#include "../../include/theater.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

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
                    printf("]%c%d[ ", s.row, s.number);
                } 
                else {
                    printf("[%c%d] ", s.row, s.number);
                }
            }
            else if (s.number == t.qtdColumns) {
                 if (s.reserved == 0) {
                    printf("]%c%d[ ", s.row, s.number);
                } 
                else {
                    printf("[%c%d] ", s.row, s.number);
                }
            }
            else {
                if (s.reserved == 0) {
                    printf("]%c%d[ ", s.row, s.number);
                } 
                else {
                    printf("[%c%d] ", s.row, s.number);
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


Seat *saveAutomaticSeat(Theater t, char *n) {
    Seat *s = NULL;
    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            if (isSeatFree(t, i, k) == 1) {
                s = &(t.seats[i][k]);
                s->name = n;
                s->reserved = 1;
                return s;
            }
        }
    }
}

Seat ** saveAutomaticMultipleSeat(Theater t, int x, char *n) {
    Seat **seats = malloc(sizeof(Seat *) * x);
    int result, index = 0;
    
    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            // Se o assento estiver vazio
            if (isSeatFree(t, i, k) == 1) {
                // Se os pr ximos 'x' assentos estiverem vazios
                if (checkSeatsInline(t, i+1, k+1, x) == 1) {
                    // Cadastre w reservas
                    for (int w = 0; w < x; w++) {
                        result = createReservation(t, i+1, k+w+1, n);
                        seats[index++] = &(t.seats[i][k+w]);
                    }
                    return seats;
                }
                else {
                    continue;
                }
            }
            else { continue; }

        }
    }

    return NULL;
}

int isSeatFree(Theater t, int r, int c) {
    if (t.seats[r][c].reserved == 0 && (r < t.qtdRows && c < t.qtdColumns)) {
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

int cancelMultipleReservations(Theater t, char *n) {
    int check, result, counter = 0;
    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {

            if (isSeatFree(t, i, k) == 0) {
               check = strcmp(n, t.seats[i][k].name);
               if (check == 0) { 
                // Incremento em 1 para que o n mero da fileira e da poltrona sejam passados, e n o seus  ndices e evitar erros.
                    result = cancelReservation(t, i + 1, k + 1);
                    if (result == 1) { counter++; }
                }
                else { continue; }
            }
            else { continue; }

        }
    }
    return counter;
}

int saveState(Theater t, char *argv){
    Seat s;
    FILE *archive = fopen(argv, "w");
    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fprintf(archive, "%d\n", t.qtdRows);
    fprintf(archive, "%d\n", t.qtdColumns);

    createTheater(t.qtdRows, t.qtdColumns);

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
    return 1;
}

Theater loadState(char *file){
    Theater t;

    t.seats = NULL;
    t.qtdRows = 0;
    t.qtdColumns = 0;

    char name[50];

    FILE *archive = fopen(file, "r");

    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return t;
    }

    fscanf(archive, "%d\n", &t.qtdRows);
    fscanf(archive, "%d\n", &t.qtdColumns);

    t.seats = initiliazeMatrix(t.qtdRows, t.qtdColumns);

    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            fscanf(archive, "%c\n", &t.seats[i][k].row);
            fscanf(archive, "%d\n", &t.seats[i][k].number);
            fscanf(archive, "%s\n", &t.seats[i][k].name);
            fscanf(archive, "%d\n", &t.seats[i][k].reserved);
        }
    }

    displayTheater(t);

    fclose(archive);

    return t;
}


int createMultipleReservation(Theater t, int r, int c, char *n, int x) {
    int result, check = checkSeatsInline(t, r, c, x);

    if (check == 0) {
        // N o h  disponibilidade de assentos.
        return -1;
    }
    else {
        // H  disponibilidade de assentos.
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
        c++; // Avan a para a pr xima coluna.
    }
    return 1;
}

int cancelAllReservations(Theater t) {
    int c = 0;

    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            if (isSeatFree(t, i, k) == 0) {
                cancelReservation(t, i + 1, k + 1);
                c++;
            }
        }
    }
    return c;
}

void seeConsecutiveSeats(Theater t, int n) {
    for (int i = 0; i < t.qtdRows; i++) {
        int count = 0;
        for (int k = 0; k < t.qtdColumns; k++) {
            if (isSeatFree(t, i, k)) {
                count++;
                if (count == n) {
                    printf("Há pelo menos %d assentos consecutivos disponíveis na fileira %c, começando no assento %d.\n", n, t.seats[i][k - n + 1].row, t.seats[i][k - n + 1].number);
                    break;
                }
            } else {
                count = 0;
            }
        }
    }
}