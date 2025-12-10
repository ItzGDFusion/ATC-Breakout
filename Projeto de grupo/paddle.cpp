#pragma once 

#include <iostream>
#include <cmath>
using namespace std;

class paddle {
private:
	int x;
	int y;
	int tamanho;

public:
	paddle(int startX, int startY, int size)
		: x(startX), y(startY), tamanho(size) {
	}

	int getX() const { return x; }
	int getY() const { return y; }
	int getTamanho() const { return tamanho; }

	void moverEsquerda() {
		if (x > 1) x--;
	}
	void moverDireita(int limite) {
		if (x + tamanho < limite) x++;
	}
};