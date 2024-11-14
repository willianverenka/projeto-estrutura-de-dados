#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/lista.h"
#include "./include/registro.h"
#include "./include/abb.h"



// Estrutura do nó da fila
typedef struct EFila {
    Registro *Dados;
    struct EFila *Proximo;
} EFila;

// Estrutura da fila
typedef struct {
    EFila *Head;
    EFila *Tail;
} Fila;

// Definindo as operações possíveis
typedef enum { ENFILEIRAR, DESENFILEIRAR, NENHUMA_OPERACAO } TipoOperacao;

// Estrutura de célula para a pilha
typedef struct Celula {
    struct Celula *proximo;
    TipoOperacao valor;
} Celula;

// Estrutura da pilha
typedef struct {
    Celula *topo;
    int qtde;
} Stack;

// Funções para manipular a pilha (mantidas iguais)
Celula *criar_celula(TipoOperacao valor) {
    Celula *celula = malloc(sizeof(Celula));
    celula->proximo = NULL;
    celula->valor = valor;
    return celula;
}

Stack *criar_pilha() {
    Stack *pilha = malloc(sizeof(Stack));
    pilha->topo = NULL;
    pilha->qtde = 0;
    return pilha;
}

void push(Stack *pilha, TipoOperacao valor) {
    Celula *novo = criar_celula(valor);
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->qtde++;
}

TipoOperacao pop(Stack *pilha) {
    if (pilha->qtde == 0) {
        return NENHUMA_OPERACAO;
    }
    TipoOperacao valor = pilha->topo->valor;
    Celula *temp = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    pilha->qtde--;
    free(temp);
    return valor;
}

// Funções para manipular a fila de pacientes
void inicializarFila(Fila *f) {
    f->Head = NULL;
    f->Tail = NULL;
}

int filaVazia(Fila *f) {
    return f->Head == NULL;
}

void enfileirar(Fila *f, Registro paciente, Stack *pilha) {
    EFila *novo = (EFila*)malloc(sizeof(EFila));
    novo->Dados = (Registro*)malloc(sizeof(Registro));
    *(novo->Dados) = paciente;
    novo->Proximo = NULL;

    if (filaVazia(f)) {
        f->Head = novo;
        f->Tail = novo;
    } else {
        f->Tail->Proximo = novo;
        f->Tail = novo;
    }

    push(pilha, ENFILEIRAR);
    printf("\n");
    printf("\n");
    printf("========================================================\n");
    printf("Paciente %s foi enfileirado.\n", paciente.nome);
    printf("========================================================\n");
    printf("\n");
}

void desenfileirar(Fila *f, Stack *pilha) {
    if (!filaVazia(f)) {
        EFila *temp = f->Head;
        Registro paciente = *(temp->Dados);
        
        f->Head = f->Head->Proximo;
        if (f->Head == NULL) {
            f->Tail = NULL;
        }
        
        free(temp->Dados);
        free(temp);

        push(pilha, DESENFILEIRAR);
        printf("\n");
        printf("\n");
        printf("========================================================\n");
        printf("Paciente %s desenfileirado.\n", paciente.nome);
        printf("========================================================\n");
        printf("\n");
    } else {
        printf("\n");
        printf("\n");
        printf("========================================================\n");
        printf("Erro: Fila vazia.\n");
        printf("========================================================\n");
        printf("\n");
    }
}

void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\n");
        printf("\n");
        printf("========================================================\n");
        printf("Fila vazia.\n");
        printf("========================================================\n");
        printf("\n");
        return;
    }

    printf("Fila de pacientes:\n");
    EFila *atual = f->Head;
    while (atual != NULL) {
        Registro p = *(atual->Dados);
        printf("Nome: %s, Idade: %d, RG: %s, Data de Entrada: %02d/%02d/%04d\n",
               p.nome, p.idade, p.RG, p.entrada->dia, p.entrada->mes,
               p.entrada->ano);
        atual = atual->Proximo;
    }
}

void desfazerOperacao(Fila *f, Stack *pilha) {
    if (pilha->qtde == 0) {
        printf("\n");
        printf("\n");
        printf("========================================================\n");
        printf("Não há operações para desfazer.\n");
        printf("========================================================\n");
        printf("\n");
        return;
    }

    TipoOperacao ultimaOperacao = pop(pilha);
    const char *descricaoOperacao = ultimaOperacao == ENFILEIRAR
                                        ? "Enfileirar paciente"
                                        : "Desenfileirar paciente";

    printf("Última operação para ser desfeita: %s\n", descricaoOperacao);
    printf("Deseja realmente desfazer esta operação? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 's') {
        if (ultimaOperacao == ENFILEIRAR && !filaVazia(f)) {
            EFila *atual = f->Head;
            if (atual == f->Tail) {
                free(atual->Dados->entrada);
                free(atual->Dados);
                free(atual);
                f->Head = NULL;
                f->Tail = NULL;
            } else {
                while (atual->Proximo != f->Tail) {
                    atual = atual->Proximo;
                }
                free(f->Tail->Dados->entrada);
                free(f->Tail->Dados);
                free(f->Tail);
                f->Tail = atual;
                f->Tail->Proximo = NULL;
            }
            printf("\n");
            printf("\n");
            printf("========================================================\n");
            printf("Operação de enfileirar desfeita.\n");
            printf("========================================================\n");
            printf("\n");
        } else if (ultimaOperacao == DESENFILEIRAR) {
            printf("\n");
            printf("\n");
            printf("========================================================\n");
            printf("Operação de desenfileirar não pode ser desfeita.\n");
            printf("========================================================\n");
            printf("\n");
        }
    } else {
        printf("\n");
        printf("\n");
        printf("========================================================\n");
        printf("Operação não foi desfeita.\n");
        printf("========================================================\n");
        printf("\n");
    }
}

