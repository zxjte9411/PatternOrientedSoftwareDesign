#include <gtest/gtest.h>
#include "../src/terminal.h"

class TerminnalTesting : public ::testing::Test {
protected:
void SetUp() override {
    // terminal = new Terminal("");
}

void TearDown() override {
    // delete terminal;
}

// Terminal * terminal;
};

TEST_F(TerminnalTesting, createTerminal) {
    try
    {
        Terminal terminal("");
        FAIL();
    }
    catch(const std::string e)
    {
        ASSERT_EQ("invalid input", e);
    }

    try
    {
        Terminal terminal("Rectangle (3.7, 4.2) Ellipse (3, 4) area");
        FAIL();
    }
    catch(const std::string e)
    {
        ASSERT_EQ("invalid input", e);
    }
    
    try
    {
        Terminal terminal("Rectangle (3.7, 4.2) Ellipse (3, 4) inc");
        FAIL();
    }
    catch(const std::string e)
    {
        ASSERT_EQ("invalid input", e);
    }
    
    try
    {
        Terminal terminal("area inc");
        FAIL();
    }
    catch(const std::string e)
    {
        ASSERT_EQ("invalid input", e);
    }

    ASSERT_NO_THROW(Terminal("Rectangle (3.7, 4.2) Ellipse (3, 4) Triangle ([0,-3], [-3,0], [0,-4]) area inc"));
}

