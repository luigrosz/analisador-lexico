#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T_IDENTIFICADOR 1
#define T_NUMERAL 2
#define T_COMENTARIO 3
#define T_TIPO_DADO 4
#define T_DECISAO 5
#define T_LACO 6
#define T_OPERADOR 7
#define T_RETORNO 8
#define T_INICIO_ESCOPO 9
#define T_FIM_ESCOPO 10
#define T_INICIO_EQ 11
#define T_FIM_EQ 12

enum Estados {
  Q0,
  Q1,
  Q2,
  Q3,
  Q4,
  Q5,
  Q6,
  Q7,
  Q8,
  Q9,
  Q10,
  Q11,
  Q12,
  NUM_ESTADOS
};

enum Colunas {
  C_LETRA,
  C_DIGITO,
  C_UNDER,
  C_MAIS,
  C_DIV,
  C_MENOS,
  C_MULT,
  C_LBRACE,
  C_RBRACE,
  C_LPAREN,
  C_RPAREN,
  C_PONTO,
  C_MENOR,
  C_MAIOR,
  C_IGUAL,
  C_EXC,
  C_ESPACO,
  C_OUTRO
};
#define NUM_COLUNAS 18

int get_coluna(char c) {
  if (isalpha(c))
    return C_LETRA;
  if (isdigit(c))
    return C_DIGITO;
  if (c == '_')
    return C_UNDER;
  if (c == '+')
    return C_MAIS;
  if (c == '/')
    return C_DIV;
  if (c == '-')
    return C_MENOS;
  if (c == '*')
    return C_MULT;
  if (c == '{')
    return C_LBRACE;
  if (c == '}')
    return C_RBRACE;
  if (c == '(')
    return C_LPAREN;
  if (c == ')')
    return C_RPAREN;
  if (c == '.')
    return C_PONTO;
  if (c == '<')
    return C_MENOR;
  if (c == '>')
    return C_MAIOR;
  if (c == '=')
    return C_IGUAL;
  if (c == '!')
    return C_EXC;
  if (isspace(c))
    return C_ESPACO;
  return C_OUTRO;
}

int tabela_transicao[NUM_ESTADOS][NUM_COLUNAS];

int tokens_finais[NUM_ESTADOS];

void inicializar_dfa() {
  for (int i = 0; i < NUM_ESTADOS; i++) {
    for (int j = 0; j < NUM_COLUNAS; j++) {
      tabela_transicao[i][j] = -1;
    }
    tokens_finais[i] = 0;
  }

  tabela_transicao[Q0][C_LETRA] = Q1;
  tabela_transicao[Q0][C_DIGITO] = Q2;
  tabela_transicao[Q0][C_MAIS] = Q3;
  tabela_transicao[Q0][C_DIV] = Q4;
  tabela_transicao[Q0][C_MENOS] = Q3;
  tabela_transicao[Q0][C_MULT] = Q3;
  tabela_transicao[Q0][C_LBRACE] = Q5;
  tabela_transicao[Q0][C_RBRACE] = Q6;
  tabela_transicao[Q0][C_LPAREN] = Q7;
  tabela_transicao[Q0][C_RPAREN] = Q8;
  tabela_transicao[Q0][C_MENOR] = Q3;
  tabela_transicao[Q0][C_MAIOR] = Q3;
  tabela_transicao[Q0][C_IGUAL] = Q3;
  tabela_transicao[Q0][C_EXC] = Q3;
  tabela_transicao[Q0][C_ESPACO] = Q0;
  tokens_finais[Q0] = 0;

  tabela_transicao[Q1][C_LETRA] = Q1;
  tabela_transicao[Q1][C_DIGITO] = Q1;
  tabela_transicao[Q1][C_UNDER] = Q1;
  tokens_finais[Q1] = T_IDENTIFICADOR;

  tabela_transicao[Q2][C_LETRA] = Q2;
  tabela_transicao[Q2][C_DIGITO] = Q2;
  tabela_transicao[Q2][C_PONTO] = Q9;
  tokens_finais[Q2] = T_NUMERAL;

  tokens_finais[Q3] = T_OPERADOR;

  tabela_transicao[Q4][C_MULT] = Q10;
  tokens_finais[Q4] = T_OPERADOR;

  tokens_finais[Q5] = T_INICIO_ESCOPO;

  tokens_finais[Q6] = T_FIM_ESCOPO;

  tokens_finais[Q7] = T_INICIO_EQ;

  tokens_finais[Q8] = T_FIM_EQ;

  tabela_transicao[Q9][C_DIGITO] = Q9;
  tokens_finais[Q9] = T_NUMERAL;

  tabela_transicao[Q10][C_LETRA] = Q10;
  tabela_transicao[Q10][C_DIGITO] = Q10;
  tabela_transicao[Q10][C_UNDER] = Q10;
  tabela_transicao[Q10][C_MAIS] = Q10;
  tabela_transicao[Q10][C_DIV] = Q10;
  tabela_transicao[Q10][C_MENOS] = Q10;
  tabela_transicao[Q10][C_MULT] = Q11;
  tabela_transicao[Q10][C_LBRACE] = Q10;
  tabela_transicao[Q10][C_RBRACE] = Q10;
  tabela_transicao[Q10][C_LPAREN] = Q10;
  tabela_transicao[Q10][C_RPAREN] = Q10;
  tabela_transicao[Q10][C_PONTO] = Q10;
  tabela_transicao[Q10][C_MENOR] = Q10;
  tabela_transicao[Q10][C_MAIOR] = Q10;
  tabela_transicao[Q10][C_IGUAL] = Q10;
  tabela_transicao[Q10][C_EXC] = Q10;
  tabela_transicao[Q10][C_ESPACO] = Q10;
  tabela_transicao[Q10][C_OUTRO] = Q10;
  tokens_finais[Q10] = 0;

  tabela_transicao[Q11][C_LETRA] = Q10;
  tabela_transicao[Q11][C_DIGITO] = Q10;
  tabela_transicao[Q11][C_UNDER] = Q10;
  tabela_transicao[Q11][C_MAIS] = Q10;
  tabela_transicao[Q11][C_DIV] = Q12;
  tabela_transicao[Q11][C_MENOS] = Q10;
  tabela_transicao[Q11][C_MULT] = Q11;
  tabela_transicao[Q11][C_LBRACE] = Q10;
  tabela_transicao[Q11][C_RBRACE] = Q10;
  tabela_transicao[Q11][C_LPAREN] = Q10;
  tabela_transicao[Q11][C_RPAREN] = Q10;
  tabela_transicao[Q11][C_PONTO] = Q10;
  tabela_transicao[Q11][C_MENOR] = Q10;
  tabela_transicao[Q11][C_MAIOR] = Q10;
  tabela_transicao[Q11][C_IGUAL] = Q10;
  tabela_transicao[Q11][C_EXC] = Q10;
  tabela_transicao[Q11][C_ESPACO] = Q10;
  tabela_transicao[Q11][C_OUTRO] = Q10;
  tokens_finais[Q11] = 0;

  tokens_finais[Q12] = T_COMENTARIO;
}

