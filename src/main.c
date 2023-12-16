#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/seats.h"
#include "../include/theater.h"

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
            case 0: // Criar Teatro
                break;
            case 1: // Reservar Assento
                char *s;
                int r, c;
                printf("Você escolheu a opção 'Reservar Assento'. Digite seu nome, o número da fileira e o número da cadeira.");
                fgets(s, 99, stdin);
                scanf("%d %d", &r, &c);
                createReservation(t, r, c, s);
                break;
            case 2: // Exibir Teatro
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

void startup(int op) {

}