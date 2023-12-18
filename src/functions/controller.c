#include "../../include/theater.h"
#include "../../include/controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateParams(Theater t, int r, int c) {
    if (r > t.qtdRows || c > t.qtdColumns || r < 1 || c < 1) {
        return 0;
    }
    return 1;
}

void main_SaveSpecificSeat(Theater t) { 
    char *str = malloc(sizeof(char) * 100);
    int r, c, result, validation;
    Seat *s;
    char opc;

    printf("Você escolheu a opção 'Reservar Assento'.\n");
    printf("Digite seu primeiro nome: ");
    scanf("%s", str);
    getchar();
    printf("Digite o número da fileira e o número do assento desejada: ");
    scanf("%d %d", &r, &c);

    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inválidas. Insira uma fileira e um número de assento válidos: ");
        getchar();
        scanf("%d %d", &r, &c);
        validation = validateParams(t, r, c);
    }

    s = &(t.seats[r-1][c-1]);
    result = createReservation(t, r, c, str);
    if (result == 1) {
        printf("Reserva feita com sucesso no assento %c%d no nome de %s! \n", s->row, s->number, s->name);
    }
    else {
        printf("O assento não está disponível. Deseja cadastrar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        if (opc == 's') { main_SaveSpecificSeat(t); }
        else { return; }
    }
}

void main_CancelReservation(Theater t) {
    int r, c, result, validation;
    char opc;
    Seat *s;

    printf("Você escolheu a opção 'Cancelar Reserva'.\n");
    printf("Digite o número da fileira e a coluna do assento que você deseja cancelar a reserva: ");
    scanf("%d %d", &r, &c);

    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inválidas. Insira uma fileira e um número de assento válidos: ");
        getchar();
        scanf("%d %d", &r, &c);
        validation = validateParams(t, r, c);
    }

    s = &(t.seats[r-1][c-1]);
    result = cancelReservation(t, r, c);

    if (result == 0) { 
        printf("Não há reserva para esse assento. Deseja tentar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        if (opc == 's') { main_CancelReservation(t); }
        else { return; }
    } 
    else {
        printf("Caro cliente, sua reserva do assento %c%d foi cancelada com sucesso.\n", s->row, s->number);
    }
}

void main_View(Theater t) {
    printf("Estado atual do teatro com assentos livres e ocupados:\n");
    displayTheater(t);
}

void main_SaveStateOnFile(Theater t) {
    char *str = malloc(sizeof(char) * 54);
    int result;
    char opc;

    printf("Digite o nome do arquivo a salvar o teatro (até 50 caracteres): ");
    scanf("%s", str);
    strcat(str, ".txt");
    str[strlen(str)] = '\0';
    result = saveState(t, str);
    free(str);

    if (result == 1) {
        printf("Seus dados foram salvos com sucesso! \n");
    }
    else {
        printf("Não foi possível abrir o arquivo. Tentar novamente? (s/n) ");
        if(scanf("%c") == 's') { main_SaveStateOnFile(t); } 
        else { return; }
    }
}

void main_SaveMultipleSeats(Theater t) {
    char *str = malloc(sizeof(char) * 100);
    int r, c, x, result, validation;
    char opc;

    printf("Você escolheu a opção 'Reservar Assentos Consecutivos'.\n");
    printf("Digite seu primeiro nome: ");
    scanf("%s", str);
    str[strlen(str)] = '\0';
    getchar();
    printf("Digite quantos assentos desejará reservar: ");
    scanf("%d", &x);
    printf("Digite o número da fileira e o número do assento inicial: ");
    scanf("%d %d", &r, &c);

    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inválidas. Insira uma fileira e um número de assento válidos: ");
        scanf("%d %d", &r, &c);
        validation = validateParams(t, r, c);
    }

    result = createMultipleReservation(t, r, c, str, x);

    switch (result) {
        case -1:
            printf("Não há assentos suficientes disponíveis. Deseja reiniciar a operação? (s/n) ");
            scanf("%c", &opc);
            if (opc == 's') { main_SaveMultipleSeats(t); }
            break;
        case 0:
            printf("Não foi possível criar reserva em um dos assentos. Deseja reiniciar o processo? (s/n) ");
            scanf("%c", &opc);
            if (opc == 's') { main_SaveMultipleSeats(t); }
            break;
        case 1:
            printf("Os %d assentos escolhidos da fileira %c foram reservados com sucesso!\n");
            break;
        default:
            break;
    }     

}
