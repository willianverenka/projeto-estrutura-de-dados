#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACIENTES 10
//#define ARQUIVO_DADOS "dados.txt"

// Estrutura para a data de entrada
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

// Estrutura para o registro do paciente
typedef struct {
  char nome[50];
  int idade;
  char rg[15];
  Data *entrada; // Ponteiro para uma estrutura Data
} Registro;

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

// Funções para manipular a pilha
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

// Estrutura para a fila de pacientes
typedef struct {
  Registro pacientes[MAX_PACIENTES];
  int frente;
  int tras;
} Fila;

// Funções para manipular a fila de pacientes
void inicializarFila(Fila *f) {
  f->frente = 0;
  f->tras = -1;
}

int filaVazia(Fila *f) { return f->tras < f->frente; }

int filaCheia(Fila *f) { return f->tras == MAX_PACIENTES - 1; }

void enfileirar(Fila *f, Registro paciente, Stack *pilha) {

  if (!filaCheia(f)) {

    f->pacientes[++f->tras] = paciente;

    push(pilha, ENFILEIRAR);
    printf("\n");
    printf("\n");
    printf("========================================================\n");
    printf("Paciente %s foi enfileirado.\n", paciente.nome);
    printf("========================================================\n");
    printf("\n");
  } else {
    printf("\n");
    printf("\n");
    printf("========================================================\n");
    printf("Erro: Fila cheia.\n");
    printf("========================================================\n");
    printf("\n");
  }
}

void desenfileirar(Fila *f, Stack *pilha) {

  if (!filaVazia(f)) {
    Registro paciente = f->pacientes[f->frente++];

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
  } else {

    printf("Fila de pacientes:\n");
    for (int i = f->frente; i <= f->tras; i++) {

      Registro p = f->pacientes[i];

      printf("Nome: %s, Idade: %d, RG: %s, Data de Entrada: %02d/%02d/%04d\n",
             p.nome, p.idade, p.rg, p.entrada->dia, p.entrada->mes,
             p.entrada->ano);
    }
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
      free(f->pacientes[f->tras--].entrada);
      printf("\n");
      printf("\n");
      printf("========================================================\n");
      printf("Operação de enfileirar desfeita.\n");
      printf("========================================================\n");
      printf("\n");

    } else if (ultimaOperacao == DESENFILEIRAR && f->frente > 0) {
      f->frente--;
      printf("\n");
      printf("\n");
      printf("========================================================\n");
      printf("Operação de desenfileirar desfeita.\n");
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

void carregarDados(Fila *f) {

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
  while (!filaCheia(f)) {
    Registro paciente;
    paciente.entrada = (Data *)malloc(sizeof(Data));

    if (fscanf(file, "%49s %d %14s %d %d %d", paciente.nome, &paciente.idade,
               paciente.rg, &paciente.entrada->dia, &paciente.entrada->mes,
               &paciente.entrada->ano) != 6) {
      free(paciente.entrada);
      break;
    }
    f->pacientes[++f->tras] = paciente;
  }

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

  for (int i = f->frente; i <= f->tras; i++) {

    Registro p = f->pacientes[i];
    fprintf(file, "%s %d %s %d %d %d\n", p.nome, p.idade, p.rg, p.entrada->dia,
            p.entrada->mes, p.entrada->ano);
  }

  fclose(file);
  printf("\n");
  printf("\n");
  printf("========================================================\n");
  printf("Dados escritos e salvos com sucesso.\n");
  printf("========================================================\n");
  printf("\n");
}

void mostrarInformacoes() {
  printf("\n");
  printf("\n");
  printf("\n================ Informações do Trabalho ================\n");
  printf("Projeto: Sistema de Gerenciamento de Saúde\n");
  printf("Grupo:\n");
  printf("William Verenka RA: 22.124.081-5\n");
  printf("João Vitor Sitta Giopatto RA: 22.123.054-3\n");
  printf("Ciclo: 4º Semestre\n");
  printf("Disciplina: Estrutura de Dados CC4652\n");
  printf("11/11/2024\n");
  printf("========================================================\n");
  printf("\n");
}

// Exibe o menu
void exibirMenu() {
  printf("\n======= Sistema de Saúde  =======\n");
  printf("1. Enfileirar Paciente\n");
  printf("2. Desenfileirar Paciente\n");
  printf("3. Mostrar Fila de Pacientes\n");
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

  inicializarFila(&filaPacientes);

  do {
    exibirMenu();
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      Registro paciente;
      paciente.entrada = (Data *)malloc(sizeof(Data));

      printf("Nome: ");
      scanf(" %49[^\n]", paciente.nome);
      printf("Idade: ");
      scanf("%d", &paciente.idade);
      printf("RG: ");
      scanf(" %14s", paciente.rg);
      printf("Data de Entrada (dd mm aaaa): ");
      scanf("%d %d %d", &paciente.entrada->dia, &paciente.entrada->mes,
            &paciente.entrada->ano);

      enfileirar(&filaPacientes, paciente, pilhaOperacoes);
      break;
    }
    case 2:
      desenfileirar(&filaPacientes, pilhaOperacoes);
      break;
    case 3:
      mostrarFila(&filaPacientes);
      break;
    case 4:
      desfazerOperacao(&filaPacientes, pilhaOperacoes);
      break;
    case 5:
      carregarDados(&filaPacientes);
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
      break;
    default:
      printf("========================================================\n");
      printf("Opção inválida! Por favor, escolha uma opção válida.\n");
      printf("========================================================\n");
      printf("\n");
      break;
    }
  } while (opcao != 0);

  return 0;
}
