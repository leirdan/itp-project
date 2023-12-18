## TO-DO

1. Criar função loadState (*clezio*);
2. Ajeitar a leitura das strings, adicionando o caractere '\0' (a definir);
3. Criar função cancelReservations(*andriel*);

* <del>Verificar erro quando no `realloc` do `main.c` (quando há 7 operações ou mais); </del>
* <del>Consertar os textos dos prints (*andriel*)</del>;
* <del>Verificar e/ou transferir as alterações para o controller (*andriel*)</del>;
    - <del>Modificação no realloc</del>;
    - <del>Função saveState</del>;
    - <del>Chamada da função na main</del>;
    - <del>Função criar reserva</del>;
* <del>Verificar erro de `segmentation fault` na função que valida os parâmetros de linha e coluna em `main_SaveSpecificSeat`; (*andriel*) </del>;
* <del>Verificar erro de `segmentation fault` na chamada da função `main_CancelateReservation`; (*clézio*) </del>
* <del>Realocar `displayTheater` para o controller; (*andriel*) </del>
* <del>Retirar duplicação de barras verticais (`theater.c`, função `displayTheater`)</del>;
* <del> Exibir mensagem de sucesso na criação da reserva (`main.c`, 68) </del>;
* <del> Lidar com a falha na criação da reserva: perguntar ao usuário se ele quer tentar novamente e replicar o processo (`main.c`, função `startup_2`)</del>;