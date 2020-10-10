#include <string>

#ifndef SHAPE
#define SHAPE
class Shape {
private:
    std::string _id;
    std::string _color;

public:
    Shape(std::string id): _id(id), _color("white"){} // interface for default color "white".
    Shape(std::string id, std::string color): _id(id), _color(color){} // interface for color input by user.

    std::string id() const {
        return _id;
    } // return id of shape.

    std::string color() const {
        return _color;
    } // return color of shape.

    virtual void addShape(Shape *shape) {
        throw std::string("Only compound shape can add shape!");
    } // throw std::string "Only compound shape can add shape!"

    virtual void deleteShapeById(std::string id) {
        throw std::string("Only compound shape can delete shape!");
    } // throw std::string "Only compound shape can delete shape!"

    virtual Shape* getShapeById(std::string id) {
        throw std::string("Only compound shape can get shape!");
    } // throw std::string "Only compound shape can get shape!"

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string info() const = 0;
    virtual ~Shape() {};
};
#endif