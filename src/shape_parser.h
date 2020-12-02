#ifndef SHAPEPARSER_H
#define SHAPEPARSER_H

#include "scanner.h"
#include "shape_builder.h"

#include <deque>
#include <string>

class ShapeParser {
private:
    Scanner * _scanner;
    ShapeBuilder _shapeBuilder;

    void buildRectangleOrEllipse(std::string shapeType) {
        double value1, value2;
        if (_scanner->nextToken() == "(") {
            value1 = std::stod(_scanner->nextToken());
            if (_scanner->nextToken() == ",") {
                value2 = std::stod(_scanner->nextToken());
                if (_scanner->nextToken() == ")"){
                    try {
                        if (shapeType == "Rectangle")
                            _shapeBuilder.buildRectangle(value1, value2);
                        else if (shapeType == "Ellipse")
                            _shapeBuilder.buildEllipse(value1, value2);
                    }
                    catch(const std::string e){}
                }
            }
        }        
    }

    void buildTriangle() {
        std::deque<double> values;
        if (_scanner->nextToken() == "("){
            for (int i=0; i<6; i++) {
                try {
                    values.push_back(std::stod(_scanner->nextToken()));
                }
                catch(const std::string e) {}
                if (i!=5 && _scanner->nextToken() != ",")
                    return;
            }
            if (_scanner->nextToken() == ")")
                _shapeBuilder.buildTriangle(values[0], values[1], values[2], values[3], values[4], values[5]);
        }
    }

    void buildCompoundShape() {
        if (_scanner->nextToken() == "{") {
            _shapeBuilder.buildCompoundShapeBegin();
            parser();
        }
    }
public:
    ShapeParser(std::string input) {
        _scanner = new Scanner(input);
        _shapeBuilder = ShapeBuilder();
        // initialize a scanner for handling input.
        // initialize a shape builder for handling building shape.
    }
    
    void parser() {
        try {
            while (true) {
                std::string token= _scanner->nextToken();
                if (token == "Rectangle" || token == "Ellipse") {
                    buildRectangleOrEllipse(token);
                }
                else if(token == "Triangle") {
                    buildTriangle();
                }
                else if(token == "CompoundShape") {
                    buildCompoundShape();
                }
                else if (token == "}") {
                    _shapeBuilder.buildCompoundShapeEnd();
                }
            }
        }
        catch(const std::string e) {}
        
        // using Scanner::nextToken() to get all information to determine what to build,
        // and provide the argument the shape needed.
        // use functions in ShapeBuilder to build out the shape.
    }
    
    std::deque<Shape*> getResult() {
        return _shapeBuilder.getResult();
    }

    ~ShapeParser() {
        delete _scanner;
    }
};
#endif