#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/shape_iterator.h"
#include "../src/compound_shape.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"

#include <gtest/gtest.h>

class IteratorTesting : public ::testing::Test {
protected :
    void SetUp() override {
        shapes = new std::list<Shape*>();
        shapes->push_back(new Rectangle("0", 3, 4, "red"));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        shapes->push_back(new Triangle("1", triangleVector, "blue"));
        shapes->push_back(new Rectangle("2", 2, 2, "red"));
        compoundShape = new CompoundShape("20201010", shapes);
        sit = new ShapeIterator<std::list<Shape*>::iterator>(shapes->begin(), shapes->end());
    }
    
    void TearDown() override {
        if (compoundShape != nullptr) {
            delete compoundShape;
            compoundShape = nullptr;
        }
        delete shapes;
        delete sit;
    }

    CompoundShape * compoundShape;
    std::list<Shape*> * shapes;
    std::vector<TwoDimensionalCoordinate*> triangleVector;
    Iterator * sit;
};

TEST_F(IteratorTesting, createIterators) {
    Iterator * it = new NullIterator();
    ASSERT_TRUE(it->isDone());
    Iterator * _sit = new ShapeIterator<std::list<Shape*>::iterator>(shapes->begin(), shapes->end());
    ASSERT_FALSE(_sit->isDone());
    delete _sit;
    delete it;
}

TEST_F(IteratorTesting, next) {
    ASSERT_FALSE(sit->isDone());
    EXPECT_EQ("0", sit->currentItem()->id());

    ASSERT_NO_THROW(sit->next());
    EXPECT_EQ("1", sit->currentItem()->id());

    ASSERT_NO_THROW(sit->next());
    EXPECT_EQ("2", sit->currentItem()->id());
    ASSERT_NO_THROW(sit->next());
    ASSERT_TRUE(sit->isDone());
    try
    {
        sit->next();
        FAIL();
    }
    catch(std::string e)
    {
        EXPECT_EQ("Moving past the end!", e);
    }
}

TEST_F(IteratorTesting, first) {
    ASSERT_FALSE(sit->isDone());
    ASSERT_NO_THROW(sit->next());
    ASSERT_NO_THROW(sit->next());
    ASSERT_NO_THROW(sit->next());
    ASSERT_TRUE(sit->isDone());
    sit->first();
    EXPECT_EQ("0", sit->currentItem()->id());
}

TEST_F(IteratorTesting, isDone) {
    ASSERT_FALSE(sit->isDone());
    ASSERT_NO_THROW(sit->next());
    ASSERT_NO_THROW(sit->next());
    ASSERT_NO_THROW(sit->next());
    ASSERT_TRUE(sit->isDone());
    sit->first();
    ASSERT_FALSE(sit->isDone());
}

TEST_F(IteratorTesting, currentItem) {
    std::list<Shape*>::iterator it = shapes->begin();
    ASSERT_FALSE(sit->isDone());
    EXPECT_EQ(*it, sit->currentItem());
    ASSERT_NO_THROW(sit->next());
    ASSERT_NO_THROW(sit->next());
    ASSERT_NO_THROW(sit->next());
    ASSERT_TRUE(sit->isDone());
    it = shapes->end();
    EXPECT_EQ(*it, sit->currentItem());
}

TEST_F(IteratorTesting, nullIteratorExceptions) {
    Iterator * nit = new NullIterator();
    try
    {
        nit->first();
    }
    catch(std::string e)
    {
        EXPECT_EQ("No child member!", e);
    }
    try
    {
        nit->currentItem();
    }
    catch(std::string e)
    {
        EXPECT_EQ("No child member!", e);
    }
    try
    {
        nit->next();
    }
    catch(std::string e)
    {
        EXPECT_EQ("No child member!", e);
    }
}