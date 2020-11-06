#ifndef AREA_VISITOR
#define AREA_VISITOR

#include "compound_shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "iterator.h"
#include "visitor.h"

#include <math.h>

class AreaVisitor : public Visitor {
private:
    double _area;
public:
    void visit(Ellipse* ellipse) {
        _area = M_PI * ellipse->getSemiMajorAxes() * ellipse->getSemiMinorAxes();
        // caculate the area of Ellipse.
        // DO NOT use ellipse->area() to get area directly.
        // you may add public function for Ellipse to get it's data members.
    }

    void visit(Triangle* triangle) {
        double sideA = triangle->getSideA();
        double sideB = triangle->getSideB();
        double sideC = triangle->getSideC();
        double s = (sideA + sideB + sideC) / 2.0;
        _area = sqrt(s * (s-sideA) * (s-sideB) * (s-sideC));
        // caculate the area of Triangle.
        // DO NOT use triangle->area() to get area directly.
        // you may add public function for Triangle to get it's data members.
    }

    void visit(Rectangle* rectangle) {
        _area = rectangle->getWidth() * rectangle->getLength();
        // caculate the area of Rectangle.
        // DO NOT use rectangle->area() to get area directly.
        // you may add public function for Rectangle to get it's data members.
    }

    void visit(CompoundShape* compoundShape) {
        _area = 0;
        Iterator * it = compoundShape->createIterator();
        Visitor * v = new AreaVisitor();
        for (;!it->isDone(); it->next()) {
            it->currentItem()->accept(v);
            _area += dynamic_cast<AreaVisitor*>(v)->area();
        }
        // caculate the area of CompoundShape.
        // DO NOT use compoundShape->area() to get area directly.
        // you may add public function for CompoundShape to get it's data members.
    }

    double area() const {
        return _area;
    }
};
#endif