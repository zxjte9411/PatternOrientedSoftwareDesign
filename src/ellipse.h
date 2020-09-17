#include "./shape.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;
#ifndef Ellipse
class Ellipse: public Shape{
public: 
    Ellipse(double semiMajorAxes, double semiMinorAxes) {
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
    }
    
    double area() const {
        // return the area of the Ellipse.
    }
    
    double perimeter() const {
        // return the perimeter of the Ellipse.
    }
    
    string info() const {
        // return the info of the Ellipse.
        // ex. Ellipse (3.712, 4.000)
    }
};
#endif