#pragma once

#include <iostream>
#include <cmath>
using namespace std;

class bola {
private:
    int x, y;
    int dx, dy;
    int velocidade;
    char caractere;
    int maxX, maxY;

public:
    bola(int x, int y, char caractere, int velocidade, int maxX, int maxY)
        : x(x), y(y), caractere(caractere), velocidade(velocidade), maxY(maxY), maxX(maxX) {
        dx = 1;
        dy = -1;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getDY() const { return dy; }
    int getDX() const { return dx; }
    char getCaractere() const { return caractere; }

    void setDY(int newDY) { dy = newDY; }
    void setDX(int newDX) { dx = newDX; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }

    void mover() {
        x += dx;
        y += dy;

        // Colisão com paredes laterais
        if (x <= 1 || x >= maxX - 2) {
            dx = -dx;
            if (x <= 1) x = 1;
            if (x >= maxX - 1) x = maxX - 2;
        }

        // Colisão com a parede superior
        if (y <= 1) {
            dy = -dy;
            y = 1;
        }
    }
};