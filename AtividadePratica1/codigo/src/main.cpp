#include "include/main.h"
#include "include/definitions.h"
#include "include/Pixel.h"
#include "include/mygl.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{

	//*****************************************************************************
	// Put pixel
	//*****************************************************************************
		int rgba[4];
		rgba[0] = 255;
		rgba[1] = 255;
		rgba[2] = 255;
		rgba[3] = 255;

		putPixel(Pixel(160,255,rgba));

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