void carregarDados(Fila *f, Lista* lista) {
    FILE *file = fopen("dados_pacientes.txt", "r");
    if (!file) {
        printf("\n");
        printf("\n");
        printf("========================================================\n");
        printf("Erro ao abrir o arquivo para leitura.\n");
        printf("========================================================\n");
        printf("\n");
        return;
    }

    inicializarFila(f);
    Registro paciente;
    paciente.entrada = (Data *)malloc(sizeof(Data));

    while (fscanf(file, "%49s %d %14s %d %d %d", 
                 paciente.nome, &paciente.idade, paciente.RG,
                 &paciente.entrada->dia, &paciente.entrada->mes,
                 &paciente.entrada->ano) == 6) {
        
        EFila *novo = (EFila*)malloc(sizeof(EFila));
        novo->Dados = (Registro*)malloc(sizeof(Registro));
        novo->Dados->entrada = (Data*)malloc(sizeof(Data));
        
        // Copia os dados individualmente
        strcpy(novo->Dados->nome, paciente.nome);
        novo->Dados->idade = paciente.idade;
        strcpy(novo->Dados->RG, paciente.RG);
        novo->Dados->entrada->dia = paciente.entrada->dia;
        novo->Dados->entrada->mes = paciente.entrada->mes;
        novo->Dados->entrada->ano = paciente.entrada->ano;
        
        novo->Proximo = NULL;

        // insere o paciente tambem na lista de paciente cadastrados
        inserePaciente(lista, novo->Dados);

        if (filaVazia(f)) {
            f->Head = novo;
            f->Tail = novo;
        } else {
            f->Tail->Proximo = novo;
            f->Tail = novo;
        }
    }

    free(paciente.entrada);
    fclose(file);
    printf("\n");
    printf("\n");
    printf("========================================================\n");
    printf("Dados carregados com sucesso.\n");
    printf("========================================================\n");
    printf("\n");
}

void salvarDados(Fila *f) {
    FILE *file = fopen("dados_pacientes.txt", "w");
    if (!file) {
        printf("\n");
        printf("\n");
        printf("========================================================\n");
        printf("Erro ao abrir o arquivo para escrita.\n");
        printf("========================================================\n");
        printf("\n");
        return;
    }

    EFila *atual = f->Head;
    while (atual != NULL) {
        Registro p = *(atual->Dados);
        fprintf(file, "%s %d %s %d %d %d\n", 
                p.nome, p.idade, p.RG,
                p.entrada->dia, p.entrada->mes, p.entrada->ano);
        atual = atual->Proximo;
    }

    fclose(file);
    printf("\n");
    printf("\n");
    printf("========================================================\n");
    printf("Dados escritos e salvos com sucesso.\n");
    printf("========================================================\n");
    printf("\n");
}

// Função para liberar a memória da fila
void liberarFila(Fila *f) {
    EFila *atual = f->Head;
    while (atual != NULL) {
        EFila *temp = atual;
        atual = atual->Proximo;
        free(temp->Dados->entrada);
        free(temp->Dados);
        free(temp);
    }
    f->Head = NULL;
    f->Tail = NULL;
}


void mostrarInformacoes() {
  printf("\n");
  printf("\n");
  printf("\n================ Informações do Trabalho ================\n");
  printf("Projeto: Sistema de Gerenciamento de Saúde\n");
  printf("Grupo:\n");
  printf("Willian Verenka RA: 22.124.081-5\n");
  printf("João Vitor Sitta Giopatto RA: 22.123.054-3\n");
  printf("Ciclo: 4º Semestre\n");
  printf("Disciplina: Estrutura de Dados CC4652\n");
  printf("11/11/2024\n");
  printf("========================================================\n");
  printf("\n");
}



void exibirMenuCadastro(){
    printf("\n======= Cadastro =======\n");
    printf("1. Cadastrar Paciente\n");
    printf("2. Consultar Paciente\n");
    printf("3. Mostrar Lista de Pacientes\n");
    printf("4. Atualizar Dados de Paciente\n");
    printf("5. Remover Paciente\n");
    printf("0. Sair\n");
}

