#include "include/Pixel.h"

Pixel::Pixel (int x, int y, int* RGBA) {
    this->position = new int[2];
    this->RGBA = new int[4];
    setPosition(x,y);
    setColor(RGBA);
}

Pixel::~Pixel() {
    if(this->position != nullptr) {
        delete []position;
    }
    if(this->RGBA != nullptr) {
        delete []RGBA;
    }
}

void Pixel::setPosition(int x, int y) {

    if( x < 0 || x > IMAGE_WIDTH || y < 0 || y > IMAGE_HEIGHT ) {
        throw std::invalid_argument( "Invalid position of the pixel" );
    }

    this->position[0] = x;
    this->position[1] = y;
}

void Pixel::setColor(int* RGBA) {

    for(int index = 0 ; index <= 3 ; index++) {
        if(RGBA[index] < 0 || RGBA[index] > 255) {
            throw std::invalid_argument( "Invalid color of the pixel" );
        }
    }

    for(int index = 0 ; index <= 3 ; index++) {
        this->RGBA[index] = RGBA[index];
    }
}

int* Pixel::getPosition() const {
  return this->position;
}

int* Pixel::getColor() const {
  return this->RGBA;
}

int Pixel::getX() const {
  return this->position[0];
}

int Pixel::getY() const {
  return this->position[1];
}
