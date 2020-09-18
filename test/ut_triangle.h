#include <gtest/gtest.h>

#include "../src/two_dimensional_coordinate.h"
#include "../src/triangle.h"

#define ABS_ERROR 0.001

TEST(Triangle, getInfo){
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle triangle = Triangle(triangleVector);
    ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", triangle.info());
}

TEST(Triangle, testCreateTriangle) {
    try
    {
        std::vector<TwoDimensionalCoordinate*> triangleVector = std::vector<TwoDimensionalCoordinate*>();
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        Triangle triangle = Triangle(triangleVector);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a triangle!", e);
    }

    try
    {
        std::vector<TwoDimensionalCoordinate*> triangleVector = std::vector<TwoDimensionalCoordinate*>();
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 1));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 2));
        Triangle triangle = Triangle(triangleVector);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a triangle!", e);
    }

    try
    {
        std::vector<TwoDimensionalCoordinate*> triangleVector = std::vector<TwoDimensionalCoordinate*>();
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(2, 2));
        triangleVector.push_back(new TwoDimensionalCoordinate(2, 2));
        Triangle triangle = Triangle(triangleVector);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a triangle!", e);
    }
    std::vector<TwoDimensionalCoordinate*> triangleVector = std::vector<TwoDimensionalCoordinate*>();
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 3));
    triangleVector.push_back(new TwoDimensionalCoordinate(4, 0));
    ASSERT_NO_THROW(Triangle triangle(triangleVector));

}

TEST(Triangle, testGetArea) {
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle triangle = Triangle(triangleVector);
    ASSERT_NEAR(6.000, triangle.area(), ABS_ERROR);
}

TEST(Triangle, testGetPerimeter) {
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
    triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
    Triangle triangle = Triangle(triangleVector);
    ASSERT_NEAR(12.000, triangle.perimeter(), ABS_ERROR);
}
