#include "../src/null_iterator.h"
#include "../src/compound_shape.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"
#include "../src/shape.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/sort.h"
#include <gtest/gtest.h>
#include <vector>
#include <list>

class CompoundShapeTesting : public ::testing::Test {
protected :

    void SetUp() override {
        shapes = new std::list<Shape*>();
        shapes->push_back(new Rectangle("0", 3, 4, "red"));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        shapes->push_back(new Triangle("1", triangleVector, "blue"));
        shapes->push_back(new Rectangle("2", 2, 2, "red"));
        compoundShape = new CompoundShape("20201010", shapes);
    }
    
    void TearDown() override {
        if (compoundShape != nullptr) {
            delete compoundShape;
            compoundShape = nullptr;
        }
        delete shapes;
    }

    CompoundShape * compoundShape;
    std::list<Shape*> * shapes;
    std::vector<TwoDimensionalCoordinate*> triangleVector;

};

TEST_F(CompoundShapeTesting, createCompoundShape) {
    // test setUp
    ASSERT_EQ("transparent", compoundShape->color());
    ASSERT_EQ("20201010", compoundShape->id());
    //-----------------------------------------------
    std::list<Shape*> * _shapes = new std::list<Shape*>();
    try
    {
        CompoundShape compoundShape("99", _shapes);
        FAIL();
    }
    catch(std::string e)
    {
        delete _shapes;
        ASSERT_EQ("This is not a compound shape!", e);
    }    
}

TEST_F(CompoundShapeTesting, getArea) {
    ASSERT_EQ(22.0, compoundShape->area());
}

TEST_F(CompoundShapeTesting, getPerimeter) {
    ASSERT_EQ(34.0, compoundShape->perimeter());
    std::list<Shape*> * _shapes = new std::list<Shape*>();
    _shapes->push_back(new Ellipse("3", 5.0, 4.0));
    CompoundShape * cs = new CompoundShape("4", _shapes);
    cs->addShape(compoundShape);
    ASSERT_NEAR(63.132, cs->perimeter(), 0.001);
    cs->deleteShapeById("20201010");
    ASSERT_NEAR(29.132, cs->perimeter(), 0.001);
}

TEST_F(CompoundShapeTesting, getInfo) {
    std::string const answer = "Compound Shape {Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000]), Rectangle (2.000, 2.000)}";
    ASSERT_EQ(answer, compoundShape->info());
}

TEST_F(CompoundShapeTesting, addShape) {
    std::list<Shape*> * _shapes = new std::list<Shape*>();
    _shapes->push_back(new Ellipse("3", 5.0, 4.0));
    CompoundShape * cs = new CompoundShape("4", _shapes);
    compoundShape->addShape(cs);
    std::string const answer = "Compound Shape {Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000]), Rectangle (2.000, 2.000), Compound Shape {Ellipse (5.000, 4.000)}}";
    ASSERT_EQ(answer, compoundShape->info());
}

TEST_F(CompoundShapeTesting, getShapeById) {
    std::list<Shape*> * _shapes = new std::list<Shape*>();
    _shapes->push_back(new Ellipse("3", 5.0, 4.0));
    CompoundShape * cs = new CompoundShape("4", _shapes);
    cs->addShape(compoundShape);
    
    ASSERT_EQ("red", cs->getShapeById("0")->color());
    ASSERT_EQ("blue", cs->getShapeById("1")->color());
    ASSERT_EQ("red", cs->getShapeById("2")->color());
    ASSERT_EQ("white", cs->getShapeById("3")->color());

    try
    {
        cs->getShapeById("7");
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("Expected get shape but shape not found", e);
    }

    try
    {
        cs->getShapeById("4");
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("Expected get shape but shape not found", e);
    }
    
}

TEST_F(CompoundShapeTesting, deleteById) {
    std::list<Shape*> * _shapes = new std::list<Shape*>();
    _shapes->push_back(new Ellipse("3", 5.0, 4.0));
    CompoundShape * cs = new CompoundShape("4", _shapes);
    cs->addShape(compoundShape);
    cs->deleteShapeById("0");
    std::string const answer = "Compound Shape {Ellipse (5.000, 4.000), Compound Shape {Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000]), Rectangle (2.000, 2.000)}}";
    ASSERT_EQ(answer, cs->info());
    ASSERT_TRUE(cs->getShapeById("20201010") == compoundShape);
    try
    {
        cs->deleteShapeById("-1");
    }
    catch(std::string e)
    {
        ASSERT_EQ("Expected delete shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTesting, shapeType) {
    std::list<Shape*>::iterator it = shapes->begin();
    shapes->push_back(new Ellipse("3", 4, 3, "blue"));
    ASSERT_EQ("Rectangle", (*it)->type());
    it++;
    ASSERT_EQ("Triangle", (*it)->type());
    it++;
    ASSERT_EQ("Rectangle", (*it)->type());
    it++;
    ASSERT_EQ("Ellipse", (*it)->type());
    ASSERT_EQ("Compound Shape", compoundShape->type());
}

TEST_F(CompoundShapeTesting, createIterator) {
    std::list<Shape*>::iterator it = shapes->begin();
    shapes->push_back(new Ellipse("3", 4, 3, "blue"));
    ASSERT_TRUE((*it)->createIterator()->isDone());
    it++;
    ASSERT_TRUE((*it)->createIterator()->isDone());
    it++;
    ASSERT_TRUE((*it)->createIterator()->isDone());
    it++;
    ASSERT_TRUE((*it)->createIterator()->isDone());
    // ASSERT_FALSE(compoundShape->createIterator()->isDone());
}