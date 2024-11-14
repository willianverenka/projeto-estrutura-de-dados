#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "./include/registro.h"

typedef struct EFila {
    Registro* dados;
    struct EFila* proximo;
} EFila;

typedef struct Fila {
    EFila* head;
    EFila* tail;
    int qtd;
} Fila;

EFila* criar_EFila(Registro* data) {
    EFila* temp = (EFila*)malloc(sizeof(EFila));
    if (temp == NULL) return NULL;

    // Aloca e copia os dados do registro
    temp->dados = (Registro*)malloc(sizeof(Registro));
    if (temp->dados == NULL) {
        free(temp);
        return NULL;
    }

    // Aloca a estrutura de data
    temp->dados->entrada = (Data*)malloc(sizeof(Data));
    if (temp->dados->entrada == NULL) {
        free(temp->dados);
        free(temp);
        return NULL;
    }

    // Copia todos os dados
    strcpy(temp->dados->nome, data->nome);
    strcpy(temp->dados->RG, data->RG);
    temp->dados->idade = data->idade;
    temp->dados->entrada->dia = data->entrada->dia;
    temp->dados->entrada->mes = data->entrada->mes;
    temp->dados->entrada->ano = data->entrada->ano;

    temp->proximo = NULL;
    return temp;
}

//cria uma fila zerada
Fila* criar_fila() {
    Fila* q = (Fila*)malloc(sizeof(Fila));
    if (q == NULL) return NULL;
    
    q->head = q->tail = NULL;
    q->qtd = 0;  // Inicializa qtd com 0
    return q;
}

//adiciona registro ao fim da fila

void enqueue(Fila* q, Registro* data) {
    EFila* temp = criar_EFila(data);
    if (temp == NULL) return;  

    if (q->tail == NULL) {
        q->head = q->tail = temp;
    } else {
        q->tail->proximo = temp;
        q->tail = temp;
    }
    q->qtd++;
}

Registro* dequeue(Fila* q) {
    if (q->head == NULL) {
        return NULL;
    }
    
    EFila* temp = q->head;
    Registro* data = temp->dados;  
    
    q->head = q->head->proximo;

    // se a fila ficar vazia, atualiza o tail
    if (q->head == NULL) {
        q->tail = NULL;
    }
    
    free(temp);  // Libera apenas o nó da fila
    q->qtd--;
    return data;
}

int isEmpty(Fila* q) {
    return q->head == NULL;
}

void freeQueue(Fila* q) {
    while (!isEmpty(q)) {
        Registro* data = dequeue(q);
        if (data != NULL) {
            free(data->entrada);  // Libera a data
            free(data);           // Libera o registro
        }
    }
    free(q);
}

void registro_imprime(Registro* reg) {
    if (reg == NULL) {
        printf("Registro nulo!\n");
        return;
    }
    
    printf("+--------------------------+\n");
    printf("| Nome: %-18s |\n", reg->nome);
    printf("| Idade: %-17d |\n", reg->idade);
    printf("| RG: %-19s |\n", reg->RG);
    
    if (reg->entrada != NULL) {
        printf("| Data: %02d/%02d/%04d       |\n", 
               reg->entrada->dia, 
               reg->entrada->mes, 
               reg->entrada->ano);
    } else {
        printf("| Data: Não disponível    |\n");
    }
    printf("+--------------------------+\n");
}

void printQueue(Fila* q) {
    if (q == NULL) return;
    
    EFila* temp = q->head;

    if(q->head == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    while (temp != NULL) {
        registro_imprime(temp->dados);
        temp = temp->proximo;
    }
    printf("\n");
}