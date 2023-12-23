#include "../../include/theater.h"
#include "../../include/controller.h"
#include "../../include/seats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>



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

    printf("Voc� escolheu a op��o 'Reservar Assento'.\n");
    printf("Digite o primeiro do nome do cliente (at� 99 caracteres): ");
    getchar();
    scanf("%s", str);
    printf("Digite o n�mero da fileira e o n�mero do assento desejada: ");
    getchar();
    scanf("%d %d", &r, &c);

    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inv�idas. Insira uma fileira e um n�mero de assento v�idos: ");
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
        printf("O assento n�o est� dispon�vel. Deseja cadastrar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        free(str);  
        if (opc == 's') { main_SaveSpecificSeat(t); }
        else { return; }
    }
}

void main_CancelReservation(Theater t) {
    int r, c, result, validation;
    char opc; 
    Seat *s;

    printf("Voc� escolheu a op��o 'Cancelar Reserva'.\n");
    printf("Digite o n�mero da fileira e a coluna do assento que voc� deseja cancelar a reserva: ");
    getchar();
    scanf("%d %d", &r, &c);

    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inv�lidas. Insira uma fileira e um n�mero de assento v�lidos: ");
        getchar();
        scanf("%d %d", &r, &c);
        validation = validateParams(t, r, c);
    }

    s = &(t.seats[r-1][c-1]);
    result = cancelReservation(t, r, c);

    if (result == 0) { 
        printf("N�o h� reserva para esse assento. Deseja tentar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        if (opc == 's') { main_CancelReservation(t); }
        else { return; }
    } 
    else {
        printf("A reserva do assento %c%d foi cancelada com sucesso.\n", s->row, s->number);
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

    printf("Digite o nome do arquivo a salvar o teatro (at� 50 caracteres): ");
    getchar();
    scanf("%s", str);
    strcat(str, ".txt");
    str[strlen(str)] = '\0';
    result = saveState(t, str);
    free(str);

    if (result == 1) {
        printf("Seus dados foram salvos com sucesso! \n");
    }
    else {
        printf("N�o foi poss�vel abrir o arquivo. Tentar novamente? (s/n) ");
        getchar();
        if(scanf("%c") == 's') { main_SaveStateOnFile(t); } 
        else { return; }
    }
}

void main_SaveMultipleSeats(Theater t) {
    char *str = malloc(sizeof(char) * 100);
    int r, c, x, result, validation;
    char opc;

    printf("Voc� escolheu a op��o 'Reservar Assentos Consecutivos'.\n");
    printf("Digite o primeiro do nome do cliente (at� 99 caracteres): ");
    getchar();
    scanf("%s", str);
    str[strlen(str)] = '\0';
    getchar();
    printf("Digite quantos assentos deseja reservar: ");
    scanf("%d", &x);
    printf("Digite o n�mero da fileira e o n�mero do assento inicial: ");
    getchar();
    scanf("%d %d", &r, &c);

    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inv�lidas. Insira uma fileira e um n�mero de assento v�lidos: ");
        getchar();
        scanf("%d %d", &r, &c);
        validation = validateParams(t, r, c);
    }

    result = createMultipleReservation(t, r, c, str, x);          

    switch (result) {
        case -1:
            printf("N�o h� assentos suficientes dispon�veis. Deseja reiniciar a opera��o? (s/n) ");
            getchar();
            scanf("%c", &opc);
            free(str);  
            if (opc == 's') { main_SaveMultipleSeats(t); }
            break;
        case 0:
            printf("N�o foi poss�vel criar reserva em um dos assentos. Deseja reiniciar o processo? (s/n) ");
            getchar();
            scanf("%c", &opc);
            free(str);  
            if (opc == 's') { main_SaveMultipleSeats(t); }
            break;
        case 1:
            printf("Os %d assentos escolhidos da fileira %c foram reservados com sucesso!\n", x, t.seats[r-1][0].row);
            break;
        default:
            break;
    }     

}

void main_SaveSpecificSeatThroughSystem(Theater t) {
    char *str = malloc(sizeof(char) * 99);
    char opc;
    Seat *s;

    printf("Voc� selecionou a op��o 'Reservar assento pelo sistema'.\n");
    printf("Ao continuar, um assento ser� reservado de forma autom�tica. Deseja continuar? (s/n) ");
    getchar();
    scanf("%c", &opc);

    if (opc == 's') {
        printf("Digite o primeiro do nome do cliente (at� 99 caracteres): ");
        scanf("%s", str);
        getchar();
        str[strlen(str)] = '\0';
        s = saveAutomaticSeat(t, str);
        
        if (s == NULL) {
            printf("N�o h� assentos dispon�veis.\n");
            free(str);
            return; 
        } else {
            printf("A reserva do cliente %s foi marcada para o assento %c%d!\n", str, s->row, s->number);
            return;
        }
    }
    else { return; }
}

