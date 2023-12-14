#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/seats.h"
#include "../include/theater.h"

int main(int argc, char *argv[]) { 
    printf("Seja bem vindo/a/e! Por favor, informe a quantidade de fileiras e número de cadeiras por fileira de seu teatro: ");
    int f, n;
    scanf("%d %d", &f, &n);
    
    Teatro t = criarTeatro(f, n);
    printf("%d \n", t.linha);
    printf("%d \n", t.coluna);

    return 0;
}

