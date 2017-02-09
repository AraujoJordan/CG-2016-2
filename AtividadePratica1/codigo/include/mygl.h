#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include "Pixel.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

void putPixel(int x, int y, int RGBA[4]) {

  int offset = (x  + y * IMAGE_WIDTH) * 4;

	for (int i = 0; i <= 3; i++) {
			FBptr[offset + i] = (int)RGBA[i];
	}
}

void putPixel(Pixel px) {
		putPixel(px.getX(),px.getY(),px.getColor());
}


//*************************************************************************
// drawLine
//*************************************************************************



#endif // _MYGL_H_
