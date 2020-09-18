#include <gtest/gtest.h>

#include "../src/rectangle.h"

TEST(Rectangle, getInfo){
    Rectangle rectangle(1.0, 1.0);
    ASSERT_EQ("Rectangle (1.000, 1.000)", rectangle.info());
}
