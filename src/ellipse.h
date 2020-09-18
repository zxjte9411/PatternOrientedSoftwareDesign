#include <stdio.h>
#include <math.h>
#include <string>

#include "shape.h"

#ifndef ELLIPSE
#define ELLIPSE
#define PI 3.14159

class Ellipse: public Shape{
private:
    double _semiMajorAxes; // 長
    double _semiMinorAxes; // 短

public: 
    Ellipse(double semiMajorAxes, double semiMinorAxes) {
        if (semiMajorAxes > 0 && semiMinorAxes > 0) {
            if (semiMajorAxes > semiMinorAxes) {
                _semiMajorAxes = semiMajorAxes;
                _semiMinorAxes = semiMinorAxes;
                return;
            }
        }
        throw std::string("This is not a ellipse!");
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
    }
    
    double area() const {
        // return the area of the Ellipse.
        double answer = floor(PI * _semiMajorAxes * _semiMinorAxes * 1000) / 1000;
        return answer;
    }
    
    double perimeter() const {
        // return the perimeter of the Ellipse.
        double answer = floor((2 * PI * _semiMinorAxes + 4 *(_semiMajorAxes-_semiMinorAxes)) * 1000) / 1000;
        return answer;
    }
    
    std::string info() const {
        // return the info of the Ellipse.
        // ex. Ellipse (3.712, 4.000)
        char buffer[50];
        double newSemiMajorAxes = round(_semiMajorAxes * 1000 - 0.5) / 1000;
        double newSemiMinorAxes = round(_semiMinorAxes * 1000 - 0.5) / 1000;
        sprintf(buffer, "Ellipse (%.3f, %.3f)", newSemiMajorAxes, newSemiMinorAxes);
        return buffer;
    }
};
#endif