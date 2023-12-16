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
    printf("01 | Reservar Assento\n");
    printf("02 | Exibir Teatro\n");
    
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
            case 1: // Reservar Assento
                saveSpecificSeat(t);
                break;
            case 2: // Exibir Teatro
                printf("Esse é o estado atual do teatro: \n");
                displayTheater(t);
                break;
            default:
                break;
        }
    }

    free(t.seats);
    free(operations);

    return 0;
}