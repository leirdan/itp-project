#ifndef theater_h
#define theater_h

#include "entities.h"

/// @brief Cria um teatro com "l" fileiras e "c" colunas. 
/// @param l Número de fileiras.
/// @param c Número de colunas.
/// @return Um teatro alocado dinamicamente.
Theater createTheater(int l, int c);

/// @brief Carrega um arquivo e cria uma nova matriz com base nas informações contidas nesse arquivo carregado
/// @param argv Nome do arquivo
/// @return Um novo teatro
Theater loadState(char *argv);

/// @brief Cria uma única reserva no teatro. 
/// @param t Teatro a ser reservado.
/// @param r Fileira (linha) do assento.
/// @param c Coluna do assento.
/// @param n Nome da pessoa a reservar.
/// @return 0 se o assento não está disponível; 1 se o assento está livre e foi reservado.
int createReservation(Theater t, int r, int c, char *n);

/// @brief Imprime os assentos do teatro no console.
/// @param t O teatro.
void displayTheater(Theater t);

/// @brief Cancela a reserva do assento localizado na fileira 'r' e coluna 'c'
/// @param t O teatro.
/// @param r Índice da fileira.
/// @param c Índice da coluna.
/// @return 1 se o assento estava reservado e 0 caso contrário.
int cancelReservation(Theater t, int r, int c);

/// @brief Cancela todas as reservas de assentos para uma única pessoa.
/// @param t O teatro.
/// @param n Nome da pessoa que reservou.
/// @return Número de reservas canceladas.
int cancelMultipleReservations(Theater t, char *n);

/// @brief Verifica se um assento está reservado no teatro.
/// @param t O teatro.
/// @param r Índice da fileira.
/// @param c Índice da coluna.
/// @return 1 se o assento está disponível; senão, retorna 0. 
int isSeatFree(Theater t, int r, int c);

/// @brief Salva os dados do teatro atual em um arquivo.
/// @param t O teatro.
/// @param file Nome do arquivo.
/// @return 1 se foi possível escrever os dados no arquivo; 0, caso contrário.
int saveState(Theater t, char *file);

/// @brief Cria n reservas no teatro em uma mesma fileira para um mesmo cliente.
/// @param t O teatro.
/// @param r Fileira da reserva.
/// @param c Número da poltrona inicial da reserva.
/// @param n Nome do cliente.
/// @param x Quantidade de reservas a serem feitas.
/// @return 1 se foi possível reservar os 'x' assentos; 0, caso contrário.
int createMultipleReservation(Theater t, int r, int c, char *n, int x);

/// @brief Verifica se 'x' poltronas da mesma fileira estão reservadas.
/// @param t O teatro.
/// @param r Fileira da poltrona.
/// @param c Número da poltrona inicial.
/// @param x Quantidade de poltronas a verificar.
/// @return 1 se as 'x' poltronas estão livres; 0, caso contrário.
int checkSeatsInline(Theater t, int r, int c, int x);

/// @brief Cancela todas as reservas de assentos no teatro.
/// @param t O teatro.
/// @return Quantidade de reservas canceladas.
int cancelAllReservations(Theater t);

/// @brief Cria uma reserva para o primeiro assento disponível que encontrar.
/// @param t O teatro.
/// @param n Nome do cliente.
/// @return Endereço de memória do assento ou NULL caso não haja assento disponível.
Seat *saveAutomaticSeat(Theater t, char *n);

/// @brief Cria 'x' reservas em uma mesma fileira para uma única pessoa.
/// @param t O teatro.
/// @param x Quantidade de assentos a serem reservados.
/// @param n Nome do cliente.
/// @return Endereço de memória do vetor de assentos ou NULL caso não seja possível criar as 'x' reservas.
Seat **saveAutomaticMultipleSeat(Theater t, int x, char *n);

#endif