#include <stdio.h>
#include <math.h>
#include <string>

#include "shape.h"

#ifndef ELLIPSE
#define ELLIPSE

class Ellipse: public Shape{
private:
    double _semiMajorAxes; // 長
    double _semiMinorAxes; // 短

public: 
    Ellipse(double semiMajorAxes, double semiMinorAxes) {
        if (semiMajorAxes > 0 && semiMinorAxes > 0 ) {
            _semiMajorAxes = semiMajorAxes;
            _semiMinorAxes = semiMinorAxes;
            return;
        }
        throw std::string("This is not a ellipse!");
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
    }
    
    double area() const {
        // return the area of the Ellipse.
        double answer = floor(M_PI * _semiMajorAxes * _semiMinorAxes * 1000) / 1000;
        return answer;
    }
    
    double perimeter() const {
        // return the perimeter of the Ellipse.
        double answer = floor((2 * M_PI * _semiMinorAxes + 4 *(_semiMajorAxes-_semiMinorAxes)) * 1000) / 1000;
        return answer;
    }
    
    std::string info() const {
        // return the info of the Ellipse.
        // ex. Ellipse (3.712, 4.000)
        char buffer[50];
        double newSemiMajorAxes = floor(_semiMajorAxes * 1000) / 1000;
        double newSemiMinorAxes = floor(_semiMinorAxes * 1000) / 1000;
        sprintf(buffer, "Ellipse (%.3f, %.3f)", newSemiMajorAxes, newSemiMinorAxes);
        return buffer;
    }
};
#endif