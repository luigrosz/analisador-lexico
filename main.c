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
#define MAX_LEXEMA 256

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
  Q13,
  Q14,
  Q15,
  Q16,
  Q17,
  Q18,
  Q19,
  Q20,
  Q21,
  Q22,
  Q23,
  Q24,
  Q25,
  Q26,
  Q27,
  Q28,
  Q29,
  Q30,
  Q31,
  Q32,
  Q33,
  Q34,
  Q35,
  Q36,
  Q37,
  Q38,
  Q39,
  Q40,
  Q41,
  Q42,
  Q43,
  Q44,
  Q45,
  Q46,
  Q47,
  Q48,
  Q49,
  Q50,
  Q51,
  Q52,
  Q53,
  Q54,
  Q55,
  Q56,
  Q57,
  Q58,
  Q59,
  Q60,
  Q61,
  Q62,
  Q63,
  Q64,
  NUM_ESTADOS
};

enum Colunas {
  C_SP,
  C_LETRA_OUTRA,
  C_DIGITO,
  C_UNDER,
  C_MAIS,
  C_DIV,
  C_MULT,
  C_LBRACE,
  C_RBRACE,
  C_LPAREN,
  C_RPAREN,
  C_PONTO,
  C_MENOS,
  C_c,
  C_d,
  C_e,
  C_f,
  C_i,
  C_o,
  C_r,
  C_v,
  C_w,
  C_h,
  C_s,
  C_a,
  C_u,
  C_l,
  C_t,
  C_n,
  C_b,
  C_OUTRO,
  NUM_COLUNAS
};

int tabela_transicao[NUM_ESTADOS][NUM_COLUNAS];
int tokens_finais[NUM_ESTADOS];

int get_coluna(char ch) {
  if (isspace(ch))
    return C_SP;
  if (isdigit(ch))
    return C_DIGITO;
  if (ch == '_')
    return C_UNDER;
  if (ch == '+')
    return C_MAIS;
  if (ch == '/')
    return C_DIV;
  if (ch == '*')
    return C_MULT;
  if (ch == '{')
    return C_LBRACE;
  if (ch == '}')
    return C_RBRACE;
  if (ch == '(')
    return C_LPAREN;
  if (ch == ')')
    return C_RPAREN;
  if (ch == '.')
    return C_PONTO;
  if (ch == '-')
    return C_MENOS;

  switch (tolower(ch)) {
  case 'c':
    return C_c;
  case 'd':
    return C_d;
  case 'e':
    return C_e;
  case 'f':
    return C_f;
  case 'i':
    return C_i;
  case 'o':
    return C_o;
  case 'r':
    return C_r;
  case 'v':
    return C_v;
  case 'w':
    return C_w;
  case 'h':
    return C_h;
  case 's':
    return C_s;
  case 'a':
    return C_a;
  case 'u':
    return C_u;
  case 'l':
    return C_l;
  case 't':
    return C_t;
  case 'n':
    return C_n;
  case 'b':
    return C_b;
  }

  if (isalpha(ch))
    return C_LETRA_OUTRA;
  return C_OUTRO;
}

void set_transicoes_q1(int estado) {
  for (int j = C_LETRA_OUTRA; j <= C_b; j++)
    tabela_transicao[estado][j] = Q1;
  tabela_transicao[estado][C_DIGITO] = Q1;
  tabela_transicao[estado][C_UNDER] = Q1;
}

