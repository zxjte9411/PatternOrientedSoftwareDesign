#include "../src/sort.h"
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"
#include "../src/two_dimensional_coordinate.h"

#include <gtest/gtest.h>
#include <vector>

class SortTesting : public ::testing::Test {
protected:
    void SetUp() override {
        shapes = std::vector<Shape *>();
        twoDimensionalCoordinats = std::vector<TwoDimensionalCoordinate *>();
        shapes.push_back(new Rectangle(2, 2));
        shapes.push_back(new Rectangle(4, 4));
        shapes.push_back(new Rectangle(1, 1));
        shapes.push_back(new Rectangle(3, 3));
        twoDimensionalCoordinats.push_back(new TwoDimensionalCoordinate(0, 0));
        twoDimensionalCoordinats.push_back(new TwoDimensionalCoordinate(3, 0));
        twoDimensionalCoordinats.push_back(new TwoDimensionalCoordinate(0, 4));
        shapes.push_back(new Triangle(twoDimensionalCoordinats));
        shapes.push_back(new Ellipse(5.0, 4.0));
    }

    void TearDown() override {
        for (int i = 0; i < shapes.size(); i++) 
            delete shapes[i];
        for (int i = 0; i < twoDimensionalCoordinats.size(); i++) 
            delete twoDimensionalCoordinats[i];
    }
    std::vector<Shape *> shapes;
    std::vector<TwoDimensionalCoordinate*> twoDimensionalCoordinats;
};

/*
area
1
4
9
16
6
62.831
*/
#include <algorithm>
TEST_F(SortTesting, testAreaAscendingCompare) {
    std::sort(shapes.begin(), shapes.end(), areaAscendingCompare);
    EXPECT_EQ(1, shapes[0]->area());
    EXPECT_EQ(4, shapes[1]->area());
    EXPECT_EQ(6, shapes[2]->area());
    EXPECT_EQ(9, shapes[3]->area());
    EXPECT_EQ(16, shapes[4]->area());
    EXPECT_EQ(62.831, shapes[5]->area());
}

TEST_F(SortTesting, testAreaDescendingCompare) {
    std::sort(shapes.begin(), shapes.end(), areaDescendingCompare);
    EXPECT_EQ(1, shapes[5]->area());
    EXPECT_EQ(4, shapes[4]->area());
    EXPECT_EQ(6, shapes[3]->area());
    EXPECT_EQ(9, shapes[2]->area());
    EXPECT_EQ(16, shapes[1]->area());
    EXPECT_EQ(62.831, shapes[0]->area());
}

/*
perimeter
8
16
4
12
12
29.132
*/
TEST_F(SortTesting, testPerimeterAscendingCompare) {
    std::sort(shapes.begin(), shapes.end(), perimeterAscendingCompare);
    EXPECT_EQ(4, shapes[0]->perimeter());
    EXPECT_EQ(8, shapes[1]->perimeter());
    EXPECT_EQ(12, shapes[2]->perimeter());
    EXPECT_EQ(12, shapes[3]->perimeter());
    EXPECT_EQ(16, shapes[4]->perimeter());
    EXPECT_EQ(29.132, shapes[5]->perimeter());
}

TEST_F(SortTesting, testPerimeterDescendingCompare) {
    std::sort(shapes.begin(), shapes.end(), perimeterDescendingCompare);
    EXPECT_EQ(4, shapes[5]->perimeter());
    EXPECT_EQ(8, shapes[4]->perimeter());
    EXPECT_EQ(12, shapes[3]->perimeter());
    EXPECT_EQ(12, shapes[2]->perimeter());
    EXPECT_EQ(16, shapes[1]->perimeter());
    EXPECT_EQ(29.132, shapes[0]->perimeter());
}

/*AscendingCompare & DescendingCompare Testing ↓*/

TEST_F(SortTesting, testAscendingCompareUseArea) {
    std::sort(shapes.begin(), shapes.end(), AscendingCompare("area"));
    EXPECT_EQ(1, shapes[0]->area());
    EXPECT_EQ(4, shapes[1]->area());
    EXPECT_EQ(6, shapes[2]->area());
    EXPECT_EQ(9, shapes[3]->area());
    EXPECT_EQ(16, shapes[4]->area());
    EXPECT_EQ(62.831, shapes[5]->area());
}

TEST_F(SortTesting, testAscendingCompareUsePerimeter) {
    std::sort(shapes.begin(), shapes.end(), AscendingCompare("perimeter"));
    EXPECT_EQ(4, shapes[0]->perimeter());
    EXPECT_EQ(8, shapes[1]->perimeter());
    EXPECT_EQ(12, shapes[2]->perimeter());
    EXPECT_EQ(12, shapes[3]->perimeter());
    EXPECT_EQ(16, shapes[4]->perimeter());
    EXPECT_EQ(29.132, shapes[5]->perimeter());
}

TEST_F(SortTesting, testDescendingCompareUseArea) {
    std::sort(shapes.begin(), shapes.end(), DescendingCompare("area"));
    EXPECT_EQ(4, shapes[5]->perimeter());
    EXPECT_EQ(8, shapes[4]->perimeter());
    EXPECT_EQ(12, shapes[3]->perimeter());
    EXPECT_EQ(12, shapes[2]->perimeter());
    EXPECT_EQ(16, shapes[1]->perimeter());
    EXPECT_EQ(29.132, shapes[0]->perimeter());
}

TEST_F(SortTesting, testDescendingCompareUsePerimeter) {
    std::sort(shapes.begin(), shapes.end(), DescendingCompare("perimeter"));
    EXPECT_EQ(4, shapes[5]->perimeter());
    EXPECT_EQ(8, shapes[4]->perimeter());
    EXPECT_EQ(12, shapes[3]->perimeter());
    EXPECT_EQ(12, shapes[2]->perimeter());
    EXPECT_EQ(16, shapes[1]->perimeter());
    EXPECT_EQ(29.132, shapes[0]->perimeter());
}
