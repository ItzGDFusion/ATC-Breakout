#pragma once 

#include "bola.cpp"
#include "paddle.cpp"
#include "blocos.cpp" 
#include <vector>

class Colisao {
public:

    static void processarColisaoPaddle_BOLA(bola& b, const paddle& p) {
        if (b.getY() == p.getY() &&
            b.getX() >= p.getX() &&
            b.getX() < p.getX() + p.getTamanho())
        {
            b.setDY(-b.getDY());
        }
    }

    static int processarColisaoBlocos_BOLA(bola& b, std::vector<bloco>& parede) {
        for (auto& bloco : parede) {
            if (bloco.estaAtivo()) {

                int ballX = b.getX();
                int ballY = b.getY();
                bool colideX = (ballX >= bloco.getX() && ballX < bloco.getX() + bloco.getLargura());
                bool colideY = (ballY == bloco.getY());

                if (colideX && colideY) {

                    bloco.destruir();
                    b.setDY(-b.getDY());

                    return 10; //10 equivalente á pontuação por cada bloco partido
                }
            }
        }
        return 0;
    }

    static bool ColisaoBOLA_base(bola& b, int mainWinHeight) {
        return b.getY() >= mainWinHeight - 1;
    }
};