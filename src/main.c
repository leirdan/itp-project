#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include "../include/seats.h"
#include "../include/theater.h"
#include "../include/controller.h"

void printOperations();

void redirect();

int main(int argc, char *argv[]) { 

    setlocale(LC_ALL, "Portuguese_Brazil");

    int f, n, op = 1;

    system("cls");
    printf("Seja bem vindo!\n");
    printf("Por favor, informe a quantidade de fileiras e número de cadeiras por fileira de seu teatro: ");
    scanf("%d %d", &f, &n);
    
    Theater t = createTheater(f, n);
    
    system("sleep 1");

    while(op != 0) {
        system("cls");
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
                t = main_LoadState(t);
                redirect();
                break;
            case 3: // Exibir teatro
                main_View(t);
                redirect();
                break;
            case 4: // Reservar assento
                main_View(t);
                main_SaveSpecificSeat(t);
                redirect();
                break;
            case 5: // Reservar assentos consecutivos
                main_View(t);
                main_SaveMultipleSeats(t);
                redirect();
                break;
            case 6: // Reservar assentos pelo sistema
                main_View(t);
                main_SaveSpecificSeatThroughSystem(t);
                redirect();
                break;
            case 7: // Reservar assentos consecutivos pelo sistema
                main_View(t);
                main_SaveMultipleSeatsThroughSystem(t);
                redirect();
                break;
            case 8: // Cancelar reserva de um assento
                main_View(t);
                main_CancelReservation(t);
                redirect();
                break;
            case 9: // Cancelar todas as reservas para uma mesma pessoa
                main_View(t);
                main_CancelMultipleReservations(t);
                redirect();
                break;
            case 10: // Cancelar todas as reservas
                main_View(t);
                main_CancelAllReservations(t);
                redirect();
                break;
            case 11: // Verificar um assento específico
                main_CheckSeat(t);
                redirect();
                break;
            case 12: // Consultar assentos consecutivos
                main_View(t);
                main_seeConsecutiveSeats(t);
                redirect();
            default:
                break;
        }
    }

    deallocateMatrix(t.seats, t.qtdRows);

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
    printf("06 | Reservar Assento pelo Sistema\n");
    printf("07 | Reservar Assentos Consecutivos pelo Sistema\n");
    printf("08 | Cancelar Reserva\n");
    printf("09 | Cancelar Reservas de uma Pessoa\n");
    printf("10 | Cancelar Todas as Reservas\n");
    printf("11 | Verificar Disponibilidade\n");
    printf("12 | Consultar Assentos Consecutivos\n");
}

void redirect() {
    printf("Pressione qualquer tecla para retornar ao menu\n");
    // getch();
    system("cls");
}