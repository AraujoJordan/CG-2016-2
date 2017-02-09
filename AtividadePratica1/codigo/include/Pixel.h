#ifndef PIXEL_H
#define PIXEL_H

#include "definitions.h"
#include <stdexcept>

class Pixel {
private:
    int* position;
    int* RGBA;

public:
    Pixel(int x, int y, int* RGBA);
    ~Pixel();
    void setPosition (int x, int y);
    void setColor (int* RGBA);
    int* getPosition() const;
    int* getColor() const;
    int getX() const;
    int getY() const;

};

#endif
