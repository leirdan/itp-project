## TO-DO

1. Criar função de consultar assentos consecutivos (*clezio*);
2. Consertar textos no Windows.

* <del> Tratar o caso da entrada ser maior que o número de assentos disponíveis em `main_SaveSpecificSeatThroughSystem` (*andriel*) </del>;
* <del>Criar função loadState (*clezio*)</del>;
* <del>Criar arquivo do compilador (*clezio*)</del>;
* <del>Adicionar parâmetros à saída da reserva de múltiplos assentos (*andriel*)</del>;
* <del>Criar função cancelReservations(*andriel*)</del>;
* <del>Consertar os textos dos prints (*andriel*)</del>;
* <del>Verificar erro quando no `realloc` do `main.c` (quando há 7 operações ou mais); </del>
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