
#include "../src/scanner.h"

#include <ctype.h>
#include <gtest/gtest.h>
#include <list>

class ScannerTesting : public ::testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {
    }
};

TEST_F(ScannerTesting, ellipse) {
    Scanner scanner("Ellipse (4.000, 3.000)");
    ASSERT_EQ("Ellipse", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    } catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST_F(ScannerTesting, rectangle) {
    Scanner scanner("Rectangle (4.000, 3.000)");
    ASSERT_EQ("Rectangle", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    } catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST_F(ScannerTesting, triangle) {
    Scanner scanner("Triangle (4.000, 3.000, -1.000, 0.000, -3.000, -2.050)");
    ASSERT_EQ("Triangle", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-1.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-3.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-2.050", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    } catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST_F(ScannerTesting, scan_multi_line_string) {
    Scanner scanner("Ellipse (4.000, 3.000)\n  Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)(   )");

    ASSERT_EQ("Ellipse", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    ASSERT_EQ("Triangle", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-3.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    } catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST_F(ScannerTesting, compoundShape) {
    Scanner scanner("CompoundShape {Triangle (4.000, 3.000, -1.000, 0.000, -3.000, -2.050),Ellipse (4.000, 3.000)}");
    ASSERT_EQ("CompoundShape", scanner.nextToken());
    ASSERT_EQ("{", scanner.nextToken());
    ASSERT_EQ("Triangle", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-1.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-3.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-2.050", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("Ellipse", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());
    ASSERT_EQ("}", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    } catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}