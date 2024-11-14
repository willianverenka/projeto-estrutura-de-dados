#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACIENTES 15
//#define ARQUIVO_DADOS "dados.txt"

// Estruturando data de entrada
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

// Estrutura para o registro do paciente
typedef struct {
  char nome[35];
  int idade;
  char rg[15];
  Data *entrada;
} Registro;

// Definindo as operações
typedef enum { ENFILEIRAR, DESENFILEIRAR, NENHUMA_OPERACAO } Operacao;

// Estruturando celula para a struct pilha
typedef struct Celula {
  struct Celula *proximo;
  Operacao valor;
} Celula;

// Estrutura da pilha
typedef struct {
  Celula *topo;
  int qtde;
} Stack;

// Funções para manipular a pilha
Celula *criar_celula(Operacao valor) {
  Celula *celula = malloc(sizeof(Celula)); //aloca a memoria para a struct
  celula->proximo = NULL; //define o proximo valor valor como nulo
  celula->valor = valor; //define o valor da celula com o valor passado na chamada da funcao
  return celula;
}

Stack *criar_pilha() {
  Stack *pilha = malloc(sizeof(Stack)); //aloca a memoria para a pilha
  pilha->topo = NULL; //seta como nulo o topo
  pilha->qtde = 0; //inicia com quantiddade 0
  return pilha;
}

void push(Stack *pilha, Operacao valor) {
  Celula *novo = criar_celula(valor); //comeca criando uma nova celula
  novo->proximo = pilha->topo; // passa o proximo dessa nova celula como o topo da pilha 
  pilha->topo = novo; //define o topo da pilha para a nova celula
  pilha->qtde++;
}

Operacao pop(Stack *pilha) {
  if (pilha->qtde == 0) { //verifica se ha alguma operacao ja na pilha
    return NENHUMA_OPERACAO;
  }
// caso tenha, armazena o valor da operacao no topo e ajusta o ponteiro para a celula seguinte
  Operacao valor = pilha->topo->valor;
  Celula *temp = pilha->topo;
  pilha->topo = pilha->topo->proximo;
  pilha->qtde--;
  free(temp);
  return valor;
}

// Estrutura para a fila de pacientes
typedef struct {
  Registro pacientes[MAX_PACIENTES];
  int head;
  int tail;
} Fila;

// Funções para manipular a fila de pacientes
void inicializarFila(Fila *f) {
  f->head = 0;
  f->tail = -1;
}

int filaVazia(Fila *f) { return f->tail < f->head; }

int filaCheia(Fila *f) { return f->tail == MAX_PACIENTES - 1; }

void enfileirar(Fila *f, Registro paciente, Stack *pilha) {

  if (!filaCheia(f)) {

    f->pacientes[++f->tail] = paciente;

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
    Registro paciente = f->pacientes[f->head++];

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
    for (int i = f->head; i <= f->tail; i++) {

      Registro paciente = f->pacientes[i];

      printf("Nome: %s, Idade: %d, RG: %s, Data de Entrada: %02d/%02d/%04d\n",
             paciente.nome, paciente.idade, paciente.rg, paciente.entrada->dia,
             paciente.entrada->mes, paciente.entrada->ano);
    }
  }
}

void desfazerOperacao(Fila *f, Stack *pilha) {
  if (pilha->qtde == 0) { // verifica se tem alguma operacao armazenada na pilha
    printf("\n");
    printf("\n");
    printf("========================================================\n");
    printf("Não há operações para desfazer.\n");
    printf("========================================================\n");
    printf("\n");
    return;
  }

  // Operacao ultimaOperacao = pop(pilha);
  // pega a ultima operacao na pilha para fazer os laços de comparacao
  Operacao ultimaOperacao = pilha->topo->valor;
  char confirm;
  // confirma qual foi a ultima operacao realizada
  const char *descricaoOperacao = ultimaOperacao == ENFILEIRAR
                                      ? "Enfileirar paciente"
                                      : "Desenfileirar paciente";

  printf("Última operação para ser desfeita: %s\n", descricaoOperacao);
  printf("\n-----------------------------------------------\n");

  printf("Deseja realmente desfazer esta operação? (S/N): ");

  scanf(" %c", &confirm);
  // se o usuario digitar 's' ele ira remover o valor(ultima operacao) da pilha
  if (confirm == 's') {
    pop(pilha);
    // caso a ultima operacao seja enfileirar e a fila nao esteja vazia
    if (ultimaOperacao == ENFILEIRAR && !filaVazia(f)) {
      // lremove o ultimo paciente enfilerado, libera a memoria alocada e
      // decrementa o tamanho da fila
      free(f->pacientes[f->tail--].entrada);
      // f->pacientes[f->tras].entrada = NULL;
      printf("\n");
      printf("\n");
      printf("========================================================\n");
      printf("Operação de enfileirar desfeita.\n");
      printf("========================================================\n");
      printf("\n");
      // repete o processo, porem movendo o head para tras, restaurando o
      // paciente que eestava no inicio da fila
    } else if (ultimaOperacao == DESENFILEIRAR && f->head > 0) {
      f->head--;
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
    Registro paciente; // cria um novo paciente
    paciente.entrada = (Data *)malloc(sizeof(
        Data)); // aloca memoria para a data de entrada desse novo paciente
    // lendo os dados armazenados no arquivo do paciente
    if (fscanf(file, "%49s %d %14s %d %d %d", paciente.nome, &paciente.idade,
               paciente.rg, &paciente.entrada->dia, &paciente.entrada->mes,
               &paciente.entrada->ano) != 6) {
      free(paciente.entrada); // caso algum dado esteja faltando, a  memoria é
                              // liberada
      break;
    }
    f->pacientes[++f->tail] = paciente; // paciente é adicionado na fila
    //++f->tail garante que o paciente seja adicionado no proximo espaço vazio
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
  // laço para percorrer a fila e salvar os dados dos pacientes no arquivo
  for (int i = f->head; i <= f->tail; i++) {

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
      printf("Saindo do sistema. . .\n");
      printf("========================================================\n");
      printf("\n");
      break;
    default:
      printf("========================================================\n");
      printf("Opção inválida!\n");
      printf("========================================================\n");
      printf("\n");
      break;
    }
  } while (opcao != 0);

  return 0;
}
