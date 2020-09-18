#include <gtest/gtest.h>

#include "../src/rectangle.h"
#define ABS_ERROR 0.001

TEST(Rectangle, getInfo){
    Rectangle rectangle = Rectangle(1.0, 1.0);
    ASSERT_EQ("Rectangle (1.000, 1.000)", rectangle.info());
    rectangle = Rectangle(4.123, 5.3215);
    ASSERT_EQ("Rectangle (4.123, 5.321)", rectangle.info());
}

TEST(Rectangle, testCreateRectangle){
    try
    {
        Rectangle rectangle(0, 1.0);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a rectangle!", e);
    }

    try
    {
        Rectangle rectangle(-1.54, 1.0);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a rectangle!", e);
    }
    ASSERT_NO_THROW(Rectangle(1, 1));
}

TEST(Rectangle, testGetArea) {
    Rectangle rectangle = Rectangle(4, 5);
    ASSERT_NEAR(20.0, rectangle.area(), ABS_ERROR);
    rectangle = Rectangle(4.123, 5.789);
    ASSERT_NEAR(23.868, rectangle.area(), ABS_ERROR);
    rectangle = Rectangle(111, 999);
    ASSERT_EQ(110889.0, rectangle.area());
}

TEST(Rectangle, testGetPerimeter) {
    Rectangle rectangle = Rectangle(4, 5);
    ASSERT_NEAR(18.0, rectangle.perimeter(), ABS_ERROR);
    rectangle = Rectangle(4.123, 5.789);
    ASSERT_NEAR(19.824, rectangle.perimeter(), ABS_ERROR);
    rectangle = Rectangle(111, 999);
    ASSERT_NEAR(2220.0, rectangle.perimeter(), ABS_ERROR);
}