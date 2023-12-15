#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/seats.h"
#include "../include/theater.h"

int main(int argc, char *argv[]) { 
    printf("Seja bem vindo!");
    printf("Por favor, informe a quantidade de fileiras e número de cadeiras por fileira de seu teatro: ");
    int f, n;
    scanf("%d %d", &f, &n);
    Theater t = createTheater(f, n);

    int operations;

    printf("Quais operações deseja realizar? Veja a lista abaixo:\n");
    printf("00 | Sair do Programa\n");
    printf("01 | Salvar Estado\n");
    printf("02 | Carregar Estado\n");
    printf("03 | Visualizar\n");

    return 0;
}

