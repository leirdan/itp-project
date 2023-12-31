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
                // Se os próximos 'x' assentos estiverem vazios
                if (checkSeatsInline(t, i+1, k+1, x) == 1) {
                    // Cadastre w reservas
                    for (int w = 0; w < x; w++) {
                        result = createReservation(t, i+1, k+w+1, n);
                        seats[index++] = &(t.seats[i][k+w]);
                    }
                    return seats;
                }
            }
            else { continue; }

        }
    }

    return NULL;
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

int cancelMultipleReservations(Theater t, char *n) {
    int check, result, counter = 0;
    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {

            if (isSeatFree(t, i, k) == 0) {
               check = strcmp(n, t.seats[i][k].name);
               if (check == 0) { 
                // Incremento em 1 para que o número da fileira e da poltrona sejam passados, e não seus índices e evitar erros.
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

    createTheater(t.qtdRows, t.qtdRows);

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

Theater loadState(char *file){
    Theater t;
    char *name = malloc(sizeof(char) * 99);
    Seat *s;

    FILE *archive = fopen(file, "r");

    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        fclose(archive);
        return t;
    }

    fscanf(archive, "%d", &t.qtdRows);
    fscanf(archive, "%d", &t.qtdColumns);

    t.seats = initiliazeMatrix(t.qtdRows, t.qtdColumns);

    for (int i = 0; i < t.qtdRows; i++) {
        for (int k = 0; k < t.qtdColumns; k++) {
            // ALOCAR OS DADOS PARA T.SEATS
            s = &(t.seats[i][k]);
            fscanf(archive, "%c\n", s->row);
            fscanf(archive, "%d\n", s->number);
            fscanf(archive, "%s\n", name);
            if (strcmp(name, "null") != 0) {
                s->name = name;
                s->reserved = 1;
            }
            else {
                s->name = "null";
                s->reserved = 0;
            }
        }
    }

    fclose(archive);

    return t;
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