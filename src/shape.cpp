#include "null_iterator.h"

#include <string>

Shape::Shape(std::string id): _id(id), _color("white"){} // interface for default color "white".
Shape::Shape(std::string id, std::string color): _id(id), _color(color){} // interface for color input by user.

std::string Shape::id() const {
    return _id;
} // return id of shape.

std::string Shape::color() const {
    return _color;
} // return color of shape.

void Shape::addShape(Shape *shape) {
    throw std::string("Only compound shape can add shape!");
} // throw std::string "Only compound shape can add shape!"

void Shape::deleteShapeById(std::string id) {
    throw std::string("Only compound shape can delete shape!");
} // throw std::string "Only compound shape can delete shape!"

Shape* Shape::getShapeById(std::string id) const {
    throw std::string("Only compound shape can get shape!");
} // throw std::string "Only compound shape can get shape!"

Iterator* Shape::createIterator() const {
    return new NullIterator();
}

Shape::~Shape() {};