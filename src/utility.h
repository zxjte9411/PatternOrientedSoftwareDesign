#ifndef UTILITY_H
#define UTILITY_H
#include "shape.h"
#include "iterator.h"

#include <string>

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
#endif