#include "./shape.h"
#include "./two_dimensional_coordinate.h"
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

#ifndef TRIANGLE
#define TRIANGLE
class Triangle: public Shape {
public: 
    Triangle(vector<TwoDimensionalCoordinate*> vectors) {
        // If the triangle can't be successfully created,
        // handle the exception by throwing string "This is not a triangle!"
    }
    
    double area() const {
        // return the area of the Triangle.
    }
    
    double perimeter() const {
        // return the perimeter of the Triangle.
    }
    
    string info() const {
        // return the info of the Triangle.
        // ex. Triangle ([0.000, 0.000], [0.000, -3.141], [-4.000, 0.000])
    }
};
#endif