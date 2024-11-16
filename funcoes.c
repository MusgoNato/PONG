# include <stdio.h>
# include <time.h>
# include "conio_v3.2.4.h"  
# include "console_v1.5.5.h"   
# include "funcoes.h"

/*Responsavel pela janela*/
void Cria_Janela(JANELA *janela)
{
    int i;

    textbackground(BLUE);

    /*Criacao da coluna superior*/
    for(i = 0; i < COLUNAS; i++)
    {
        gotoxy(janela->Janela.X + i, janela->Janela.Y);
        printf(" ");
    }

    /*Criacao da esquerda*/
    for(i = 0; i < LINHAS; i++)
    {
        gotoxy(janela->Janela.X, janela->Janela.Y + i);
        printf(" ");
    }

    /*Criacao da coluna da direita*/
    for(i = 0; i < LINHAS; i++)
    {
        gotoxy(janela->Janela.X + COLUNAS, janela->Janela.Y + i);
        printf(" ");
    }

    /*Coluna inferior*/
    for(i = 0; i <= COLUNAS; i++)
    {
        gotoxy(janela->Janela.X + i, janela->Janela.Y + LINHAS);
        printf(" ");
    }
}

/*Cria a area que sera o gol*/
void Area_do_gol(JANELA *janela, JOGADOR_1 *player_1, JOGADOR_2 *player_2)
{
    int i;  

    janela = janela;

    player_1->gol.X = 1;
    player_1->gol.Y = (LINHAS - GOL) / 2;

    player_2->gol.X = COLUNAS + 1;
    player_2->gol.Y = (LINHAS - GOL) / 2;

    textbackground(WHITE);

    /*Area esquerda*/
    for(i = 0; i < GOL; i++)
    {
        gotoxy(player_1->gol.X, player_1->gol.Y + i);
        printf(" ");
    }

    /*Area direita*/
    for(i = 0; i < GOL; i++)
    {
        gotoxy(player_2->gol.X, player_2->gol.Y + i);
        printf(" ");
    }

}

/*Desenha meu jogador 1*/
void Desenha_Jogador_1(JOGADOR_1 *jogador_1)
{
    int i;
    for(i = 0; i < TAM_BARRA_JOGADOR; i++)
    {
        textbackground(YELLOW);
        gotoxy(jogador_1->coordenada_player1.X, jogador_1->coordenada_player1.Y + i);
        printf(" ");
    }
}

/*Desenha jogador 2*/
void Desenha_Jogador_2(JOGADOR_2 *jogador_2)
{
    int i;

    for(i = 0; i < TAM_BARRA_JOGADOR; i++)
    {
        textbackground(GREEN);
        gotoxy(jogador_2->coordenada_player2.X - ESPACAMENTO_BARRA_JOGADOR, jogador_2->coordenada_player2.Y + i);
        printf(" ");
    }    

    
}

/*Pega entrada do teclado, para saber qual barra sera movida*/
void Pega_entrada(EVENTOS_DO_TECLADO *teclas_evento, JOGADOR_1 *jogador_1, JOGADOR_2 *jogador_2, JANELA *janela)
{
    /*Verifico se ha um hit do teclado*/
    if(hit(KEYBOARD_HIT))
    {
        /*Pego a tecla do teclado*/
        teclas_evento->teclas = Evento();
    
        /*Verifico se eh um evento do teclado*/
        if(teclas_evento->teclas.tipo_evento & KEY_EVENT)
        {
            /*Verifico se esta libreada a tecla*/
            if(teclas_evento->teclas.teclado.status_tecla == LIBERADA)
            {                
                switch(teclas_evento->teclas.teclado.key_code)
                {
                    /*Movimento jogador 2*/
                    case SETA_PARA_CIMA:
                    {
                        if(jogador_2->coordenada_player2.Y >= janela->Janela.Y + 2)
                        {
                            teclas_evento->controle_player_2 = 1;
                            Apaga_jogador_2(jogador_2);

                            jogador_2->coordenada_player2.Y -= 1;
                        }

                        break;
                    }

                    case SETA_PARA_BAIXO:
                    {
                        if(jogador_2->coordenada_player2.Y <= COLUNAS - LINHAS - TAM_BARRA_JOGADOR)
                        {
                            teclas_evento->controle_player_2 = 1;
                            Apaga_jogador_2(jogador_2);

                            jogador_2->coordenada_player2.Y += 1;
                        }
                        
                        break;
                    }
                }

                /*Pego as teclas*/
                switch(teclas_evento->teclas.teclado.ascii_code)
                {   
                    case ESC:
                    {
                        teclas_evento->saida = 0;
                        break;
                    }

                    /*Movimentos jogador 1*/
                    case 'a':
                    {
                        if(jogador_1->coordenada_player1.Y >= janela->Janela.Y + 2)
                        {
                            teclas_evento->controle_player_1 = 1;
                            Apaga_jogador_1(jogador_1);

                            jogador_1->coordenada_player1.Y -= 1;
                        }

                        break;
                    }

                    case 'z':
                    {
                        if(jogador_1->coordenada_player1.Y <= COLUNAS - LINHAS - TAM_BARRA_JOGADOR)
                        {
                            teclas_evento->controle_player_1 = 1;
                            Apaga_jogador_1(jogador_1);

                            jogador_1->coordenada_player1.Y += 1;
                        }
                        
                        break;
                    }
                }
            }
        }
    }
}

