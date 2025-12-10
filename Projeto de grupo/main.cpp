#include <iostream>
#include <cmath>
#include <curses.h>
#include <vector> 

// Camada Interface
#include "INTERFACE.cpp" 
// Camada Lógica
#include "paddle.cpp"
#include "bola.cpp"
#include "blocos.cpp" 
#include "colisoes.cpp" 

using namespace std;

//Tamanho da Janela
const int Altura = 30;
const int Largura = 42;
const int Altura_Cabeçalho = 2;

// Função para resetar a bola para a posição inicial
void reset_bola(bola& ball, int startX, int startY) {
    ball.setX(startX);
    ball.setY(startY);
    ball.setDY(-1);
    ball.setDX(1);
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    //Criar janelas
    WINDOW* Cabecalho = newwin(Altura_Cabeçalho, Largura, 0, 0);
    WINDOW* janelaPrincipal = newwin(Altura - Altura_Cabeçalho, Largura, Altura_Cabeçalho, 0);

    keypad(janelaPrincipal, TRUE); // Teclas

    int TELA_SEM_CABECALHO = Altura - Altura_Cabeçalho;
    int LARGURA_TELA_PRINCIPAL = Largura;

    //INTERFACE
    INTERFACE ui(janelaPrincipal, Cabecalho);

    //Parámetros do jogo
    int pontuacao = 0;
    int vidas = 3;
    bool emJogo = true;  //variavel que define jogo em andamento ou não
    bool ganhou = false; // Flag de vitória

    // Paddle
    int paddleY = TELA_SEM_CABECALHO - 2;
    paddle pad(LARGURA_TELA_PRINCIPAL / 2 - 2, paddleY, 4); //mudar tamanho do padle

    // Bola ('*')
    int startX = LARGURA_TELA_PRINCIPAL / 2;
    int startY = TELA_SEM_CABECALHO - 3;
    bola ball(startX, startY, '*', 1, LARGURA_TELA_PRINCIPAL, TELA_SEM_CABECALHO);

    reset_bola(ball, startX, startY);

    // Blocos e as defs dos mesmos
    std::vector<bloco> parede;
    int blocosPorLinha = 8;
    int linhasBlocos = 3;
    int blocoLargura = 4;
    int espacoEntreBlocos = 1;

    int larguraDisponivel = LARGURA_TELA_PRINCIPAL - 2;
    int larguraTotalComEspaco = blocosPorLinha * blocoLargura + (blocosPorLinha - 1) * espacoEntreBlocos;
    int espacoMargens = larguraDisponivel - larguraTotalComEspaco;
    int startXBlocos = 1 + (espacoMargens / 2);

    for (int l = 0; l < linhasBlocos; ++l) {
        for (int c = 0; c < blocosPorLinha; ++c) {
            int x = startXBlocos + c * (blocoLargura + espacoEntreBlocos);
            int y = 3 + l * 2; // Linha 3, com uma linha de espaço entre
            char caractere = '#';

            parede.emplace_back(x, y, blocoLargura, 1, caractere, 10);
        }
    }

    int ch = 0;
    int frameCounter = 0;
    const int ballSpeedRatio = 4;

    while (ch != 'q' && emJogo) {

        //Programa enquanto não for precionado " q "

        if (frameCounter % ballSpeedRatio == 0) {

            ball.mover();

            // Colisões
            Colisao::processarColisaoPaddle_BOLA(ball, pad);
            pontuacao += Colisao::processarColisaoBlocos_BOLA(ball, parede); //somador de potuação com o return da função

            // Perda de Vida quando bater no limite inferior da janela
            if (Colisao::ColisaoBOLA_base(ball, TELA_SEM_CABECALHO)) {
                vidas--;

                if (vidas > 0) {
                    reset_bola(ball, startX, startY);
                }
                else {
                    emJogo = false; // Game Over
                }
            }

            // Condição de Vitória
            long blocosAtivos = 0;
            for (const auto& b : parede) {
                if (b.estaAtivo()) {
                    blocosAtivos++;
                }
            }
            if (blocosAtivos == 0) {
                emJogo = false;
                ganhou = true;
            }
        }

        frameCounter++;

        // INTERFACE NA PRÁTICA , ou seja , quando está EM JOGO

        werase(janelaPrincipal);
        ui.DESENHAMoldura();
        ui.DESENHACabecalho(pontuacao, vidas, LARGURA_TELA_PRINCIPAL);

        ui.DESENHABlocos(parede);
        ui.DESENHAPaddle(pad);

        if (emJogo) {
            ui.DESENHABola(ball);
        }

        ui.refreshScreen();

        // Leitura das teclas

        nodelay(janelaPrincipal, TRUE);
        ch = wgetch(janelaPrincipal);
        nodelay(janelaPrincipal, FALSE);

        switch (ch) {
        case KEY_LEFT:
            if (pad.getX() > 1) {
                pad.moverEsquerda();
            }
            break;

        case KEY_RIGHT:
            pad.moverDireita(LARGURA_TELA_PRINCIPAL - 1);
            break;
        }

        delay_output(10);
    }

    // Quando Acabar o jogo
    ui.GameOver(TELA_SEM_CABECALHO, LARGURA_TELA_PRINCIPAL, pontuacao, ganhou);

    while (ch != 'q') {
        ch = wgetch(janelaPrincipal);
    }

    delwin(Cabecalho);
    delwin(janelaPrincipal);
    endwin();

    return 0;
}