#include <gtest/gtest.h>

#include "../src/ellipse.h"

#define ABS_ERROR 0.001

TEST(Ellipse, getInfo){
    Ellipse ellipse = Ellipse(5.0, 1.0);
    ASSERT_EQ("Ellipse (5.000, 1.000)", ellipse.info());
    ellipse = Ellipse(5.3215, 4.123);
    ASSERT_EQ("Ellipse (5.321, 4.123)", ellipse.info());
}

TEST(Ellipse, testCreateEllipse){
    try
    {
        Ellipse ellipse(0, 1.0);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a ellipse!", e);
    }

    try
    {
        Ellipse ellipse(-1.54, 1.0);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a ellipse!", e);
    }

        try
    {
        Ellipse ellipse(1.132, 80.21);
        FAIL();
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a ellipse!", e);
    }

    ASSERT_NO_THROW(Ellipse(90.50, 40.9));
}

TEST(Ellipse, testGetArea) {
    Ellipse ellipse = Ellipse(5.0, 4.0);
    ASSERT_NEAR(62.831, ellipse.area(), ABS_ERROR);
    ellipse = Ellipse(5.123, 4.789);
    ASSERT_NEAR(77.075, ellipse.area(), ABS_ERROR);
    ellipse = Ellipse(888, 111);
    ASSERT_NEAR(309660.243, ellipse.area(), ABS_ERROR);
}

TEST(Ellipse, testGetPerimeter) {
    Ellipse ellipse = Ellipse(5.0, 4.0);
    ASSERT_NEAR(29.132, ellipse.perimeter(), ABS_ERROR);
    ellipse = Ellipse(5.123, 4.789);
    ASSERT_NEAR(31.426, ellipse.perimeter(), ABS_ERROR);
    ellipse = Ellipse(888, 111);
    ASSERT_NEAR(3805.432, ellipse.perimeter(), ABS_ERROR);    
}