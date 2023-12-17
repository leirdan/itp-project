#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/seats.h"
#include "../include/theater.h"
#include "../include/controller.h"

int main(int argc, char *argv[]) { 
    int f, n, op = 1, c = 0;
    int *operations = malloc(sizeof(int));

    printf("Seja bem vindo! ");
    printf("Por favor, informe a quantidade de fileiras e número de cadeiras por fileira de seu teatro: ");
    scanf("%d %d", &f, &n);
    
    Theater t = createTheater(f, n);

    printf("Quais operações deseja realizar? Veja a lista abaixo:\n");
    printf("00 | Sair do Programa\n");
    printf("01 | Salvar Estado\n");
    printf("02 | Carregar Estado\n");
    printf("03 | Exibir Teatro\n");
    printf("04 | Reservar Assento\n");
    printf("08 | Cancelar Reserva\n");
    
    while(op != 0) {
        scanf("%d", &op);
        operations[c] = op; 
        c++;
        operations = (int *) realloc(operations, sizeof(int) + 1);
    }

    for (int i = 0; i < c; i++) {
        op = operations[i];
        switch(op) {
            case 0: // Sair do Programa
                printf("Volte sempre!\n");
                break;
            case 1: // Salvar estado
                break;
            case 2: // Carregar estado
                break;
            case 3: // Exibir Teatro
                main_View(t);
                break;
            case 4: // Reservar Assento
                main_SaveSpecificSeat(t);
                break;
            case 5:
                break;
            case 8: // Cancelar reserva de um assento
                main_CancelateReservation(t);
                break;
            default:
                break;
        }
    }

    free(t.seats);
    free(operations);

    return 0;
}