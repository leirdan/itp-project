#include "../../include/theater.h"
#include "../../include/controller.h"
#include <stdio.h>
#include <stdlib.h>

void saveSpecificSeat(Theater t) { 
    char *s = malloc(sizeof(char) * 100);
    int r, c, result;
    char opc;

    printf("Você escolheu a opção 'Reservar Assento'. Digite seu primeiro nome, o número da fileira e o número da cadeira: ");
    scanf("%s", s);
    getchar();
    scanf("%d %d", &r, &c);
    result = createReservation(t, r, c, s);
    if (result == 1) {
        printf("Reserva feita com sucesso no assento %c%d no nome de %s \n",  t.seats[r-1][c-1].row,  t.seats[r-1][c-1].number, t.seats[r-1][c-1].name);
    }
    else {
        printf("O assento não está disponível. Deseja cadastrar novamente? (s/n) \n");
        getchar();
        scanf("%c", &opc);
        if (opc == 's') { saveSpecificSeat(t); }
        else { return; }
    }
}
