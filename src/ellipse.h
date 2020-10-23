#ifndef ELLIPSE
#define ELLIPSE
#include "shape.h"

#include <stdio.h>
#include <math.h>
#include <string>

class Ellipse: public Shape {
private:
    double _semiMajorAxes; // 長
    double _semiMinorAxes; // 短
    void createChecker(double semiMajorAxes, double semiMinorAxes) {
        if (semiMajorAxes > 0 && semiMinorAxes > 0 ) {
            if (semiMajorAxes >= semiMinorAxes) {
                _semiMajorAxes = semiMajorAxes;
                 _semiMinorAxes = semiMinorAxes;
                return;
            }
        }
        throw std::string("This is not an ellipse!");
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not an ellipse!"
    }
public: 
    Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes): Shape(id) {
        createChecker(semiMajorAxes, semiMinorAxes);
    }
    Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes, std::string color): Shape(id, color) {
        createChecker(semiMajorAxes, semiMinorAxes);
    }
    double area() const {
        // return the area of the Ellipse.
        double answer = M_PI * _semiMajorAxes * _semiMinorAxes;
        return answer;
    }
    
    double perimeter() const {
        // return the perimeter of the Ellipse.
        double answer = 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes-_semiMinorAxes);
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

    std::string type() const {
        return "Ellipse";
    }
};
#endif