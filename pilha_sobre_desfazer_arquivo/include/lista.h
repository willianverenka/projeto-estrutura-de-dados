#ifndef LISTA_H
#define LISTA_H
#include "registro.h"

struct ELista {
    Registro* dados;
    struct ELista* proximo;
};

// Typedef para ELista
typedef struct ELista ELista;

// Estrutura principal da lista
typedef struct {
    ELista* inicio;
    int qtde;
} Lista;

Registro* buscarPaciente(Lista* lista, char* rg);
void cadastrarPaciente(Lista* lista);
void consultarPaciente(Lista* lista);
void mostrarLista(Lista* lista);
void atualizarPaciente(Lista* lista);
void removerPaciente(Lista* lista);
Lista* criarLista();
void inserePaciente(Lista* lista, Registro* paciente);

#endif