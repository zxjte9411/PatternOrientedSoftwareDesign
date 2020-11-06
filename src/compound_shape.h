#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H

#include "visitor.h"
#include "shape.h"
#include "iterator.h"
#include "shape_iterator.h"

#include <vector>
#include <sstream>
#include <list>

class CompoundShape : public Shape {
private:
    std::list<Shape*> _shapes;
    void createChecker(std::list<Shape*> shapes) {
        if (shapes.empty()) {
            throw std::string("This is not a compound shape!");
        }
    }
public:
    CompoundShape(std::string id, std::list<Shape*> shapes): Shape(id, "transparent") {
        createChecker(shapes);
        _shapes = std::list<Shape*>();
        std::list<Shape*>::iterator sptr = shapes.begin();
        for (;sptr!=shapes.end();sptr++)
            _shapes.push_back(*sptr);
        // The default color of compound shape should be "transparent".
        // When there's no shape contain in the compound shape,
        // should throw std::string "This is not a compound shape!"
        
        // throw std::string("This is not a compound shape!");
    }

    Iterator* createIterator() const {
        return new ShapeIterator<std::list<Shape*>::const_iterator>(_shapes.begin(), _shapes.end());
    }

    double area() const {
        std::list<Shape*>::const_iterator sptr = _shapes.begin();
        double total = 0.0;
        for (;sptr!=_shapes.end();sptr++) {
            total += (*sptr)->area();
        }
        // return sum of all containing shapes area.
        return total;
    }

    double perimeter() const {
        std::list<Shape*>::const_iterator sptr = _shapes.begin();
        double total = 0.0;
        for (;sptr!=_shapes.end();sptr++) {
            total += (*sptr)->perimeter();
        }
        // return sum of all containing shapes perimeter.
        return total;
    }

    std::string info() const {
        // return list of all containing shapes info with wrapped of "CompoundShape {}".
        // ex."Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}"
        std::list<Shape*>::const_iterator sptr = _shapes.begin();
        std::string result = "Compound Shape {";
        for (;sptr!=_shapes.end();sptr++) {
            result += (*sptr)->info() + ", ";
        }
        std::string key = ", ";
        result.replace(result.rfind(key), key.length(), "}");
        return result;
    }
    
    void addShape(Shape* shape) {
        _shapes.push_back(shape);
        // add shape into compound shape.
    }
    
    void deleteShapeById(std::string id) {
        Iterator * it = createIterator();
        for (; !it->isDone(); it->next()) {
            try
            {
                if (id == it->currentItem()->id()) {
                    _shapes.remove(it->currentItem());
                    return;
                }
                it->currentItem()->deleteShapeById(id);
                return;
            }
            catch(std::string e){} //先接起來等到真的都沒有，回圈結束後就會擲出例外
        }
        throw std::string("Expected delete shape but shape not found");
        // search and delete a shape through id,
        // search all the containing shapes and the tree structure below,
        // if no match of id, throw std::string "Expected delete shape but shape not found"
    }
    
    Shape* getShapeById(std::string id) const {
        Iterator * it = createIterator();
        for (; !it->isDone(); it->next()) {
            try
            {
                if (id == it->currentItem()->id()){
                    return it->currentItem();
                }
                return it->currentItem()->getShapeById(id);
            }
            catch(std::string e){} //先接起來等到真的都沒有，回圈結束後就會擲出例外
        }
        throw std::string("Expected get shape but shape not found");
        // search and return a shape through id,
        // search all the containing shapes and the tree structure below,
        // if no match of id, throw std::string "Expected get shape but shape not found"
    }

    std::string type() const {
        return "Compound Shape";
    }

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }

    ~CompoundShape() {
        std::list<Shape*>::iterator ptr = _shapes.begin();
        for (;ptr!=_shapes.end(); ptr++) 
            delete *ptr;
        _shapes.clear();
    }
};
#endif 