int get_token_palavra_reservada(const char *str) {
  if (strcmp(str, "char") == 0)
    return T_TIPO_DADO;
  if (strcmp(str, "double") == 0)
    return T_TIPO_DADO;
  if (strcmp(str, "float") == 0)
    return T_TIPO_DADO;
  if (strcmp(str, "int") == 0)
    return T_TIPO_DADO;
  if (strcmp(str, "void") == 0)
    return T_TIPO_DADO;
  if (strcmp(str, "if") == 0)
    return T_DECISAO;
  if (strcmp(str, "else") == 0)
    return T_DECISAO;
  if (strcmp(str, "case") == 0)
    return T_DECISAO;
  if (strcmp(str, "for") == 0)
    return T_LACO;
  if (strcmp(str, "while") == 0)
    return T_LACO;
  if (strcmp(str, "do") == 0)
    return T_LACO;
  if (strcmp(str, "return") == 0)
    return T_RETORNO;
  return T_IDENTIFICADOR;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Uso: %s <arquivo_de_entrada> <arquivo_de_saida>\n",
            argv[0]);
    return 1;
  }

  FILE *arquivo_entrada = fopen(argv[1], "r");
  if (!arquivo_entrada) {
    perror("Erro ao abrir o arquivo de entrada");
    return 1;
  }

  FILE *arquivo_saida = fopen(argv[2], "w");
  if (!arquivo_saida) {
    perror("Erro ao abrir o arquivo de saida");
    fclose(arquivo_entrada);
    return 1;
  }

  inicializar_dfa();

  int estado_atual = Q0;
  char lexema_atual[256];
  int lexema_idx = 0;
  int c;

  while ((c = fgetc(arquivo_entrada)) != EOF) {
    int coluna = get_coluna(c);
    int proximo_estado =
        (estado_atual >= 0) ? tabela_transicao[estado_atual][coluna] : -1;

    if (proximo_estado == -1) {
      if (lexema_idx > 0) {
        lexema_atual[lexema_idx] = '\0';
        int token_final = tokens_finais[estado_atual];

        if (token_final == T_IDENTIFICADOR) {
          token_final = get_token_palavra_reservada(lexema_atual);
        }

        if (token_final != 0) {
          fprintf(arquivo_saida, "%d ", token_final);
        } else {
          fprintf(stderr, "Erro: Lexema não reconhecido -> %s\n", lexema_atual);
        }
      }

      lexema_idx = 0;
      memset(lexema_atual, 0, sizeof(lexema_atual));

      estado_atual = tabela_transicao[Q0][coluna];
      if (estado_atual != Q0 && estado_atual != -1) {
        lexema_atual[lexema_idx++] = c;
      }

    } else {
      estado_atual = proximo_estado;
      if (!isspace(c) || estado_atual == Q10 || estado_atual == Q11) {
        lexema_atual[lexema_idx++] = c;
      }
    }
  }

  if (lexema_idx > 0) {
    lexema_atual[lexema_idx] = '\0';
    int token_final = tokens_finais[estado_atual];
    if (token_final == T_IDENTIFICADOR) {
      token_final = get_token_palavra_reservada(lexema_atual);
    }
    if (token_final != 0) {
      fprintf(arquivo_saida, "%d ", token_final);
    }
  }

  printf("Análise léxica concluída. Verifique o arquivo '%s'.\n", argv[2]);

  fclose(arquivo_entrada);
  fclose(arquivo_saida);

  return 0;
}
