#ifndef RECTANGLE
#define RECTANGLE

#include "visitor.h"
#include "shape.h"

#include <stdio.h>
#include <math.h>
#include <string>

class Rectangle: public Shape {
private:
    double _length, _width;
    void createChecker(double length, double width) {
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
public: 
    Rectangle(std::string id, double length, double width): Shape(id) {
        createChecker(length, width);
    }
    Rectangle(std::string id, double length, double width, std::string color): Shape(id, color) {
        createChecker(length, width);
    }
    
    double area() const {
        // return the area of the Rectangle.
        double answer = _length * _width;
        return answer;
    }
    
    double perimeter() const {
        // return the perimeter of the Rectangle.
        return (_length + _width) * 2;
    }
    
    std::string info() const {
        char buffer[50];
        double newLength = floor(_length * 1000) / 1000;
        double newWidth = floor(_width * 1000) / 1000;
        sprintf(buffer, "Rectangle (%.3f, %.3f)", newLength, newWidth);
        return buffer;
        // return the info of the Rectangle.
        // ex. Rectangle (3.712, 4.000)
    }

    std::string type() const {
        return "Rectangle";
    }

    double getLength() const {
        return _length;
    }
    double getWidth() const {
        return _width;
    }

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};
#endif