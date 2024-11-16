# include <stdio.h>
# include <stdlib.h>
# include "conio_v3.2.4.h"
# include "console_v1.5.5.h"


/*Constantes*/
# define LINHAS 20
# define COLUNAS 40
# define GOL 8 
# define ESPACAMENTO_BARRA_JOGADOR 10
# define TAM_BARRA_JOGADOR 3
# define TEMPO_DO_JOGO 20

/*Registros*/
typedef struct _janela
{
    COORD Janela;
}JANELA;

typedef struct _player_1
{
    COORD coordenada_player1;
    COORD gol;
}JOGADOR_1;

typedef struct _player_2
{
    COORD coordenada_player2;
    COORD gol;
}JOGADOR_2;

typedef struct _eventos
{
    EVENTO teclas;
    int saida;
    int controle_player_1;
    int controle_player_2;
}EVENTOS_DO_TECLADO;

typedef struct _bola
{
    COORD coordenada_bolinha;
    int direcao;
}BOLINHA;

enum
{
    DIAGONAL_SUPERIOR_ESQUERDA = 1,
    DIAGONAL_SUPERIOR_DIREITA,
    ESQUERDA,
    DIREITA,
    CIMA,
    BAIXO,
    DIAGONAL_INFERIOR_DIREITA,
    DIAGONAL_INFERIOR_ESQUERDA
};


void Pega_entrada(EVENTOS_DO_TECLADO *, JOGADOR_1 *, JOGADOR_2 *, JANELA *);

void Cria_Janela(JANELA *);
void Area_do_gol(JANELA *, JOGADOR_1 *, JOGADOR_2 *);

void Desenha_Jogador_1(JOGADOR_1 *);
void Desenha_Jogador_2(JOGADOR_2 *);
void Apaga_jogador_1(JOGADOR_1 *);
void Apaga_jogador_2(JOGADOR_2 *);

void Desenha_direcao_bolinha(BOLINHA *);
void Altera_direcao_da_bolinha(BOLINHA *, JANELA *);
