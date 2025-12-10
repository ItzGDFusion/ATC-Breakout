#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include "paddle.cpp" 
#include "bola.cpp"
#include "blocos.cpp"

class INTERFACE {
private:
    WINDOW* mainWin;
    WINDOW* headerWin;

public:
    INTERFACE(WINDOW* main, WINDOW* header) : mainWin(main), headerWin(header) {}

    void DESENHACabecalho(int pontuacao, int vidas, int gameWidth) {
        wclear(headerWin);
        mvwprintw(headerWin, 0, 1, "PONTUACAO: %d", pontuacao);
        mvwprintw(headerWin, 0, gameWidth - 15, "VIDAS: %d", vidas);
        wrefresh(headerWin);
    }

    void DESENHAMoldura() {
        box(mainWin, 0, 0);
    }

    void DESENHAPaddle(const paddle& p) {
        mvwprintw(mainWin, p.getY(), p.getX(), std::string(p.getTamanho(), '=').c_str());
    }

    void DESENHABola(const bola& b) {
        mvwprintw(mainWin, b.getY(), b.getX(), "%c", b.getCaractere());
    }

    void DESENHABlocos(const std::vector<bloco>& parede) {
        for (const auto& b : parede) {
            if (b.estaAtivo()) {
                mvwprintw(mainWin, b.getY(), b.getX(), std::string(b.getLargura(), b.getCaractere()).c_str());
            }
        }
    }

    void GameOver(int mainWinHeight, int mainWinWidth, int pontuacao, bool ganhou) {
        wclear(mainWin);
        drawFrame();

        const char* msg = ganhou ? "VITORIA!" : "FIM DO JOGO!";
        mvwprintw(mainWin, mainWinHeight / 2, mainWinWidth / 2 - (strlen(msg) / 2), "%s", msg);
        mvwprintw(mainWin, mainWinHeight / 2 + 1, mainWinWidth / 2 - 10, "PONTUACAO FINAL: %d", pontuacao);
        mvwprintw(mainWin, mainWinHeight / 2 + 2, mainWinWidth / 2 - 10, "Pressione 'q' para sair.");
        wrefresh(mainWin);
    }

    void refreshScreen() {
        wrefresh(mainWin);
    }
};