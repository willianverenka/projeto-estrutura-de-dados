#ifndef REGISTRO_H
#define REGISTRO_H
#include "data.h"

typedef struct {
    char nome[50];
    int idade;
    char RG[15];
    Data* entrada;
} Registro;
void registro_imprime(Registro* r);

#endif