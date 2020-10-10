#include <gtest/gtest.h>

#include "../src/rectangle.h"
#define ABS_ERROR 0.001

class RectangleTesting : public ::testing::Test {
protected:
    Rectangle * rectangle; 

    void SetUp() override {
        rectangle = new Rectangle("20201010", 2, 2);
    }
    void TearDown() override {
        delete rectangle;
    }
};

TEST_F(RectangleTesting, getInfo){
    delete rectangle;
    rectangle = new Rectangle("20201010", 1.0, 1.0);
    ASSERT_EQ("Rectangle (1.000, 1.000)", rectangle->info());
    delete rectangle;
    rectangle = new Rectangle("20201010", 4.123, 5.3215);
    ASSERT_EQ("Rectangle (4.123, 5.321)", rectangle->info());
}

TEST_F(RectangleTesting, testCreateRectangle){
    try
    {
        Rectangle rectangle("20201010", 0, 1.0);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a rectangle!", e);
    }

    try
    {
        Rectangle rectangle("20201010", -1.54, 1.0);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a rectangle!", e);
    }
    ASSERT_NO_THROW(Rectangle("20201010", 1, 1));
}

TEST_F(RectangleTesting, testGetArea) {
    delete rectangle;
    rectangle = new Rectangle("20201010", 4, 5);
    ASSERT_NEAR(20.0, rectangle->area(), ABS_ERROR);
    delete rectangle;
    rectangle = new Rectangle("20201010", 4.123, 5.789);
    ASSERT_NEAR(23.868, rectangle->area(), ABS_ERROR);
    delete rectangle;
    rectangle = new Rectangle("20201010", 111, 999);
    ASSERT_EQ(110889.0, rectangle->area());
}

TEST_F(RectangleTesting, testGetPerimeter) {
    delete rectangle;
    rectangle = new Rectangle("20201010", 4, 5);
    ASSERT_NEAR(18.0, rectangle->perimeter(), ABS_ERROR);
    delete rectangle;
    rectangle = new Rectangle("20201010", 4.123, 5.789);
    ASSERT_NEAR(19.824, rectangle->perimeter(), ABS_ERROR);
    delete rectangle;
    rectangle = new Rectangle("20201010", 111, 999);
    ASSERT_NEAR(2220.0, rectangle->perimeter(), ABS_ERROR);
}

TEST_F(RectangleTesting, testGetId) {
    ASSERT_EQ("20201010", rectangle->id());
}

TEST_F(RectangleTesting, testGetColorWhite) {
    ASSERT_EQ("white", rectangle->color());
}

TEST_F(RectangleTesting, constructor) {
    Rectangle r1("123654987", 4, 3);
    ASSERT_EQ("123654987", r1.id());
    ASSERT_EQ("white", r1.color());
    Rectangle r2("123654987", 4, 3, "red");
    ASSERT_EQ("123654987", r2.id());
    ASSERT_EQ("red", r2.color());
}