void inicializar_dfa() {
  for (int i = 0; i < NUM_ESTADOS; i++) {
    for (int j = 0; j < NUM_COLUNAS; j++) {
      tabela_transicao[i][j] = -1;
    }
    tokens_finais[i] = 0;
  }

  tabela_transicao[Q0][C_SP] = Q0;
  tabela_transicao[Q0][C_LETRA_OUTRA] = Q1;
  tabela_transicao[Q0][C_DIGITO] = Q2;
  tabela_transicao[Q0][C_UNDER] = Q1;
  tabela_transicao[Q0][C_MAIS] = Q3;
  tabela_transicao[Q0][C_DIV] = Q4;
  tabela_transicao[Q0][C_MULT] = Q3;
  tabela_transicao[Q0][C_LBRACE] = Q5;
  tabela_transicao[Q0][C_RBRACE] = Q6;
  tabela_transicao[Q0][C_LPAREN] = Q7;
  tabela_transicao[Q0][C_RPAREN] = Q8;
  tabela_transicao[Q0][C_MENOS] = Q3;
  tabela_transicao[Q0][C_c] = Q13;
  tabela_transicao[Q0][C_d] = Q24;
  tabela_transicao[Q0][C_e] = Q18;
  tabela_transicao[Q0][C_f] = Q36;
  tabela_transicao[Q0][C_i] = Q17;
  tabela_transicao[Q0][C_r] = Q59;
  tabela_transicao[Q0][C_v] = Q27;
  tabela_transicao[Q0][C_w] = Q49;
  tabela_transicao[Q0][C_h] = Q1;
  tabela_transicao[Q0][C_s] = Q1;
  tabela_transicao[Q0][C_a] = Q1;
  tabela_transicao[Q0][C_u] = Q1;
  tabela_transicao[Q0][C_l] = Q1;
  tabela_transicao[Q0][C_t] = Q1;
  tabela_transicao[Q0][C_n] = Q1;
  tabela_transicao[Q0][C_b] = Q1;
  tabela_transicao[Q0][C_o] = Q1;
  tabela_transicao[Q0][C_OUTRO] = Q0;

  set_transicoes_q1(Q1);

  tabela_transicao[Q2][C_DIGITO] = Q2;
  tabela_transicao[Q2][C_PONTO] = Q9;

  tabela_transicao[Q4][C_MULT] = Q10;

  tabela_transicao[Q9][C_DIGITO] = Q9;

  for (int j = 0; j < NUM_COLUNAS; j++)
    tabela_transicao[Q10][j] = Q10;
  tabela_transicao[Q10][C_MULT] = Q11;

  for (int j = 0; j < NUM_COLUNAS; j++)
    tabela_transicao[Q11][j] = Q10;
  tabela_transicao[Q11][C_MULT] = Q11;
  tabela_transicao[Q11][C_DIV] = Q12;

  set_transicoes_q1(Q13);
  tabela_transicao[Q13][C_h] = Q14;
  tabela_transicao[Q13][C_a] = Q31;
  set_transicoes_q1(Q14);
  tabela_transicao[Q14][C_a] = Q15;
  set_transicoes_q1(Q15);
  tabela_transicao[Q15][C_r] = Q16;
  set_transicoes_q1(Q16);
  set_transicoes_q1(Q17);
  tabela_transicao[Q17][C_f] = Q21;
  tabela_transicao[Q17][C_n] = Q22;
  set_transicoes_q1(Q18);
  tabela_transicao[Q18][C_l] = Q19;
  set_transicoes_q1(Q19);
  tabela_transicao[Q19][C_s] = Q20;
  set_transicoes_q1(Q20);
  tabela_transicao[Q20][C_e] = Q64;
  set_transicoes_q1(Q21);
  set_transicoes_q1(Q22);
  tabela_transicao[Q22][C_t] = Q23;
  set_transicoes_q1(Q23);
  set_transicoes_q1(Q24);
  tabela_transicao[Q24][C_o] = Q25;
  set_transicoes_q1(Q25);
  tabela_transicao[Q25][C_d] = Q26;
  tabela_transicao[Q25][C_u] = Q54;
  set_transicoes_q1(Q26);
  set_transicoes_q1(Q27);
  tabela_transicao[Q27][C_o] = Q28;
  set_transicoes_q1(Q28);
  tabela_transicao[Q28][C_i] = Q29;
  set_transicoes_q1(Q29);
  tabela_transicao[Q29][C_d] = Q30;
  set_transicoes_q1(Q30);
  set_transicoes_q1(Q31);
  tabela_transicao[Q31][C_s] = Q32;
  set_transicoes_q1(Q32);
  tabela_transicao[Q32][C_e] = Q35;
  set_transicoes_q1(Q35);
  set_transicoes_q1(Q36);
  tabela_transicao[Q36][C_l] = Q37;
  tabela_transicao[Q36][C_o] = Q43;
  set_transicoes_q1(Q37);
  tabela_transicao[Q37][C_o] = Q38;
  set_transicoes_q1(Q38);
  tabela_transicao[Q38][C_a] = Q39;
  set_transicoes_q1(Q39);
  tabela_transicao[Q39][C_t] = Q42;
  set_transicoes_q1(Q42);
  set_transicoes_q1(Q43);
  tabela_transicao[Q43][C_r] = Q45;
  set_transicoes_q1(Q45);
  set_transicoes_q1(Q49);
  tabela_transicao[Q49][C_h] = Q50;
  set_transicoes_q1(Q50);
  tabela_transicao[Q50][C_i] = Q51;
  set_transicoes_q1(Q51);
  tabela_transicao[Q51][C_l] = Q52;
  set_transicoes_q1(Q52);
  tabela_transicao[Q52][C_e] = Q53;
  set_transicoes_q1(Q53);
  set_transicoes_q1(Q54);
  tabela_transicao[Q54][C_b] = Q55;
  set_transicoes_q1(Q55);
  tabela_transicao[Q55][C_l] = Q56;
  set_transicoes_q1(Q56);
  tabela_transicao[Q56][C_e] = Q58;
  set_transicoes_q1(Q58);
  set_transicoes_q1(Q59);
  tabela_transicao[Q59][C_e] = Q60;
  set_transicoes_q1(Q60);
  tabela_transicao[Q60][C_t] = Q61;
  set_transicoes_q1(Q61);
  tabela_transicao[Q61][C_u] = Q62;
  set_transicoes_q1(Q62);
  tabela_transicao[Q62][C_r] = Q63;
  set_transicoes_q1(Q63);
  set_transicoes_q1(Q64);

  tokens_finais[Q1] = T_IDENTIFICADOR;
  tokens_finais[Q2] = T_NUMERAL;
  tokens_finais[Q3] = T_OPERADOR;
  tokens_finais[Q4] = T_OPERADOR;
  tokens_finais[Q5] = T_INICIO_ESCOPO;
  tokens_finais[Q6] = T_FIM_ESCOPO;
  tokens_finais[Q7] = T_INICIO_EQ;
  tokens_finais[Q8] = T_FIM_EQ;
  tokens_finais[Q9] = T_NUMERAL;
  tokens_finais[Q12] = T_COMENTARIO;
  tokens_finais[Q13] = T_IDENTIFICADOR;
  tokens_finais[Q14] = T_IDENTIFICADOR;
  tokens_finais[Q15] = T_IDENTIFICADOR;
  tokens_finais[Q16] = T_TIPO_DADO;
  tokens_finais[Q17] = T_IDENTIFICADOR;
  tokens_finais[Q18] = T_IDENTIFICADOR;
  tokens_finais[Q19] = T_IDENTIFICADOR;
  tokens_finais[Q20] = T_IDENTIFICADOR;
  tokens_finais[Q21] = T_DECISAO;
  tokens_finais[Q22] = T_IDENTIFICADOR;
  tokens_finais[Q23] = T_TIPO_DADO;
  tokens_finais[Q24] = T_IDENTIFICADOR;
  tokens_finais[Q25] = T_IDENTIFICADOR;
  tokens_finais[Q26] = T_LACO;
  tokens_finais[Q27] = T_IDENTIFICADOR;
  tokens_finais[Q28] = T_IDENTIFICADOR;
  tokens_finais[Q29] = T_IDENTIFICADOR;
  tokens_finais[Q30] = T_TIPO_DADO;
  tokens_finais[Q31] = T_IDENTIFICADOR;
  tokens_finais[Q32] = T_IDENTIFICADOR;
  tokens_finais[Q35] = T_DECISAO;
  tokens_finais[Q36] = T_IDENTIFICADOR;
  tokens_finais[Q37] = T_IDENTIFICADOR;
  tokens_finais[Q38] = T_IDENTIFICADOR;
  tokens_finais[Q39] = T_IDENTIFICADOR;
  tokens_finais[Q42] = T_TIPO_DADO;
  tokens_finais[Q43] = T_IDENTIFICADOR;
  tokens_finais[Q45] = T_LACO;
  tokens_finais[Q49] = T_IDENTIFICADOR;
  tokens_finais[Q50] = T_IDENTIFICADOR;
  tokens_finais[Q51] = T_IDENTIFICADOR;
  tokens_finais[Q52] = T_IDENTIFICADOR;
  tokens_finais[Q53] = T_LACO;
  tokens_finais[Q54] = T_IDENTIFICADOR;
  tokens_finais[Q55] = T_IDENTIFICADOR;
  tokens_finais[Q56] = T_IDENTIFICADOR;
  tokens_finais[Q58] = T_TIPO_DADO;
  tokens_finais[Q59] = T_IDENTIFICADOR;
  tokens_finais[Q60] = T_IDENTIFICADOR;
  tokens_finais[Q61] = T_IDENTIFICADOR;
  tokens_finais[Q62] = T_IDENTIFICADOR;
  tokens_finais[Q63] = T_RETORNO;
  tokens_finais[Q64] = T_DECISAO;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Uso: %s <arquivo_de_entrada> <arquivo_de_saida>\n",
            argv[0]);
    return 1;
  }
  FILE *arquivo_entrada = fopen(argv[1], "r");
  FILE *arquivo_saida = fopen(argv[2], "w");
  if (!arquivo_entrada || !arquivo_saida) {
    perror("Erro ao abrir arquivos");
    return 1;
  }

  inicializar_dfa();
  int c;

  while ((c = fgetc(arquivo_entrada)) != EOF) {
    if (isspace(c)) {
      continue;
    }

    char lexema_atual[MAX_LEXEMA] = {0};
    int lexema_idx = 0;
    int estado_atual = Q0;

    while (c != EOF) {
      int coluna = get_coluna(c);
      int proximo_estado = tabela_transicao[estado_atual][coluna];

      if (proximo_estado == -1) {
        ungetc(c, arquivo_entrada);
        break;
      }

      lexema_atual[lexema_idx++] = c;
      estado_atual = proximo_estado;

      c = fgetc(arquivo_entrada);
    }

    lexema_atual[lexema_idx] = '\0';
    int token = tokens_finais[estado_atual];

    if (token != 0) {
      fprintf(arquivo_saida, "%d ", token);
    } else if (lexema_idx > 0) {
      fprintf(stderr, "Erro: Lexema nao reconhecido '%s'\n", lexema_atual);
    }
  }

  printf("Analise lexica concluida. Verifique o arquivo '%s'.\n", argv[2]);
  fclose(arquivo_entrada);
  fclose(arquivo_saida);
  return 0;
}
