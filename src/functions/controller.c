#include "../../include/theater.h"
#include "../../include/controller.h"
#include "../../include/seats.h"
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

void main_SaveSpecificSeatThroughSystem(Theater t) {
    char *str = malloc(sizeof(char) * 99);
    char opc;
    Seat *s;

    printf("Você selecionou a opção 'Reservar assento pelo sistema'.\n");
    printf("Ao continuar, você terá um assento reservado de forma automática. Deseja continuar? (s/n) ");
    getchar();
    scanf("%c", &opc);

    if (opc == 's') {
        printf("Digite seu primeiro nome: ");
        scanf("%s", str);
        getchar();
        str[strlen(str)] = '\0';
        s = saveAutomaticSeat(t, str);
        
        if (s == NULL) {
            printf("Não há assentos disponíveis.\n");
            return;
        } else {
            printf("Sua reserva foi marcada para o assento %c%d!\n", s->row, s->number);
            return;
        }
    }
    else { return; }
}

void main_CancelMultipleReservations(Theater t) {
    char *str = malloc(sizeof(char) * 99);
    int result;
    char opc;

    printf("Você escolheu a opção 'Cancelar reservas de uma pessoa.'\n");
    printf("Digite o nome da pessoa que terá as reservas excluídas (até 99 caracteres): \n");
    scanf("%s", str);
    str[strlen(str)] = '\0';

    result = cancelMultipleReservations(t, str);

    if (result == 0) {
        printf("Não há nenhuma reserva para essa pessoa. Deseja tentar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);  
        if (opc == 's') { main_CancelMultipleReservations(t); }
        else { return; }
    }
    else {
        printf("%d reservas no total foram canceladas para %s!\n", result, str);
        return;
    }
}

void main_LoadState(Theater t){
    char *file = malloc(sizeof(char) * 54);
    char opc;

    printf("Você escolheu a opção 'Carregar Estado'.\n");
    printf("Ao continuar o processo, a configuração de assentos atual será descartada. Deseja continuar? (s/n) ");
    getchar();
    scanf("%c", &opc);

    if(opc == 's'){
        printf("Digite o nome do arquivo (até 50 caracteres): ");
        scanf("%s", file);
        strcat(file, ".txt");
        printf("%s", file);

        deallocateMatrix(t.seats, t.qtdRows);
        
        t = loadState(file);

        // if (&newT != NULL) {
            // dá erro de segmentation fault após digitar s
            printf("Operação concluída. Deseja visualizar a nova configuração de assentos? (s/n) ");
            getchar();
            scanf("%c", &opc);
            // verificar se tá certo chamar a função main_view
            if (opc == 's') { main_View(t); }
            else { return; }
        // }
        // else {
        //     // deu errado!
        // }

    }
    else { printf("Operação cancelada.\n"); return; }
}

void main_CancelAllReservations(Theater t) {
    char opc;
    int total = 0;

    printf("Você escolheu a opção 'Cancelar todas as reservas'.\n");
    printf("A partir de agora todas as reservas nos assentos serão excluídas. Deseja continuar? (s/n) ");
    getchar();
    scanf("%c", &opc);

    if (opc == 's') {
        total = cancelAllReservations(t);
        if (total == 0) { 
            printf("Nenhuma reserva foi deletada. \n");
        }
        else {
            printf("%d reservas foram canceladas.\n", total);
        }
    }
    else { printf("Operação cancelada.\n"); return; }
}