void main_SaveMultipleSeatsThroughSystem(Theater t) {
    char *str = malloc(sizeof(char) * 99);
    int x;
    char opc;
    Seat **seats;

    printf("Voc� selecionou a op��o 'Reservar assentos consecutivos pelo sistema'.\n");
    printf("Digite o primeiro nome do cliente (at� 99 caracteres): ");
    getchar();
    scanf("%s", str);
    str[strlen(str)] = '\0';
    getchar();
    printf("Digite a quantidade de assentos a reservar: ");
    getchar();
    scanf("%d", &x);

    if (x<1) {
        printf("N�mero inv�lido! Deseja tentar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        free(str);  
        if (opc == 's') { main_SaveMultipleSeatsThroughSystem(t); }
        return;
    }
    if (x > t.qtdColumns) {
        printf("N�o � poss�vel reservar %d assentos consecutivos pois a fileira cont�m somente %d assentos. Deseja tentar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        free(str);  
        if (opc == 's') { main_SaveMultipleSeatsThroughSystem(t); }
        return;
    }

    
    seats = saveAutomaticMultipleSeat(t, x, str);

    if (seats == NULL) {
        printf("N�o foi poss�vel reservar %d assentos de forma consecutiva.\n");
    }
    else {
        printf("Foram reservados os assentos");
        for (int i = 0; i < x; i++) {
            if (i + 1 != x) {
                printf(" %c%d,", seats[i]->row, seats[i]->number);
            } 
            else {
                printf(" %c%d", seats[i]->row, seats[i]->number);
            }
        }
        printf(" para %s!\n", seats[0]->name);

    }
    return;
}

void main_CancelMultipleReservations(Theater t) {
    char *str = malloc(sizeof(char) * 99);
    int result;
    char opc;

    printf("Voc� escolheu a op��o 'Cancelar reservas de uma pessoa.'\n");
    printf("Digite o nome da pessoa que ter� as reservas exclu�das (at� 99 caracteres): \n");
    getchar();
    scanf("%s", str);
    str[strlen(str)] = '\0';

    result = cancelMultipleReservations(t, str);

    if (result == 0) {
        printf("N�o h� nenhuma reserva para essa pessoa. Deseja tentar novamente? (s/n) ");
        getchar();
        scanf("%c", &opc);
        free(str);  
        if (opc == 's') { main_CancelMultipleReservations(t); }
        else { return; }
    }
    else {
        printf("%d reservas no total foram canceladas para %s!\n", result, str);
        return;
    }
}

Theater main_LoadState(Theater t){
    char file[50];
    char opc;

    printf("Voc� escolheu a op��o 'Carregar Estado'.\n");
    printf("Ao continuar o processo, a configura��o de assentos atual ser� descartada. Deseja continuar? (s/n) ");
    getchar();
    scanf("%c", &opc);

    if(opc == 's'){
        printf("Digite o nome do arquivo (at� 50 caracteres): ");
        scanf("%49s", file);
        strcat(file, ".txt ");
        printf("%s\n", file);
        deallocateMatrix(t.seats, t.qtdRows);

       t = loadState(file);
        if (t.seats == NULL) {
            printf("N�o foi poss�vel carregar o arquivo. Deseja tentar novamente? (s/n) ");
            getchar();
            scanf("%c", &opc);
            if (opc == 's') { main_LoadState(t); }
            else {                                                          
                printf("Opera��o cancelada.\n");
                return;
            }
        }
        else {
            printf("Arquivo carregado com sucesso!\n");
            return t;
        }

    }

    return t;
}

void main_CancelAllReservations(Theater t) {
    char opc;
    int total = 0;

    printf("Voc� escolheu a op��o 'Cancelar todas as reservas'.\n");
    printf("A partir de agora todas as reservas nos assentos ser�o exclu�das. Deseja continuar? (s/n) ");
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
    else { printf("Opera��o cancelada.\n"); return; }
}

void main_seeConsecutiveSeats(Theater t){
    int n;
    char opc;
    printf("Qual � o n�mero m�nimo de assentos consecutivos que voc� deseja consultar? ");
    getchar();
    scanf("%d", &n);
    if (n == 0) {
        printf("Voc� ser� redirecionado para o menu\n");
        return;
    }
    else if (n < 0 || n > t.qtdColumns){
        printf("Valor inv�lido. Deseja tentar novamente? (s/n)\n");
        getchar();
        scanf("%c\n", &opc);  
        if (opc == 's') { main_seeConsecutiveSeats(t); }
        else { return; }
    }
    seeConsecutiveSeats(t, n);
}

void main_CheckSeat(Theater t) {
    int r, c, result, validation;

    printf("Voc� escolheu a op��o 'Verificar Disponibilidade'.\n");
    printf("Digite o n�mero da fileira e do assento a ser consultado: ");
    getchar();
    scanf("%d %d", &r, &c);
    
    validation = validateParams(t, r, c);
    while (validation == 0) {
        printf("Entradas inv�lidas. Insira uma fileira e um n�mero de assento v�lidos: ");
        getchar();
        scanf("%d %d", &r, &c);
        validation = validateParams(t, r, c);
    }

    result = isSeatFree(t, r-1, c-1);

    if (result == 1) { 
        printf("O assento %c%d est� dispon�vel!\n", t.seats[r-1][c-1].row, t.seats[r-1][c-1].number);
        return;
    }
    else {
        printf("O assento %c%d n�o est� dispon�vel.\n", t.seats[r-1][c-1].row, t.seats[r-1][c-1].number); 
        return;
    }
}