#include "./include/registro.h"
#include "./include/lista.h"
#include "./include/data.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Função para criar uma nova data
Data* criarData() {
    Data* nova = (Data*)malloc(sizeof(Data));
    printf("Data de entrada (dd mm aaaa): ");
    scanf("%d %d %d", &nova->dia, &nova->mes, &nova->ano);
    return nova;
}

// Função para criar uma nova lista
Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtde = 0;
    return lista;
}

void inserePaciente(Lista* lista, Registro* paciente){
    ELista* novo = (ELista*)malloc(sizeof(ELista));
    novo->dados = paciente;
    
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->qtde++;
}

// Função para cadastrar novo paciente
void cadastrarPaciente(Lista* lista) {
    ELista* novo = (ELista*)malloc(sizeof(ELista));
    novo->dados = (Registro*)malloc(sizeof(Registro));
    
    printf("\n=== Cadastro de Novo Paciente ===\n");
    
    printf("Nome: ");
    scanf(" %[^\n]s", novo->dados->nome);
    
    printf("Idade: ");
    scanf("%d", &novo->dados->idade);
    
    printf("RG: ");
    scanf(" %[^\n]s", novo->dados->RG);
    
    novo->dados->entrada = criarData();
    
    // Inserção no início da lista
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->qtde++;
    
    printf("\nPaciente cadastrado com sucesso!\n");
}

// Função para consultar paciente
void consultarPaciente(Lista* lista) {
    if (lista->inicio == NULL) {
        printf("\nNenhum paciente cadastrado!\n");
        return;
    }
    
    char nome[50];
    printf("\nDigite o nome do paciente: ");
    scanf(" %[^\n]s", nome);
    
    ELista* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados->nome, nome) == 0) {
            printf("\n=== Dados do Paciente ===\n");
            printf("Nome: %s\n", atual->dados->nome);
            printf("Idade: %d\n", atual->dados->idade);
            printf("RG: %s\n", atual->dados->RG);
            printf("Data de entrada: %02d/%02d/%04d\n", 
                   atual->dados->entrada->dia,
                   atual->dados->entrada->mes,
                   atual->dados->entrada->ano);
            return;
        }
        atual = atual->proximo;
    }
    
    printf("\nPaciente não encontrado!\n");
}

Registro* buscarPaciente(Lista* lista, char rg[15]){
    ELista* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados->RG, rg) == 0) {
            return atual->dados;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Função para mostrar lista completa
void mostrarLista(Lista* lista) {
    if (lista->inicio == NULL) {
        printf("\nNenhum paciente cadastrado!\n");
        return;
    }
    
    printf("\n=== Lista de Pacientes ===\n");
    ELista* atual = lista->inicio;
    while (atual != NULL) {
        printf("\nNome: %s\n", atual->dados->nome);
        printf("Idade: %d\n", atual->dados->idade);
        printf("RG: %s\n", atual->dados->RG);
        printf("Data de entrada: %02d/%02d/%04d\n", 
               atual->dados->entrada->dia,
               atual->dados->entrada->mes,
               atual->dados->entrada->ano);
        printf("-----------------------\n");
        atual = atual->proximo;
    }
}

// Função para atualizar dados do paciente
void atualizarPaciente(Lista* lista) {
    if (lista->inicio == NULL) {
        printf("\nNenhum paciente cadastrado!\n");
        return;
    }
    
    char rg[15];
    printf("\nDigite o RG do paciente: ");
    scanf(" %[^\n]s", rg);
    
    ELista* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados->RG, rg) == 0) {
            printf("\n=== Atualizar Dados ===\n");
            printf("Novo nome: ");
            scanf(" %[^\n]s", atual->dados->nome);
            printf("Nova idade: ");
            scanf("%d", &atual->dados->idade);
            printf("Nova data de entrada:\n");
            free(atual->dados->entrada);
            atual->dados->entrada = criarData();
            printf("\nDados atualizados com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    
    printf("\nPaciente não encontrado!\n");
}

void removerPaciente(Lista* lista) {
    // verifica se a lista esta vazia antes de percorrer pelos registros
    if (lista == NULL || lista->inicio == NULL) {
        printf("\nNenhum paciente cadastrado!\n");
        return;
    }
    
    char rg[15];
    printf("\nDigite o RG do paciente a ser removido: ");
    scanf(" %[^\n]s", rg);
        
    ELista* atual = lista->inicio;
    ELista* anterior = NULL;
    
    while (atual != NULL) {
        
        if (strcmp(atual->dados->RG, rg) == 0) {
            
            // Guarda o próximo antes de começar a liberar memória
            ELista* proximo = atual->proximo;
            
            // Remocao no inicio da lista
            if (anterior == NULL) {
                lista->inicio = proximo;
            } else {
                // remocao no meio ou fim da lista
                anterior->proximo = proximo;
            }
            
            // Verifica se dados e entrada são válidos antes de liberar
            if (atual->dados != NULL) {
                free(atual->dados);
                atual->dados = NULL;
            }
            free(atual);
            atual = NULL;
            lista->qtde--;
            printf("\nPaciente removido com sucesso! Quantidade atual: %d\n", lista->qtde);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("\nPaciente não encontrado!\n");
}
