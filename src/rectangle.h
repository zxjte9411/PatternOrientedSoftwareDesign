#include <stdio.h>
#include <math.h>
#include <string>

#include "shape.h"

#ifndef RECTANGLE
#define RECTANGLE
class Rectangle: public Shape {
private:
    double _length, _width;

public: 
    Rectangle(double length, double width) {
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
        if (length <= 0 || width <= 0) {
            throw std::string("This is not a rectangle!");
        }
        else
        {
            _length = length;
            _width = width;
        }
    }
    
    double area() const {
        // return the area of the Rectangle.
        double answer = _length * _width * 1000;
        answer -= 0.5;
        return round(answer) / 1000;
    }
    
    double perimeter() const {
        // return the perimeter of the Rectangle.
        return _length + _length + _width + _width;
    }
    
    std::string info() const {
        char buffer[50];
        double newLength = round(_length * 1000 - 0.5) / 1000;
        double newWidth = round(_width * 1000 - 0.5) / 1000;
        sprintf(buffer, "Rectangle (%.3f, %.3f)", newLength, newWidth);
        return buffer;
        // return the info of the Rectangle.
        // ex. Rectangle (3.712, 4.000)
    }
};
#endif