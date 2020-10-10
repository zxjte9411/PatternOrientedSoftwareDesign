#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H
#include "../src/shape.h"
#include <vector>
#include <sstream>

class CompoundShape : public Shape {
private:
    std::vector<Shape*> * _shapes;
    void createChecker(std::vector<Shape*>* shapes) {
        if (shapes->size() < 1) {
            throw std::string("This is not a compound shape!");
        }
    }
public:
    CompoundShape(std::string id, std::vector<Shape*>* shapes): Shape(id, "transparent") {
        createChecker(shapes);
        _shapes = new std::vector<Shape*>();
        std::vector<Shape*>::iterator sptr = shapes->begin();
        for (;sptr<shapes->end();sptr++)
            _shapes->push_back(*sptr);
        // The default color of compound shape should be "transparent".
        // When there's no shape contain in the compound shape,
        // should throw std::string "This is not a compound shape!"
        
        // throw std::string("This is not a compound shape!");
    }

    double area() const {
        std::vector<Shape*>::iterator sptr = _shapes->begin();
        double total = 0.0;
        for (;sptr<_shapes->end();sptr++) {
            total += (*sptr)->area();
        }
        // return sum of all containing shapes area.
        return total;
    }

    double perimeter() const { 
        std::vector<Shape*>::iterator sptr = _shapes->begin();
        double total = 0.0;
        for (;sptr<_shapes->end();sptr++) {
            total += (*sptr)->perimeter();
        }
        // return sum of all containing shapes perimeter.
        return total;
    }

    std::string info() const {
        // return list of all containing shapes info with wrapped of "CompoundShape {}".
        // ex."Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}"
        std::vector<Shape*>::iterator sptr = _shapes->begin();
        std::string result = "Compound Shape {";
        for (;sptr<_shapes->end();sptr++) {
            if (std::distance(sptr, _shapes->end()) == 1)
                result += (*sptr)->info() + "}";
            else
                result += (*sptr)->info() + ", ";
        }
        return result;
    }
    
    void addShape(Shape* shape) {
        _shapes->push_back(shape);
        // add shape into compound shape.
    }
    
    void deleteShapeById(std::string id) {
        std::vector<Shape*>::iterator sptr = _shapes->begin();
        for (; sptr<_shapes->end(); sptr++) {
            try
            {
                if (id == (*sptr)->id()){
                    _shapes->erase(sptr);
                    // delete *sptr;
                    return;
                }
                else if ((*sptr)->color() == "transparent") {
                    (*sptr)->deleteShapeById(id);
                    return;
                }
            }
            catch(std::string e){} //先接起來等到真的都沒有，回圈結束後就會擲出例外
        }
        throw std::string("Expected delete shape but shape not found");
        // search and delete a shape through id,
        // search all the containing shapes and the tree structure below,
        // if no match of id, throw std::string "Expected delete shape but shape not found"
    }
    
    Shape* getShapeById(std::string id) {
        std::vector<Shape*>::iterator sptr = _shapes->begin();
        for (; sptr<_shapes->end(); sptr++) {
            try
            {
                if ((*sptr)->color() == "transparent"){
                    return (*sptr)->getShapeById(id);
                }
                else if (id == (*sptr)->id()) {
                    return *sptr;
                }
            }
            catch(std::string e){} //先接起來等到真的都沒有，回圈結束後就會擲出例外
        }
        throw std::string("Expected get shape but shape not found");
        // search and return a shape through id,
        // search all the containing shapes and the tree structure below,
        // if no match of id, throw std::string "Expected get shape but shape not found"
        // return nullptr;
    }

    ~CompoundShape() {
        std::vector<Shape*>::iterator ptr = _shapes->begin();
        for (;ptr<_shapes->end(); ptr++) 
            delete *ptr;
        delete _shapes;
    }
};
#endif 