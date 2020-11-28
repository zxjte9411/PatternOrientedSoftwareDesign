#ifndef SHAPE_BUILDER_H
#define SHAPE_BUILDER_H

#include "two_dimensional_coordinate.h"
#include "compound_shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "shape.h"

#include <list>
#include <vector>
#include <string>
#include <deque>
#include <stack>
#include <cstdlib>
#include <ctime>

class ShapeBuilder {
private:
    std::stack<Shape *> _pushdown;
public:
    ShapeBuilder() {
        srand(time(NULL));
    }
    
    void buildRectangle(double length, double width) {
        Shape * r = new Rectangle(std::to_string(rand()), length, width);
        _pushdown.push(r);
        // build a rectangle with an unique id and push in a std::stack.
    }
    
    void buildEllipse(double semiMajorAxes, double semiMinorAxes) {
        Shape * e = new Ellipse(std::to_string(rand()), semiMajorAxes, semiMinorAxes);
        _pushdown.push(e);
        // build a ellipse with an unique id and push in a std::stack.
    }
    
    void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        std::vector<TwoDimensionalCoordinate*> coordinates;
        coordinates.push_back(new TwoDimensionalCoordinate(x1, y1));
        coordinates.push_back(new TwoDimensionalCoordinate(x2, y2));
        coordinates.push_back(new TwoDimensionalCoordinate(x3, y3));
        Shape *t = new Triangle(std::to_string(rand()), coordinates);
        _pushdown.push(t);
        // build a triangle with an unique id and push in a std::stack.
    }
    
    void buildCompoundShapeBegin() {
        Shape * cs = new CompoundShape(std::to_string(rand()), std::list<Shape*>());
        _pushdown.push(cs); 
        // for notifing beginning of a Compound Shape.
    }
    
    void buildCompoundShapeEnd() {
        std::vector<Shape *> v;
        while(!dynamic_cast<CompoundShape*>(_pushdown.top()) ||
            (dynamic_cast<CompoundShape*>(_pushdown.top()) && !_pushdown.top()->createIterator()->isDone())){
            v.push_back(_pushdown.top());
            _pushdown.pop();
        }
        for(auto it=v.rbegin(); it!=v.rend(); it++){
            _pushdown.top()->addShape(*it);
        }
        // for notifing ending of a Compound Shape.
    }
    
    std::deque<Shape*> getResult() {
        std::vector<Shape *> result;
        while(!_pushdown.empty()){
            result.push_back(_pushdown.top());
            _pushdown.pop();
        }
        return std::deque<Shape*>(result.rbegin(),result.rend());
    }
};
#endif