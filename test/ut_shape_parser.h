#include "../src/shape_parser.h"

#include <ctype.h>
#include <gtest/gtest.h>
#include <deque>

class ShapeParserTesting : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {
    }
};

TEST_F(ShapeParserTesting, parserRectangle) {
    ShapeParser sp("Rectangle (2, 2)");
    sp.parser();
    std::deque<Shape*> results = sp.getResult();
    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (2.000, 2.000)", results[0]->info());
    ASSERT_EQ(4.000, results[0]->area());
    ASSERT_EQ(8.000, results[0]->perimeter());
}

TEST_F(ShapeParserTesting, parserEllipse) {
    ShapeParser sp("Ellipse (5, 4)");
    sp.parser();
    std::deque<Shape*> results = sp.getResult();
    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (5.000, 4.000)", results[0]->info());
    ASSERT_NEAR(62.831, results[0]->area(), 0.001);
    ASSERT_NEAR(29.132, results[0]->perimeter(), 0.001);
}

TEST_F(ShapeParserTesting, parserTriangle) {
    ShapeParser sp("Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();
    std::deque<Shape*> results = sp.getResult();
    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
    ASSERT_EQ(6, results[0]->area());
    ASSERT_EQ(12, results[0]->perimeter());
}

TEST_F(ShapeParserTesting, parserCompoundShape) {
    ShapeParser sp("Ellipse (5.000, 4.000), CompoundShape {Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000), Ellipse (5.000, 4.000), Rectangle (2.000, 2.000), CompoundShape {Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000), Ellipse (5.000, 4.000), Rectangle (2.000, 2.000)}}");
    sp.parser();
    std::deque<Shape*> results = sp.getResult();
    ASSERT_EQ(2, results.size());
    std::string anwser = "Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Ellipse (5.000, 4.000), Rectangle (2.000, 2.000), Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Ellipse (5.000, 4.000), Rectangle (2.000, 2.000)}}";
    ASSERT_EQ("Ellipse (5.000, 4.000)", results[0]->info());
    ASSERT_EQ(anwser, results[1]->info());
    ASSERT_NEAR(145.663, results[1]->area(), 0.001);
    ASSERT_NEAR(98.265, results[1]->perimeter(), 0.001);
}

TEST_F(ShapeParserTesting, parser_multi_simple_shapes_with_one_shape_contain_invalid_argument_that_should_be_ignored) {

    ShapeParser sp("Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Ellipse (4.200, 3.700, 12.502), Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(3, results.size());

    EXPECT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[1]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[2]->info());
}

TEST_F(ShapeParserTesting, parserCompoundShapeWithSomeSShapeIsFalse) {
    ShapeParser sp("Ellipse (5.000, 4.000), CompoundShape {Triangl (0.000, 0.000, 0.000, -3.000, -4.000, 0.000), Ellipse (5.000, 4.000), Rectangle (2.000, 2.000), CompoundShape {Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000), Ellipse (5.000, 4.000), Rectangle (2.000, 2.000)}}");
    sp.parser();
    std::deque<Shape*> results = sp.getResult();
    ASSERT_EQ(2, results.size());
    std::string anwser = "Compound Shape {Ellipse (5.000, 4.000), Rectangle (2.000, 2.000), Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Ellipse (5.000, 4.000), Rectangle (2.000, 2.000)}}";
    ASSERT_EQ("Ellipse (5.000, 4.000)", results[0]->info());
}