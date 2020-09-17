#include "../src/rectangle.h"

#include <gtest/gtest.h>

TEST(Rectangle, getTest){
    Rectangle rectangle(1.0, 1.0);
    // ASSERT_TRUE(false);
    ASSERT_EQ("Rectangle (3.712, 4.000)", rectangle.info());
}
