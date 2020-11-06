#ifndef INFO_VISITOR
#define INFO_VISITOR

#include "compound_shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "iterator.h"
#include "visitor.h"

#include <sstream>
#include <math.h>
#include <string>

class InfoVisitor : public Visitor {
private:
    std::string _info;

    std::string doubleToString(TwoDimensionalCoordinate* coordinate) const {
        char buffer[50];
        sprintf(buffer, "[%.3f, %.3f]", coordinate->getX(), coordinate->getY());
        std::string str(buffer);
        return str;
    }

public:
    void visit(Ellipse* ellipse) {
        char buffer[50];
        sprintf(buffer, "Ellipse (%.3f, %.3f)", ellipse->getSemiMajorAxes(), ellipse->getSemiMinorAxes());
        _info = buffer;
        // create info of ellipse, same way as ellipse->info().
        // DO NOT use ellipse->info() to get info directly.
        // you may add public function for Ellipse to get it's data members.
    }

    void visit(Triangle* triangle) {
        std::stringstream sString;
        sString << "Triangle ("<< doubleToString(triangle->getTwoDimensionalCoordinate()[0]) << ", " << doubleToString(triangle->getTwoDimensionalCoordinate()[1]) << ", " << doubleToString(triangle->getTwoDimensionalCoordinate()[2]) << ")";
        _info = sString.str();
        // create info of ellipse, same way as triangle->info().
        // DO NOT use triangle->info() to get info directly.
        // you may add public function for Triangle to get it's data members.
    }

    void visit(Rectangle* rectangle) {
        char buffer[50];
        sprintf(buffer, "Rectangle (%.3f, %.3f)", rectangle->getLength(), rectangle->getLength());
        _info = buffer;
        // create info of rectangle, same way as rectangle->info().
        // DO NOT use rectangle->info() to get info directly.
        // you may add public function for Rectangle to get it's data members.
    }

    void visit(CompoundShape* compoundShape) {
        Iterator * it = compoundShape->createIterator();
        Visitor * v = new InfoVisitor();
        std::stringstream ss;
        _info += "Compound Shape {";
        for (; !it->isDone(); it->next()) {
            it->currentItem()->accept(v);
            ss << dynamic_cast<InfoVisitor*>(v)->info() << ", ";
        }
        _info += ss.str();
        std::string key = ", ";
        _info.replace(_info.rfind(key), key.length(), "}");
        // create info of compoundShape, same way as compoundShape->info().
        // DO NOT use compoundShape->info() to get info directly.
        // you may add public function for CompoundShape to get it's data members.
    }

    std::string info() const {
        return _info;
    }
};
#endif