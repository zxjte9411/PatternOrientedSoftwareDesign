#include <gtest/gtest.h>

#include "../src/rectangle.h"

TEST(Rectangle, getInfo){
    Rectangle rectangle(1.0, 1.0);
    ASSERT_EQ("Rectangle (1.000, 1.000)", rectangle.info());
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
    ASSERT_NO_THROW(Rectangle(1, 1));
}