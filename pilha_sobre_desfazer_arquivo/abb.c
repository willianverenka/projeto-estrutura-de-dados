#include <stdio.h>
#include <stdlib.h>
#include "./include/abb.h"
#include "./include/registro.h"
#include "./include/data.h"
#include <string.h>

EABB* eabb_inicializar(Registro* dados) {
    printf("Nome: %s\n", dados->nome);
    printf("Idade: %d\n", dados->idade);
    printf("RG: %s\n", dados->RG);
    printf("Data: %d/%d/%d\n", dados->entrada->dia, dados->entrada->mes, dados->entrada->ano);
    
    EABB* novoNo = (EABB*)malloc(sizeof(EABB));
    if (novoNo == NULL) {
        return NULL;
    }
    
    // Aloca novo registro
    novoNo->dados = (Registro*)malloc(sizeof(Registro));
    if (novoNo->dados == NULL) {
        free(novoNo);
        return NULL;
    }
    
    novoNo->dados->entrada = (Data*)malloc(sizeof(Data));
    if (novoNo->dados->entrada == NULL) {
        free(novoNo->dados);
        free(novoNo);
        return NULL;
    }
    
    strcpy(novoNo->dados->nome, dados->nome);
    strcpy(novoNo->dados->RG, dados->RG);
    novoNo->dados->idade = dados->idade;
    novoNo->dados->entrada->dia = dados->entrada->dia;
    novoNo->dados->entrada->mes = dados->entrada->mes;
    novoNo->dados->entrada->ano = dados->entrada->ano;
    
    novoNo->filho_esq = NULL;
    novoNo->filho_dir = NULL;

    return novoNo;
}

void abb_inicializar(ABB* arvore) {
    arvore->raiz = NULL;
    arvore->qtde = 0;
}

EABB* eabb_inserir(EABB* raiz, Registro* dados, Chave chave) {

    if (raiz == NULL) {
        return eabb_inicializar(dados);
    }
    
    switch(chave){
        case ANO:
            if (dados->entrada->ano < raiz->dados->entrada->ano) {
                raiz->filho_esq = eabb_inserir(raiz->filho_esq, dados, chave);
            } else {
                raiz->filho_dir = eabb_inserir(raiz->filho_dir, dados, chave);
            }
            break;
        case MES:
            if (dados->entrada->mes < raiz->dados->entrada->mes) {
                raiz->filho_esq = eabb_inserir(raiz->filho_esq, dados, chave);
            } else {
                raiz->filho_dir = eabb_inserir(raiz->filho_dir, dados, chave);
            }
            break;
        case DIA:
            if (dados->entrada->dia < raiz->dados->entrada->dia) {
                raiz->filho_esq = eabb_inserir(raiz->filho_esq, dados, chave);
            } else {
                raiz->filho_dir = eabb_inserir(raiz->filho_dir, dados, chave);
            }
            break;
        case IDADE: 
            if (dados->idade < raiz->dados->idade) {
                raiz->filho_esq = eabb_inserir(raiz->filho_esq, dados, chave);
            } else {
                raiz->filho_dir = eabb_inserir(raiz->filho_dir, dados, chave);
            }
            break;
    }
    return raiz;
}

void abb_inserir(ABB* arvore, Registro* dados, Chave chave) {
    printf("Debug: Iniciando inserção na árvore\n");  // Debug
    arvore->raiz = eabb_inserir(arvore->raiz, dados, chave);
    arvore->qtde++;
    printf("Debug: Inserção concluída. Quantidade de nós: %d\n", arvore->qtde);  // Debug
}

EABB* buscarNo(EABB* raiz, Chave chave, int valor) {
    switch(chave){
        case ANO:
            if (raiz == NULL || raiz->dados->entrada->ano == valor) {
                return raiz;
            }
            if (valor < raiz->dados->entrada->ano) {
                return buscarNo(raiz->filho_esq, chave, valor);
            }
            return buscarNo(raiz->filho_dir, chave, valor);
        case MES:
            if (raiz == NULL || raiz->dados->entrada->mes == valor) {
                return raiz;
            }
            if (valor < raiz->dados->entrada->mes) {
                return buscarNo(raiz->filho_esq, chave, valor);
            }
            return buscarNo(raiz->filho_dir, chave, valor);
        case DIA:
            if (raiz == NULL || raiz->dados->entrada->dia == valor) {
                return raiz;
            }
            if (valor < raiz->dados->entrada->dia) {
                return buscarNo(raiz->filho_esq, chave, valor);
            }
            return buscarNo(raiz->filho_dir, chave, valor);
    }
}

EABB* buscar(ABB* arvore, Chave chave, int valor) {
    return buscarNo(arvore->raiz, chave, valor);
}

void liberarNo(EABB* raiz) {
    if (raiz != NULL) {
        liberarNo(raiz->filho_esq);
        liberarNo(raiz->filho_dir);
        free(raiz->dados);
        free(raiz);
    }
}

void liberarABB(ABB* arvore) {
    liberarNo(arvore->raiz);
    arvore->raiz = NULL;
    arvore->qtde = 0;
}

void imprimirEmOrdem(EABB* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->filho_esq);
        printf("\n=== Dados do Paciente ===\n");
            printf("Nome: %s\n", raiz->dados->nome);
            printf("Idade: %d\n", raiz->dados->idade);
            printf("RG: %s\n", raiz->dados->RG);
            printf("Data de entrada: %02d/%02d/%04d\n", 
                   raiz->dados->entrada->dia,
                   raiz->dados->entrada->mes,
                   raiz->dados->entrada->ano);
        imprimirEmOrdem(raiz->filho_dir);
    }
}