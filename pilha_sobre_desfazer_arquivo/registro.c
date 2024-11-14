#include "../include/registro.h"
#include <stdio.h>

void registro_imprime(Registro* r) {
    printf("Nome: %s\n", r->nome);
    printf("Idade: %d\n", r->idade);
    printf("RG: %s\n", r->RG);
    printf("Data de entrada: ");
    printf("%d/%d/%d\n", r->entrada->dia, r->entrada->mes, r->entrada->ano);
}