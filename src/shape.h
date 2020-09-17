#include <string>

using namespace std;

#ifndef Shape
class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string info() const = 0;
};
#endif