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
    ASSERT_NEAR(37.699, dynamic_cast<AreaVisitor*>(v)->area(), 0.001);
}

TEST_F(VisitorTesting, getCompoundShapeArea) {
    Visitor * v = new AreaVisitor();
    compoundShape_0->accept(v);
    EXPECT_NEAR(52.700, dynamic_cast<AreaVisitor*>(v)->area(), 0.001);
}

TEST_F(VisitorTesting, getCompoundShapeAreaLevel3) {
    // compoundShape struct：
    /* 
        CompoundShape(id:0)//99.398
        │
        ├── CompoundShape(id:1)//52.699
        │    │
        │    ├── Triangle(id:2)//6.000
        │    │
        │    └── CompoundShape(id:5)//46.699
        │         │
        │         ├── Ellipse(id:6)//37.699
        │         │
        │         └── Rectangle(id:7)//9.000
        │        
        ├── Ellipse(id:3)//37.699
        │
        └── Rectangle(id:4)//9.000
    */
    std::list<Shape*> _shapes = std::list<Shape*>();
    _shapes.push_back(new Ellipse("6", 4, 3, "red"));//37.000
    _shapes.push_back(new Rectangle("7", 3, 3, "red"));//9.000
    Shape * compoundShape_2 = new CompoundShape("5", _shapes);//
    compoundShape_1->addShape(compoundShape_2);

    Visitor * v = new AreaVisitor();
    compoundShape_0->accept(v);
    EXPECT_NEAR(99.398, dynamic_cast<AreaVisitor*>(v)->area(), 0.001);
}

TEST_F(VisitorTesting, getRectangleInfo) {
    Visitor * v = new InfoVisitor();
    r33->accept(v);
    ASSERT_EQ("Rectangle (3.000, 3.000)", dynamic_cast<InfoVisitor*>(v)->info());
}

TEST_F(VisitorTesting, getTriangleInfo) {
    Visitor * v = new InfoVisitor();
    t345->accept(v);
    ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", dynamic_cast<InfoVisitor*>(v)->info());
}

TEST_F(VisitorTesting, getEllipseInfo) {
    Visitor * v = new InfoVisitor();
    e43->accept(v);
    ASSERT_EQ("Ellipse (4.000, 3.000)", dynamic_cast<InfoVisitor*>(v)->info());
}

TEST_F(VisitorTesting, getCompoundShapeInfo) {
    Visitor * v = new InfoVisitor();
    compoundShape_0->accept(v);
    std::string const answer = "Compound Shape {Compound Shape {Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}, Ellipse (4.000, 3.000), Rectangle (3.000, 3.000)}";

    EXPECT_EQ(answer, dynamic_cast<InfoVisitor*>(v)->info());
}

TEST_F(VisitorTesting, getCompoundShapeInfoLevel3) {
    // compoundShape struct：
    /* 
        CompoundShape(id:0) 
        │
        ├── CompoundShape(id:1)
        │    │
        │    ├── Triangle(id:2) 
        │    │
        │    └── CompoundShape(id:5) 
        │         │
        │         ├── Ellipse(id:6)
        │         │
        │         └── Rectangle(id:7)
        ├── Ellipse(id:3)
        │
        └── Rectangle(id:4)
    */
    std::list<Shape*> _shapes = std::list<Shape*>();
    _shapes.push_back(new Ellipse("6", 4, 3, "red"));
    _shapes.push_back(new Rectangle("7", 3, 3, "red"));
    Shape * compoundShape_2 = new CompoundShape("5", _shapes);
    compoundShape_1->addShape(compoundShape_2);

    Visitor * v = new InfoVisitor();
    compoundShape_0->accept(v);
    std::string const answer = "Compound Shape {Compound Shape {Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000]), Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 3.000)}}, Ellipse (4.000, 3.000), Rectangle (3.000, 3.000)}";

    EXPECT_EQ(answer, dynamic_cast<InfoVisitor*>(v)->info());
}