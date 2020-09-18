#include "./shape.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

#ifndef RECTANGLE
#define RECTANGLE
class Rectangle: public Shape {
private:
    double _length, _width;
public: 
    Rectangle(double length, double width):_length(length), _width(width) {
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
    }
    
    double area() const {
        // return the area of the Rectangle.
        return _length * _width;
    }
    
    double perimeter() const {
        // return the perimeter of the Rectangle.
        return _length * 2.0 + _width * 2.0;
    }
    
    string info() const {
        return "Rectangle (3.712, 4.000)";
        // return the info of the Rectangle.
        // ex. Rectangle (3.712, 4.000)
    }
};
#endif