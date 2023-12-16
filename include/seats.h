#ifndef seats_h
#define seats_h

#include "entities.h"

/// @brief Aloca e inicializa uma matriz de assentos.
/// @param r Número de fileiras.
/// @param c Número de colunas.
/// @return Endereço base da matriz de assentos.
Seat **initiliazeMatrix(int r, int c);

/// @brief Desaloca uma matriz de assentos.
/// @param a Ponteiro para a matriz.
/// @param r Quantidade de linhas da matriz.
void deallocateMatrix(Seat **a, int r);

#endif