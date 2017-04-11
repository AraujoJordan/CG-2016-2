#include "main.h"
#include "definitions.h"
#include "Pixel.h"
#include "mygl.h"

int i = 0;

//-----------------------------------------------------------------------------
void MyGlDraw(void) {
		//*****************************************************************************
		// Put pixel
		//*****************************************************************************
		// for(int r = 0; r<=255 ; r++) {
		// 	for(int g = 0; g<=255 ; g++) {
		// 		for(int b = 0; b<=255 ; b++) {
		// 			int rgbaChange[4];
		// 			rgbaChange[0] = r;
		// 			rgbaChange[1] = g;
		// 			rgbaChange[2] = b;
		// 			rgbaChange[3] = 255;
		// 			putPixel(Pixel(r,g,rgbaChange));
		// 		}
		// 	}
		// }

		int rgbaRed[4];
		rgbaRed[0] = 255;
		rgbaRed[1] = 0;
		rgbaRed[2] = 0;
		rgbaRed[3] = 255;

		int rgbaGreen[4];
		rgbaGreen[0] = 0;
		rgbaGreen[1] = 255;
		rgbaGreen[2] = 0;
		rgbaGreen[3] = 255;

		int rgbaBlue[4];
		rgbaBlue[0] = 0;
		rgbaBlue[1] = 0;
		rgbaBlue[2] = 255;
		rgbaBlue[3] = 255;

		//make 4 points for visibility
		putPixel(Pixel(200,50,rgbaGreen));
		putPixel(Pixel(199,49,rgbaGreen));
		putPixel(Pixel(200,49,rgbaGreen));
		putPixel(Pixel(199,50,rgbaGreen));

		putPixel(Pixel((IMAGE_WIDTH/2),(IMAGE_HEIGHT/2)-35,rgbaGreen));
		putPixel(Pixel((IMAGE_WIDTH/2)+25,(IMAGE_HEIGHT/2)+25,rgbaRed));
		putPixel(Pixel((IMAGE_WIDTH/2)-25,(IMAGE_HEIGHT/2)+25,rgbaBlue));


		//*****************************************************************************
		// draw line
		//*****************************************************************************


		Pixel px1 = Pixel(IMAGE_WIDTH/2,IMAGE_HEIGHT/2,rgbaGreen);
		Pixel px2 = Pixel(0,IMAGE_WIDTH,rgbaRed);
		Pixel px3 = Pixel(IMAGE_WIDTH,IMAGE_WIDTH/2,rgbaBlue);

		//  drawLine(Pixel(10,35,rgbaGreen),Pixel(114,101,rgbaRed));
		//  drawLine(px1,px2);
		 //
		//  drawLine(Pixel(104,149,rgbaRed),Pixel(100,50,rgbaBlue));
		//  drawLine(Pixel(100,12,rgbaBlue),Pixel(500,10,rgbaGreen));
		 //
		//  drawLine(px3,px1);
		//  drawLine(px1,px2);

		//*****************************************************************************
		// draw triangle
		//*****************************************************************************
		 //
		//  drawTriangle(px1,px2,px3);
		//  drawTriangle(Pixel((IMAGE_WIDTH/2),(IMAGE_HEIGHT/2)-35,rgbaGreen),
		//  							Pixel((IMAGE_WIDTH/2)+25,(IMAGE_HEIGHT/2)+25,rgbaRed),
		// 							Pixel((IMAGE_WIDTH/2)-25,(IMAGE_HEIGHT/2)+25,rgbaBlue));

		//*****************************************************************************
		// drawCircle
		//*****************************************************************************

		// drawCircle(Pixel((IMAGE_WIDTH/2),(IMAGE_HEIGHT/2)-35,rgbaGreen),220);
		// drawCircle(Pixel((IMAGE_WIDTH/2)+25,(IMAGE_HEIGHT/2)+25,rgbaRed),50);
		// drawCircle(Pixel((IMAGE_WIDTH/2)-25,(IMAGE_HEIGHT/2)+25,rgbaBlue),20);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv) {
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
