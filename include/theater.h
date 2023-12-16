#ifndef theater_h
#define theater_h

#include "entities.h"

/// @brief Cria um teatro com "l" fileiras e "c" colunas. 
/// @param l Número de fileiras.
/// @param c Número de colunas.
/// @return Um teatro alocado dinamicamente.
Theater createTheater(int l, int c);

/// @brief Carrega os dados do teatro salvo no arquivo.
/// @param file Endereço do arquivo.
/// @return Dados do teatro.
Theater loadState(char *file);

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

#endif