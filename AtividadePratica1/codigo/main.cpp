#include "main.h"
#include "definitions.h"

#include "PutPixel.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// PutPixel
	//*************************************************************************

	int rgba[4];

	for(int r = 0 ; r <= 255 ; r++) {
		for(int g = 0 ; g <= 255 ; g++) {
			for(int b = 0 ; b <= 255 ; b++) {
				rgba[0] = r;
				rgba[1] = g;
				rgba[2] = b;
				rgba[3] = 255;
				putPixel(r,g,rgba);
			}
		}
	}


	//*************************************************************************
	// drawLine
	//*************************************************************************


}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

