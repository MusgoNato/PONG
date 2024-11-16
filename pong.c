/*gcc pong.c -o pong.exe funcoes.c conio_v3.2.4.c console_v1.5.5.c -Wall -pedantic -Wextra -Werror*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <windows.h>
# include "conio_v3.2.4.h"
# include "console_v1.5.5.h"
# include "funcoes.h"

/*Inicio JOGO*/
int main(int argc, char *argv[])
{
    JANELA janela;
    JOGADOR_1 player_1;
    JOGADOR_2 player_2;
    EVENTOS_DO_TECLADO teclas_evento;
    BOLINHA bola;

    argc = argc;
    argv = argv;

    /*Atribuicao de valores para minhas coordenadas*/
    janela.Janela.X = 1;
    janela.Janela.Y = 1;

    teclas_evento.saida = 1;

    player_1.coordenada_player1.X = ESPACAMENTO_BARRA_JOGADOR + 1;
    player_1.coordenada_player1.Y = (LINHAS - GOL) / 2;

    player_2.coordenada_player2.X = COLUNAS + 1;
    player_2.coordenada_player2.Y = (LINHAS - GOL) / 2;

    teclas_evento.controle_player_1 = 1;
    teclas_evento.controle_player_2 = 1;

    bola.coordenada_bolinha.X = COLUNAS/2;
    bola.coordenada_bolinha.Y = LINHAS/2;

    /*Randomiza a direcao*/
    srand(time(NULL));
    bola.direcao = 1 + rand() % 8;

    /*limpa a tela*/
    clrscr();
    setCursorStatus(_NOCURSOR);

    Cria_Janela(&janela);

    Area_do_gol(&janela, &player_1, &player_2);

    do
    {
        Pega_entrada(&teclas_evento, &player_1, &player_2, &janela);

        /*Imprime somente uma vez quando o jogador mover uma das barras*/
        if(teclas_evento.controle_player_1)
        {
            Desenha_Jogador_1(&player_1);
            teclas_evento.controle_player_1 = 0;
        }

        if(teclas_evento.controle_player_2)
        {
            Desenha_Jogador_2(&player_2);
            teclas_evento.controle_player_2 = 0;
        }

        Desenha_direcao_bolinha(&bola);
        Altera_direcao_da_bolinha(&bola, &janela);

        Sleep(TEMPO_DO_JOGO);

    }while(teclas_evento.saida);
    
    /*Volta ao padrao do CMD*/
    textbackground(BLACK);
    textcolor(LIGHTGRAY);
    setCursorStatus(_SOLIDCURSOR);

    return 0;

}