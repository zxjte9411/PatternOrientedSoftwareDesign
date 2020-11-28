
#include "../src/shape_builder.h"

#include <ctype.h>
#include <gtest/gtest.h>
#include <cmath>
#include <deque>

class ShapeBuilderTesting : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {
    }
};

TEST_F(ShapeBuilderTesting, buildTriangle) {
    ShapeBuilder sb;
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST_F(ShapeBuilderTesting, buildRectangle) {
    ShapeBuilder sb;
    sb.buildRectangle(4, 3);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (4.000, 3.000)", results[0]->info());
}

TEST_F(ShapeBuilderTesting, buildEllipse) {
    ShapeBuilder sb;
    sb.buildEllipse(5, 4);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (5.000, 4.000)", results[0]->info());
}

TEST_F(ShapeBuilderTesting, buildompoundShape){
    ShapeBuilder * sb = new ShapeBuilder();
    sb->buildCompoundShapeBegin();
    sb->buildRectangle(2, 2);
    sb->buildTriangle(0, 0, 0, -3, -4, 0);
    sb->buildCompoundShapeEnd();
    std::deque<Shape *> result = sb->getResult();
    ASSERT_EQ(1,result.size());
    ASSERT_EQ(10,result[0]->area());
}

TEST_F(ShapeBuilderTesting, buildEmptyCompoundShape){
    ShapeBuilder * sb = new ShapeBuilder();
    sb->buildTriangle(0, 0, 0, -3, -4, 0);
    sb->buildCompoundShapeBegin();
    
    sb->buildCompoundShapeBegin();
    sb->buildCompoundShapeBegin();
    
    sb->buildCompoundShapeEnd();
    sb->buildCompoundShapeEnd();
    
    sb->buildTriangle(0, 0, 0, -3, -4, 0);
    sb->buildCompoundShapeEnd();
    
    sb->buildTriangle(0, 0, 0, -3, -4, 0);
    std::deque<Shape *> result = sb->getResult();
    ASSERT_EQ(3, result.size());
    // ASSERT_EQ(0, result[0]->area());
}

TEST_F(ShapeBuilderTesting, buildForest){
    ShapeBuilder * sb = new ShapeBuilder();
    sb->buildRectangle(5, 5);
    sb->buildCompoundShapeBegin();
    sb->buildRectangle(3, 4);
    sb->buildCompoundShapeBegin();
    sb->buildRectangle(2, 2);
    sb->buildTriangle(0, 0, 0, -3, -4, 0);
    sb->buildCompoundShapeEnd();
    sb->buildCompoundShapeEnd();
    sb->buildTriangle(0, 0, 1, 0, 1, std::sqrt(2));
    std::deque<Shape *> result = sb->getResult();
    ASSERT_EQ(3, result.size());
    ASSERT_EQ(25, result[0]->area());
    ASSERT_EQ(22, result[1]->area());
    ASSERT_NEAR(0.707, result[2]->area(), 0.001);
}