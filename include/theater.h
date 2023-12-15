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

#endif