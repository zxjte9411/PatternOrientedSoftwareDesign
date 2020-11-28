// #ifndef SHAPE_BUILDER_H
// #define SHAPE_BUILDER_H

// #include "two_dimensional_coordinate.h"
// #include "compound_shape.h"
// #include "rectangle.h"
// #include "triangle.h"
// #include "ellipse.h"
// #include "shape.h"

// #include <list>
// #include <vector>
// #include <string>
// #include <deque>
// #include <stack>

// class ShapeBuilder {
// private:
//     std::stack<Shape *> _pushdown;
//     std::stack<int> _idToCompoundShape;
//     int _id;
// public:
//     ShapeBuilder() {
//         _id = 0;
//         srand(time(NULL));
//     }
    
//     void buildRectangle(double length, double width) {
//         Shape * r = new Rectangle(std::to_string(_id++), length, width);
//         _pushdown.push(r);
//         // build a rectangle with an unique id and push in a std::stack.
//     }
    
//     void buildEllipse(double semiMajorAxes, double semiMinorAxes) {
//         Shape * e = new Ellipse(std::to_string(_id++), semiMajorAxes, semiMinorAxes);
//         _pushdown.push(e);
//         // build a ellipse with an unique id and push in a std::stack.
//     }
    
//     void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
//         std::vector<TwoDimensionalCoordinate*> coordinates;
//         coordinates.push_back(new TwoDimensionalCoordinate(x1, y1));
//         coordinates.push_back(new TwoDimensionalCoordinate(x2, y2));
//         coordinates.push_back(new TwoDimensionalCoordinate(x3, y3));
//         Shape *t = new Triangle(std::to_string(_id++), coordinates);
//         _pushdown.push(t);
//         // build a triangle with an unique id and push in a std::stack.
//     }
    
//     void buildCompoundShapeBegin() {
//         Shape * cs = new CompoundShape(std::to_string(_id), std::list<Shape*>());
//         _pushdown.push(cs);
//         _idToCompoundShape.push(_id);
//         _id++;
//         // for notifing beginning of a Compound Shape.
//     }
    
//     void buildCompoundShapeEnd() {
//         std::vector<Shape *> v;
//         while(std::stoi(_pushdown.top()->id()) != _idToCompoundShape.top()) {
//             v.push_back(_pushdown.top());
//             _pushdown.pop();
//         }
//         _idToCompoundShape.pop();
//         for(auto it=v.rbegin(); it!=v.rend(); it++){
//             _pushdown.top()->addShape(*it);
//         }
//         // for notifing ending of a Compound Shape.
//     }
    
//     std::deque<Shape*> getResult() {
//         std::vector<Shape *> result;
//         while(!_pushdown.empty()){
//             result.push_back(_pushdown.top());
//             _pushdown.pop();
//         }
//         return std::deque<Shape*>(result.rbegin(),result.rend());
//     }
// };
// #endif

#ifndef SHAPE_BUILDER_H
#define SHAPE_BUILDER_H
#include "shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "compound_shape.h"
#include <deque>
#include <stack>
#include <vector>

class ShapeBuilder {
public:
    ShapeBuilder() : _id(-1) {}
    
    void buildRectangle(double length, double width) {
        _pushdown.push(new Rectangle(std::to_string(++_id), length, width));
    }
    
    void buildEllipse(double semiMajorAxes, double semiMinorAxes) {
        _pushdown.push(new Ellipse(std::to_string(++_id), semiMajorAxes, semiMinorAxes));
    }
    
    void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        std::vector<TwoDimensionalCoordinate*> coordinates{new TwoDimensionalCoordinate(x1, y1), new TwoDimensionalCoordinate(x2, y2), new TwoDimensionalCoordinate(x3, y3)};
        _pushdown.push(new Triangle(std::to_string(++_id), coordinates));
    }
    
    void buildCompoundShapeBegin() {
        _pushdown.push(new CompoundShape(std::to_string(++_id), std::list<Shape*>()));
        _comId.push(std::to_string(_id));
    }
    
    void buildCompoundShapeEnd() {
        std::vector<Shape*> shapes;
        while (!_comId.empty() && _pushdown.top()->id() != _comId.top())
        {
            shapes.push_back(_pushdown.top());
            _pushdown.pop();
        }

        for (auto it = shapes.rbegin(); it != shapes.rend(); it++)
            _pushdown.top()->addShape(*it);

        if (!_comId.empty())
            _comId.pop();
    }
    
    std::deque<Shape*> getResult() {
        std::deque<Shape*> result;

        while (!_pushdown.empty()) {
            result.push_back(_pushdown.top());
            _pushdown.pop();
        }

        return std::deque<Shape*>(result.rbegin(), result.rend());
    }
private:
    std::stack<Shape*> _pushdown;
    std::stack<std::string> _comId;
    int _id;

    bool isNotComOrNotEmptyCom(Shape * Shape) {
        return (!dynamic_cast<CompoundShape*>(Shape) || (dynamic_cast<CompoundShape*>(Shape) && !Shape->createIterator()->isDone()));
    }
};

#endif