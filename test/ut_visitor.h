#include "../src/info_visitor.h"
#include "../src/area_visitor.h"
#include "../src/visitor.h"
#include "../src/iterator.h"
#include "../src/compound_shape.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"

#include <gtest/gtest.h>
#include <list>

class VisitorTesting : public ::testing::Test {
protected:
    void SetUp() override {
        shapes = std::list<Shape*>();
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        t345 = new Triangle("2", triangleVector, "blue");
        shapes.push_back(t345);
        e43 = new Ellipse("3", 4, 3, "red");
        r33 = new Rectangle("4", 3, 3, "red");
        compoundShape_1 = new CompoundShape("1", shapes);
        shapes.clear();
        shapes.push_back(compoundShape_1);
        shapes.push_back(e43);
        shapes.push_back(r33);
        compoundShape_0 = new CompoundShape("0", shapes);
        // compoundShape struct：
        /* 
            CompoundShape(id:0) 
            │
            ├── CompoundShape(id:1)
            │    │
            │    └── Triangle(id:2) 
            │
            ├── Ellipse(id:3)
            │
            └── Rectangle(id:4)
        */
    }
    
    void TearDown() override {
        delete compoundShape_0;
    }

    Shape * compoundShape_0;
    Shape * compoundShape_1;
    Shape * e43;
    Shape * r33;
    Shape * t345;
    std::list<Shape*> shapes;
    std::vector<TwoDimensionalCoordinate*> triangleVector;
};

TEST_F(VisitorTesting, getRectangleArea) {
    Visitor * v = new AreaVisitor();
    r33->accept(v);
    ASSERT_NEAR(9.000, dynamic_cast<AreaVisitor*>(v)->area(), 0.001);
}

TEST_F(VisitorTesting, getTriangleArea) {
    Visitor * v = new AreaVisitor();
    t345->accept(v);
    ASSERT_NEAR(6.000, dynamic_cast<AreaVisitor*>(v)->area(), 0.001);
}

TEST_F(VisitorTesting, getEllipseArea) {
    Visitor * v = new AreaVisitor();
    e43->accept(v);
    ASSERT_NEAR(37.700, dynamic_cast<AreaVisitor*>(v)->area(), 0.001);
}

TEST_F(VisitorTesting, getCompoundShapeArea) {
    Visitor * v = new AreaVisitor();
    compoundShape_0->accept(v);
    EXPECT_NEAR(52.700, dynamic_cast<AreaVisitor*>(v)->area(), 0.001);
}