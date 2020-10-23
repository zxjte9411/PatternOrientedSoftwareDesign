#include "../src/utility.h"
#include "../src/iterator.h"
#include "../src/compound_shape.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"

#include <gtest/gtest.h>
#include <deque>

class UtilityTesting : public ::testing::Test {
protected:
    void SetUp() override {
        shapes = std::list<Shape*>();
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        shapes.push_back(new Triangle("2", triangleVector, "blue"));
        compoundShape_1 = new CompoundShape("1", shapes);
        shapes.clear();
        shapes.push_back(compoundShape_1);
        shapes.push_back(new Ellipse("3", 4, 3, "red"));
        shapes.push_back(new Rectangle("4", 3, 3, "red"));
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
    std::list<Shape*> shapes;
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
/*
id:0 type: Compound Shape    color: transparent  a = x       p = x
id:1 type: Compound Shape    color: transparent  a = 6       p = 12
id:2 type: Triangle         color: blue         a = 6       p = 12
id:3 type: Ellipse          color: red          a = 37.700  p = 22.849
id:4 type: Rectangle        color: red          a = 9       p = 12
*/

TEST_F(UtilityTesting, areaFilter) {
    std::deque<Shape*> shapesInDeque = filterShape(compoundShape_0, AreaFilter(15, 5));
    ASSERT_EQ(3, shapesInDeque.size());
    ASSERT_EQ("1", shapesInDeque[0]->id());
    ASSERT_EQ("Compound Shape", shapesInDeque[0]->type());
    ASSERT_EQ("2", shapesInDeque[1]->id());
    ASSERT_EQ("Triangle", shapesInDeque[1]->type());
    ASSERT_EQ("4", shapesInDeque[2]->id());
    ASSERT_EQ("Rectangle", shapesInDeque[2]->type());
    shapesInDeque.clear();

    shapesInDeque = filterShape(compoundShape_0, AreaFilter(40, 20));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("3", shapesInDeque[0]->id());
    ASSERT_EQ("Ellipse", shapesInDeque[0]->type());
    shapesInDeque.clear();
    shapesInDeque = filterShape(compoundShape_0, AreaFilter(40, 1));
    ASSERT_EQ(4, shapesInDeque.size());
    ASSERT_EQ("1", shapesInDeque[0]->id());
    ASSERT_EQ("Compound Shape", shapesInDeque[0]->type());
    ASSERT_EQ("2", shapesInDeque[1]->id());
    ASSERT_EQ("Triangle", shapesInDeque[1]->type());
    ASSERT_EQ("3", shapesInDeque[2]->id());
    ASSERT_EQ("Ellipse", shapesInDeque[2]->type());
    ASSERT_EQ("4", shapesInDeque[3]->id());
    ASSERT_EQ("Rectangle", shapesInDeque[3]->type());

}


TEST_F(UtilityTesting, perimeterFilter) {
    std::deque<Shape*> shapesInDeque = filterShape(compoundShape_0, PerimeterFilter(15, 5));
    ASSERT_EQ(3, shapesInDeque.size());
    ASSERT_EQ("1", shapesInDeque[0]->id());
    ASSERT_EQ("Compound Shape", shapesInDeque[0]->type());
    ASSERT_EQ("2", shapesInDeque[1]->id());
    ASSERT_EQ("Triangle", shapesInDeque[1]->type());
    ASSERT_EQ("4", shapesInDeque[2]->id());
    ASSERT_EQ("Rectangle", shapesInDeque[2]->type());
    shapesInDeque.clear();
    shapesInDeque = filterShape(compoundShape_0, PerimeterFilter(30, 20));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("3", shapesInDeque[0]->id());
    ASSERT_EQ("Ellipse", shapesInDeque[0]->type());
    shapesInDeque.clear();
    shapesInDeque = filterShape(compoundShape_0, PerimeterFilter(30, 1));
    ASSERT_EQ(4, shapesInDeque.size());
    ASSERT_EQ("1", shapesInDeque[0]->id());
    ASSERT_EQ("Compound Shape", shapesInDeque[0]->type());
    ASSERT_EQ("2", shapesInDeque[1]->id());
    ASSERT_EQ("Triangle", shapesInDeque[1]->type());
    ASSERT_EQ("3", shapesInDeque[2]->id());
    ASSERT_EQ("Ellipse", shapesInDeque[2]->type());
    ASSERT_EQ("4", shapesInDeque[3]->id());
    ASSERT_EQ("Rectangle", shapesInDeque[3]->type());
}

TEST_F(UtilityTesting, typeFilter) {
    std::deque<Shape*> shapesInDeque = filterShape(compoundShape_0, TypeFilter("Compound Shape"));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("1", shapesInDeque[0]->id());
    ASSERT_EQ("Compound Shape", shapesInDeque[0]->type());
    shapesInDeque.clear();
    shapesInDeque = filterShape(compoundShape_0, TypeFilter("Triangle"));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("2", shapesInDeque[0]->id());
    ASSERT_EQ("Triangle", shapesInDeque[0]->type());
    shapesInDeque = filterShape(compoundShape_0, TypeFilter("Rectangle"));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("4", shapesInDeque[0]->id());
    ASSERT_EQ("Rectangle", shapesInDeque[0]->type());
    shapesInDeque.clear();
    shapesInDeque = filterShape(compoundShape_0, TypeFilter("Ellipse"));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("3", shapesInDeque[0]->id());
    ASSERT_EQ("Ellipse", shapesInDeque[0]->type());
}

TEST_F(UtilityTesting, colorFilter) {
    std::deque<Shape*> shapesInDeque = filterShape(compoundShape_0, ColorFilter("transparent"));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("1", shapesInDeque[0]->id());
    ASSERT_EQ("Compound Shape", shapesInDeque[0]->type());
    shapesInDeque.clear();
    shapesInDeque = filterShape(compoundShape_0, ColorFilter("blue"));
    ASSERT_EQ(1, shapesInDeque.size());
    ASSERT_EQ("2", shapesInDeque[0]->id());
    ASSERT_EQ("Triangle", shapesInDeque[0]->type());
    shapesInDeque = filterShape(compoundShape_0, ColorFilter("red"));
    ASSERT_EQ(2, shapesInDeque.size());
    ASSERT_EQ("4", shapesInDeque[1]->id());
    ASSERT_EQ("Rectangle", shapesInDeque[1]->type());
    ASSERT_EQ("3", shapesInDeque[0]->id());
    ASSERT_EQ("Ellipse", shapesInDeque[0]->type());
}

TEST_F(UtilityTesting, filterShapeException) {
    try
    {
        filterShape(new Rectangle("50", 50, 40, "black"), ColorFilter("transparent"));
    }
    catch(std::string e)
    {
        ASSERT_EQ("Only compound shape can filter shape!", e);
    }    
}
