#ifndef FILA_H
#define FILA_H

typedef struct EFila {
    Registro* dados;
    struct EFila* proximo;
} EFila;

typedef struct Fila {
    EFila* head;
    EFila* tail;
    int qtd;
} Fila;

EFila* criar_EFila(Registro* data);

Fila* criar_fila();

void enqueue(Fila* q, Registro* data);

Registro* dequeue(Fila* q);

int isEmpty(Fila* q);

void freeQueue(Fila* q);

void registro_imprime(Registro* reg);
void printQueue(Fila* q);

#endif