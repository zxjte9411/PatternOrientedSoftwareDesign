#ifndef UTILITY_H
#define UTILITY_H

#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "two_dimensional_coordinate.h"
#include "iterator.h"

#include <string>
#include <deque>

Shape* getShapeById(Shape* shape, std::string id) {
    Iterator * shapeIterator = shape->createIterator();
    if (shapeIterator->isDone()) {
        throw std::string("Only compound shape can get shape!");
    }

    try
    {
        return shape->getShapeById(id);
    }
    catch(std::string e) {
        throw std::string("Expected get shape but shape not found");
    }
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return a shape under the input shape tree sturcture that matches the id.
    // throw std::string "Only compound shape can get shape!" when the input shape is not iterable.
    // throw std::string "Expected get shape but shape not found" when no shape found with the given id.
}

template <class Filter>
std::deque<Shape*> filterShape(Shape* shape, Filter filter) {
    Iterator * shapeIterator = shape->createIterator();
    if (shapeIterator->isDone()) {
        throw std::string("Only compound shape can filter shape!");
    }
    std::deque<Shape*> shapes = std::deque<Shape*>();
    for (;!shapeIterator->isDone(); shapeIterator->next()) {
        if (filter(shapeIterator->currentItem()))
            shapes.push_back(shapeIterator->currentItem());
    }
    return shapes;
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the shapes under the input shape tree sturcture that match the given filter.
    // throw std::string "Only compound shape can filter shape!" when the input shape is not iterable.
}

class AreaFilter {
public:
    AreaFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound) {}
    bool operator() (Shape* shape) const {
        return shape->area() <= _upperBound && shape->area() >= _lowerBound;
    }
private:
    double const _upperBound;
    double const _lowerBound;
};

class PerimeterFilter {
public:
    PerimeterFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound) {}
    bool operator() (Shape* shape) const {
        return shape->perimeter() <= _upperBound && shape->perimeter() >= _lowerBound;
    }
private:
    double const _upperBound;
    double const _lowerBound;
};

class ColorFilter {
public:
    ColorFilter(std::string color):_color(color) {}
    bool operator() (Shape* shape) const {
        return shape->color() == _color;
    }
private:
    std::string const _color;
};

class TypeFilter {
public:
    TypeFilter(std::string type):_type(type) {}
    bool operator() (Shape* shape) const {
        return shape->type() == _type;
    }
private:
    std::string const _type;
};
#endif