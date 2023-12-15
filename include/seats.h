#ifndef seats_h
#define seats_h

#include "entities.h"

/// @brief Aloca e inicializa uma matriz de assentos.
/// @param l Número de fileiras.
/// @param c Número de colunas.
/// @return Endereço base da matriz de assentos.
Seat **initiliazeMatrix(int l, int c);

#endif