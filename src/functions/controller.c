#include "../../include/theater.h"
#include "../../include/controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateParams(Theater t, int r, int c) {
    if (r > t.qtdRows || c > t.qtdColumns) {
        return 0;
    }
    return 1;
}

void main_SaveSpecificSeat(Theater t) { 
    char *str = malloc(sizeof(char) * 100);
    int r, c, result, validation;
    Seat *s;
    char opc;

    printf("Você escolheu a opção 'Reservar Assento'.\nDigite seu primeiro nome, o número da fileira e o número da cadeira: ");
    scanf("%s", str);
    getchar();
    scanf("%d %d", &r, &c);
    // se os números forem maiores que o número de colunas/fileiras, tratar isso!
    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inválidas. Insira uma fileira e um número de cadeira válidos: ");
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

void main_CancelateReservation(Theater t) {
    int r, c, result;
    char opc;
    Seat *s;

    printf("Você escolheu a opção 'Cancelar Reserva'.\nDigite o número da fileira e a coluna do assento que você deseja cancelar a reserva: ");
    scanf("%d %d", &r, &c);
    s = &(t.seats[r-1][c-1]);
    result = cancelReservation(t, r, c);
    if (result == 0) { 
        printf("Houve um problema no cancelamento. Deseja tentar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        if (opc == 's') { main_CancelateReservation(t); }
        else { 
            printf("Reserva do assento %c%d não foi cancelada. \n", s->row, s->number);
            return; 
        }
    } 
    else {
        printf("Caro cliente, sua reserva do assento %c%d foi cancelada com sucesso.\n", s->row, s->number);
    }
}

void main_View(Theater t) {
    printf("Estado atual do teatro com assentos livres e ocupados:\n");
    displayTheater(t);
}

void main_saveStateOnFile(Theater t) {
    char *str = malloc(sizeof(char) * 54);
    int result;
    char opc;

    printf("Digite o nome do arquivo a salvar o teatro (até 50 caracteres): ");
    scanf("%s", str);
    strcat(str, ".txt ");
    str[strlen(str) - 1] = '\0';
    result = saveState(t, str);
    free(str);
    
    if (result == 1) {
        printf("Seus dados foram salvos com sucesso! \n");
    }
    else {
        printf("Não foi possível abrir o arquivo. Tentar novamente? (s/n) ");
        if(scanf("%c") == 's') { main_saveStateOnFile(t); } 
        else { return; }
    }
}