void Apaga_jogador_1(JOGADOR_1 *jogador_1)
{
    int i;
    for(i = 0; i < TAM_BARRA_JOGADOR; i++)
    {
        textbackground(BLACK);
        gotoxy(jogador_1->coordenada_player1.X, jogador_1->coordenada_player1.Y + i);
        printf(" ");
    }
}

void Apaga_jogador_2(JOGADOR_2 *jogador_2)
{
    int i;
    for(i = 0; i < TAM_BARRA_JOGADOR; i++)
    {
        textbackground(BLACK);
        gotoxy(jogador_2->coordenada_player2.X - ESPACAMENTO_BARRA_JOGADOR, jogador_2->coordenada_player2.Y + i);
        printf(" ");
    }
}

void Altera_direcao_da_bolinha(BOLINHA *bola, JANELA *janela)
{
    /*Referente a cima e baixo*/
    if(bola->coordenada_bolinha.Y < janela->Janela.Y + 2 && bola->direcao == CIMA)
    {
        bola->direcao = BAIXO;
    }

    if(bola->coordenada_bolinha.Y == LINHAS && bola->direcao == BAIXO)
    {
        bola->direcao = CIMA;
    }


    /*Referente as diagonais*/
    if(bola->coordenada_bolinha.Y <= janela->Janela.Y + 1 && bola->direcao == DIAGONAL_SUPERIOR_DIREITA)
    {
        bola->direcao = DIAGONAL_INFERIOR_DIREITA;
    }

    if(bola->coordenada_bolinha.Y <= janela->Janela.Y + 1 && bola->direcao == DIAGONAL_SUPERIOR_ESQUERDA)
    {
        bola->direcao = DIAGONAL_INFERIOR_ESQUERDA;
    }

    if(bola->coordenada_bolinha.X == COLUNAS && bola->direcao == DIAGONAL_INFERIOR_DIREITA)
    {
        bola->direcao = DIAGONAL_INFERIOR_ESQUERDA;
    }

    if(bola->coordenada_bolinha.X == COLUNAS && bola->direcao == DIAGONAL_SUPERIOR_DIREITA)
    {
        bola->direcao = DIAGONAL_SUPERIOR_ESQUERDA;
    }

    if(bola->coordenada_bolinha.Y == LINHAS && bola->direcao == DIAGONAL_INFERIOR_DIREITA)
    {
        bola->direcao = DIAGONAL_SUPERIOR_DIREITA;
    }

    if(bola->coordenada_bolinha.Y == LINHAS && bola->direcao == DIAGONAL_INFERIOR_ESQUERDA)
    {
        bola->direcao = DIAGONAL_SUPERIOR_ESQUERDA;
    }
    
    if(bola->coordenada_bolinha.X == janela->Janela.Y + 1 && bola->direcao == DIAGONAL_SUPERIOR_ESQUERDA)
    {
        bola->direcao = DIAGONAL_SUPERIOR_DIREITA;
    }

    if(bola->coordenada_bolinha.X == janela->Janela.Y + 1 && bola->direcao == DIAGONAL_INFERIOR_ESQUERDA)
    {
        bola->direcao = DIAGONAL_INFERIOR_DIREITA;
    }
    
    /*Esquerda e direita*/
    if(bola->coordenada_bolinha.X == COLUNAS && bola->direcao == DIREITA)
    {
        bola->direcao = ESQUERDA;
    }

    if(bola->coordenada_bolinha.X < janela->Janela.Y + 2 && bola->direcao == ESQUERDA)
    {
        bola->direcao = DIREITA;
    }

}


void Desenha_direcao_bolinha(BOLINHA *bola)
{
    textbackground(BLACK);
    textcolor(BLACK);
    gotoxy(bola->coordenada_bolinha.X, bola->coordenada_bolinha.Y);
    printf(" ");
    

    switch(bola->direcao)
    {
        case DIAGONAL_INFERIOR_DIREITA:
        {
            bola->coordenada_bolinha.X++;
            bola->coordenada_bolinha.Y++;
            break;
        }
        case DIAGONAL_INFERIOR_ESQUERDA:
        {
            bola->coordenada_bolinha.X--;
            bola->coordenada_bolinha.Y++;
            break;
        }
        case CIMA:
        {
            bola->coordenada_bolinha.Y--;
            break;
        }
        case BAIXO:
        {
            bola->coordenada_bolinha.Y++;
            break;
        }
        case DIAGONAL_SUPERIOR_DIREITA:
        {
            bola->coordenada_bolinha.X++;
            bola->coordenada_bolinha.Y--;
            break;
        }
        case DIAGONAL_SUPERIOR_ESQUERDA:
        {
            bola->coordenada_bolinha.X--;
            bola->coordenada_bolinha.Y--;
            break;
        }
        case DIREITA:
        {
            bola->coordenada_bolinha.X++;
            break;
        }
        case ESQUERDA:
        {
            bola->coordenada_bolinha.X--;
            break;
        }
    }

    textbackground(WHITE_BRUSH);
    textcolor(WHITE);
    gotoxy(bola->coordenada_bolinha.X, bola->coordenada_bolinha.Y);
    printf("*");
    
}