#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/seats.h"
#include "../include/theater.h"

void startup_2(Theater t);

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
    
    // [1, 3, 2, 2, 3, ..., 0]
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
                startup_2(t);
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

void startup_2(Theater t) {
    char *s = malloc(sizeof(char) * 100);
    int r, c, result, opc = 1;

    while(opc == 1) {
        printf("Você escolheu a opção 'Reservar Assento'. Digite seu primeiro nome, o número da fileira e o número da cadeira: ");
        scanf("%s", s);
        getchar();
        scanf("%d %d", &r, &c);
        result = createReservation(t, r, c, s);
        if (result == 1) {
            // printf("Reserva feita com sucesso no assento %c%d no nome de %s \n").
            opc = 0;
        }
        else {
            printf("O assento não está disponível. Deseja cadastrar novamente? \n");
            scanf("%d", opc);
        }
    }
}