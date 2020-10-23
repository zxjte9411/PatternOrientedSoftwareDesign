#include "../src/utility.h"
#include "../src/iterator.h"
// #include "../src/null_iterator.h"
// #include "../src/shape_iterator.h"
#include "../src/compound_shape.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"

#include <gtest/gtest.h>

class UtilityTesting : public ::testing::Test {
protected:
    void SetUp() override {
        shapes = new std::list<Shape*>();
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        shapes->push_back(new Triangle("2", triangleVector, "blue"));
        compoundShape_1 = new CompoundShape("1", shapes);
        shapes->clear();
        shapes->push_back(compoundShape_1);
        shapes->push_back(new Ellipse("3", 4, 3, "red"));
        shapes->push_back(new Rectangle("4", 3, 3, "red"));
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
        delete shapes;
    }

    Shape * compoundShape_0;
    Shape * compoundShape_1;
    std::list<Shape*> * shapes;
    std::vector<TwoDimensionalCoordinate*> triangleVector;
};


TEST_F(UtilityTesting, getShapeById) {
    Shape * s = getShapeById(compoundShape_0, "2");
    EXPECT_EQ("2", s->id());
    EXPECT_EQ("blue", s->color());
    EXPECT_EQ(6, s->area());
    EXPECT_EQ(12, s->perimeter());
    EXPECT_EQ("Triangle", s->type());
    s = getShapeById(compoundShape_0, "3");
    EXPECT_EQ("3", s->id());
    EXPECT_EQ("red", s->color());
    EXPECT_NEAR(37.700, s->area(), 0.001);
    EXPECT_NEAR(22.849, s->perimeter(), 0.001);
    EXPECT_EQ("Ellipse", s->type());
    s = getShapeById(compoundShape_0, "4");
    EXPECT_EQ("4", s->id());
    EXPECT_EQ("red", s->color());
    EXPECT_NEAR(9, s->area(), 0.001);
    EXPECT_NEAR(12, s->perimeter(), 0.001);
    EXPECT_EQ("Rectangle", s->type());
    s = getShapeById(compoundShape_1, "2");
    EXPECT_EQ("2", s->id());
    EXPECT_EQ("blue", s->color());
    EXPECT_EQ(6.000, s->area());
    EXPECT_EQ(12.000, s->perimeter());
    EXPECT_EQ("Triangle", s->type());

    try
    {
        getShapeById(compoundShape_0, "-1");
        FAIL();
    }
    catch(std::string e)
    {
        EXPECT_EQ("Expected get shape but shape not found", e);
    }

    try
    {
        getShapeById(new Rectangle("4", 2, 2, "red"), "-1");
        FAIL();
    }
    catch(std::string e)
    {
        EXPECT_EQ("Only compound shape can get shape!", e);
    }
}