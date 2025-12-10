#pragma once 

#include <iostream>
#include <string>
using namespace std;

class bloco {
private:
    int x, y;
    int largura, altura;
    char caractere;
    int pontos;
    bool ativo;

public:
    bloco(int x, int y, int largura, int altura, char caractere, int pontos)
        : x(x), y(y), largura(largura), altura(altura), caractere(caractere), pontos(pontos), ativo(true) {
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getLargura() const { return largura; }
    bool estaAtivo() const { return ativo; }
    char getCaractere() const { return caractere; }

    //Função de Destruir bloco
    void destruir() {
        ativo = false;
    }
};