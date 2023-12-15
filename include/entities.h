#ifndef entities_h
#define entities_h

typedef struct {
    int reserved;
    int row;
    int number;
    char *name;
} Seat;

typedef struct {
    Seat **seats;
    int qtdRows;
    int qtdColumns;
} Theater;

#endif