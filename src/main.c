#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/seats.h"
#include "../include/theater.h"
#include "../include/controller.h"

void printOperations();

void redirect();

int main(int argc, char *argv[]) { 
    int f, n, op = 1, c = 0;
    int *operations = malloc(sizeof(int));

    system("clear");
    printf("Seja bem vindo!\n");
    printf("Por favor, informe a quantidade de fileiras e número de cadeiras por fileira de seu teatro: ");
    scanf("%d %d", &f, &n);
    
    Theater t = createTheater(f, n);
    
    system("sleep 1");

    while(op != 0) {
        system("clear");
        printOperations();
        scanf("%d", &op);
        switch(op) {
            case 0: // Sair do Programa
                printf("Volte sempre!\n");
                break;
            case 1: // Salvar estado
                main_SaveStateOnFile(t);
                redirect();
                break;
            case 2: // Carregar estado
                break;
            case 3: // Exibir Teatro
                main_View(t);
                redirect();
                break;
            case 4: // Reservar Assento
                main_View(t);
                main_SaveSpecificSeat(t);
                redirect();
                break;
            case 5: // Reservar Assentos Consecutivos
                main_SaveMultipleSeats(t);
                redirect();
                break;
            case 8: // Cancelar reserva de um assento
                main_CancelReservation(t);
                redirect();
                break;
            default:
                break;
        }
    }

    deallocateMatrix(t.seats, t.qtdRows);
    free(operations);

    return 0;
}

void printOperations() {
    printf("Escolha uma das operações abaixo:\n");
    printf("00 | Sair do Programa\n");
    printf("01 | Salvar Estado\n");
    printf("02 | Carregar Estado\n");
    printf("03 | Exibir Teatro\n");
    printf("04 | Reservar Assento\n");
    printf("05 | Reservar Assentos Consecutivos\n");
    printf("08 | Cancelar Reserva\n");
}

void redirect() {
    printf("Redirecionando...\n");
    system("sleep 3");
}