void menuCadastro(Lista* lista){
  int opcao;
  do{
    exibirMenuCadastro();
    scanf("%d", &opcao);
    switch (opcao){
      case 1:
        cadastrarPaciente(lista);
        break;
      case 2:
        consultarPaciente(lista);
        break;
      case 3:
        mostrarLista(lista);
        break;
      case 4:
        atualizarPaciente(lista);
        break;
      case 5:
        removerPaciente(lista);
        break;
      case 0:
        printf("Voltando...\n");
        break;
      default:
        printf("Opção inválida! Por favor, escolha uma opção válida.\n");
        break;
    }
  }
  while(opcao != 0);

}

void InserirPacientesNaArvore(ABB* arvore, Lista* lista, Chave chave){
  ELista* atual = lista->inicio;
  while (atual != NULL) {
    abb_inserir(arvore, atual->dados, chave);
    atual = atual->proximo;
  }
}

void exibirMenuPesquisa(){
    printf("\n======= Pesquisa =======\n");
    printf("1. Mostrar registros ordenados por ano de registro\n");
    printf("2. Mostrar registros ordenados por mês de registro\n");
    printf("3. Mostrar registros ordenados por dia de registro\n");
    printf("4. Mostrar registros ordenados por idade do paciente\n");
    printf("0. Sair\n");
}

void menuPesquisa(Lista* lista){
  int opcao;
  ABB* arvore = (ABB*)malloc(sizeof(ABB));
  abb_inicializar(arvore);
  do{
    exibirMenuPesquisa();
    scanf("%d", &opcao);

    if (arvore->raiz != NULL) {
          liberarABB(arvore);
          abb_inicializar(arvore);
      }

    switch (opcao){
      case 1:
        InserirPacientesNaArvore(arvore, lista, ANO);
        break;
      case 2:
        InserirPacientesNaArvore(arvore, lista, MES);
        break;
      case 3:
        InserirPacientesNaArvore(arvore, lista, DIA);
        break;
      case 4:
        InserirPacientesNaArvore(arvore, lista, IDADE);
        break;
      case 0:
        printf("Voltando...\n");
        break;
      default:
        printf("Opção inválida! Por favor, escolha uma opção válida.\n");
        break;
    }
    imprimirEmOrdem(arvore->raiz);
  }
  while(opcao != 0);
}

void exibeMenuAtendimento(){
    printf("\n======= Atendimento =======\n");
    printf("1. Enfileirar Paciente\n");
    printf("2. Desenfileirar Paciente\n");
    printf("3. Mostrar Fila de Pacientes\n");
    printf("0. Sair\n");
}	

void menuAtendimento(Fila* filaPacientes, Lista* lista, Stack *pilha){
    int opcao;
    do{
        exibeMenuAtendimento();
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                mostrarLista(lista);

                if(lista->qtde == 0){
                    break;
                }

                char RG[15];
                printf("Digite o RG do paciente cadastrado:\n");
                scanf(" %14s", RG);

                Registro* paciente = buscarPaciente(lista, RG);

                if (paciente == NULL){
                    printf("Paciente não encontrado!\n");
                    break;
                }
                
                enfileirar(filaPacientes, *paciente, pilha);
                break;
            case 2:
                desenfileirar(filaPacientes, pilha);
                break;
            case 3:
                mostrarFila(filaPacientes);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }
    }
    while(opcao != 0);
}

void exibirMenu() {
  printf("\n======= Sistema de Saúde  =======\n");
  printf("1. Cadastro\n");
  printf("2. Atendimento\n");
  printf("3. Pesquisa\n");
  printf("4. Desfazer Última Operação\n");
  printf("5. Carregar Dados\n");
  printf("6. Salvar Dados\n");
  printf("7. Sobre\n");
  printf("0. Sair\n");
  printf("Escolha uma opção: \n");
}

int main() {
    int opcao;
    Fila filaPacientes;
    Stack *pilhaOperacoes = criar_pilha();
    Lista* lista = criarLista();


    inicializarFila(&filaPacientes);

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: {
            menuCadastro(lista);
            break;
        }
        case 2:
            menuAtendimento(&filaPacientes, lista, pilhaOperacoes);
            break;
        case 3:
            menuPesquisa(lista);
            break;
        case 4:
            desfazerOperacao(&filaPacientes, pilhaOperacoes);
            break;
        case 5:
            carregarDados(&filaPacientes, lista);
            break;
        case 6:
            salvarDados(&filaPacientes);
            break;
        case 7:
            mostrarInformacoes();
            break;
        case 0:
            printf("========================================================\n");
            printf("Saindo do sistema...\n");
            printf("========================================================\n");
            printf("\n");
            liberarFila(&filaPacientes);
            break;
        default:
            printf("========================================================\n");
            printf("Opção inválida! Por favor, escolha uma opção válida.\n");
            printf("========================================================\n");
            printf("\n");
            break;
        }
    } while (opcao != 0);

    while (pilhaOperacoes->qtde > 0) {
        pop(pilhaOperacoes);
    }
    free(pilhaOperacoes);

    return 0;
}