#include "definitions.h"

void putPixel(int x, int y, int RGBA[4]) {

	// Verificacoes Iniciais
	if(x < 0 || y < 0 || x > IMAGE_WIDTH || y > IMAGE_HEIGHT) {
		std::clog << "Pixel to draw is out of screen...\n";
		return;
	}

    int offset = (x  + y * IMAGE_WIDTH) * 4;

	for (int i = 0; i <= 3; i++) {
			FBptr[offset + i] = (int)RGBA[i];
	}
}
