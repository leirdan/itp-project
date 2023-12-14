#ifndef entities_h
#define entities_h

typedef struct {
    int reservado;
    int fileira;
    int numero;
    char *nome;
} Assento;

typedef struct {
    Assento **assento;
    int linha;
    int coluna;
} Teatro;

#endif