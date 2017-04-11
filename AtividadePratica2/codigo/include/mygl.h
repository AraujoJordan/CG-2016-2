#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include "Pixel.h"

#include <math.h>
#include <stdio.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

//*************************************************************************
// drawPixel
//*************************************************************************
void putPixel(const Pixel& px) {
    int pixelRealPosition = (px.getX()  + px.getY() * IMAGE_WIDTH) * 4;
    for (int i = 0; i <= 3; i++) {
        FBptr[pixelRealPosition + i] = (int)px.getColor()[i];
    }
}
//*************************************************************************
// drawLine
//*************************************************************************
void drawLine(const Pixel& px1,const Pixel& px2) {

  	Pixel linePosition = Pixel(px1.getX(),px1.getY());

    int gradientColor[4];

  	int x = px1.getX();
  	int y = px1.getY();

    int xLimit, yLimit, limit;

  	int* distortedLine;
  	int* straightLine;

    int xVariation, yVariation;

    float distanceXPercent, distanceYPercent;

    //Set the deltaX and deltaY limits
  	if (px1.getX() > px2.getX())
  		xLimit = (px1.getX() - px2.getX()) + px1.getX();
  	else
  		xLimit = px2.getX();

  	if (px1.getY() > px2.getY())
  		yLimit = (px1.getY() - px2.getY()) + px1.getY();
  	else
  		yLimit = px2.getY();

  	xVariation = xLimit - px1.getX(); //the x variation of the line
  	yVariation = yLimit - px1.getY(); // the y variation of the line

    // Change the pointer for X or y octant
  	if(xVariation < yVariation) {
      straightLine = &x;
      distortedLine = &y;

	    int tmp = xVariation;
	    xVariation = yVariation;
	    yVariation = tmp;
  	  limit = yLimit;
  	}
  	else {
      straightLine = &y;
      distortedLine = &x;
  		limit = xLimit;
  	}

    // the amount of distortion for the the x and y variations
  	int distortion = (2 * yVariation) - xVariation;
  	int increaseStraight = 2 * yVariation;
  	int increaseDistortion = 2 * (yVariation - xVariation);

    /*
    The Bresenham's Algorithm increase the line until the limit is reached
    */
  	while(*distortedLine < limit) {
  		if (distortion <= 0) {
  			distortion += increaseStraight;
  		}
  		else {
  			distortion += increaseDistortion;
  			*straightLine += 1;
  		}
      *distortedLine += 1;

  		linePosition.setX(x);
  		linePosition.setY(y);

  		if(xLimit != px2.getX())
  		    linePosition.setX( px1.getX() - (linePosition.getX() - px1.getX()));
  		if(yLimit != px2.getY())
  		    linePosition.setY( px1.getY() - (linePosition.getY() - px1.getY()));

      // Degradee color
      if(px2.getX() - px1.getX() == 0)
          distanceXPercent = 1;
      else
          distanceXPercent = (1.0-((float) (linePosition.getX() - px1.getX()) / ((float) px2.getX() - px1.getX())));
      if(px2.getY() - px1.getY() == 0)
          distanceYPercent = 1;
      else
          distanceYPercent = (1.0-((float) (linePosition.getY() - px1.getY()) / ((float) px2.getY() - px1.getY())));

      float distancePercent = xVariation <= yVariation ? distanceYPercent : distanceXPercent;

      for(int index=0 ; index<4 ; index++)
          gradientColor[index] = px1.getColor()[index] * distancePercent + px2.getColor()[index] * (1 - distancePercent);

      putPixel(Pixel(linePosition.getX(),linePosition.getY(),gradientColor));
  }
  putPixel(Pixel(px1.getX(),px1.getY(),px1.getColor()));
  putPixel(Pixel(px2.getX(),px2.getY(),px2.getColor()));
}

//*************************************************************************
// drawTriangle
//*************************************************************************

void drawTriangle(const Pixel& px1,const Pixel& px2,const Pixel& px3) {
  drawLine(px1,px2);
  drawLine(px2,px3);
  drawLine(px3,px1);
}

//*************************************************************************
// drawCircle
//*************************************************************************

void drawCircle(const Pixel& px, const int radius) {
  float TWO_PI = 2 * 3.1415;
  float increaseValue;
  radius==0 ? increaseValue = 1 : increaseValue = (1.0f / (float) radius);

  Pixel circleLimits = Pixel(0,0,px.getColor());
  for(float teta = 0; teta <= TWO_PI ; teta += increaseValue) {
    float x = px.getX() + radius*cos(teta);
    float y = px.getY() + radius*sin(teta);

    circleLimits.setX(x);
    circleLimits.setY(y);

    putPixel(circleLimits);
  }
}

#endif
