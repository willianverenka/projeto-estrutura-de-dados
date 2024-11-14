#ifndef ABB_H
#define ABB_H
#include "registro.h"

typedef struct EABB {
    Registro* dados;
    struct EABB* filho_esq;
    struct EABB* filho_dir;
} EABB;

typedef struct {
    EABB* raiz;
    int qtde;
} ABB;

typedef enum{ 
    ANO,
    MES, 
    DIA,
    IDADE
} Chave;

EABB* eabb_inicializar(Registro* dados);
void abb_inicializar(ABB* arvore);
EABB* eabb_inserir(EABB* raiz, Registro* dados, Chave chave);
void abb_inserir(ABB* arvore, Registro* dados, Chave chave);
EABB* buscarNo(EABB* raiz, Chave chave, int valor);
void liberarNo(EABB* raiz);
void liberarABB(ABB* arvore);
void imprimirEmOrdem(EABB* raiz);
#endif