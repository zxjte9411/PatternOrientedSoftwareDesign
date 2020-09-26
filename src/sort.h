#include "shape.h"

#ifndef SORT
#define SORT

class Sort {
public:
    bool areaAscendingCompare(Shape *a, Shape *b) {
        return false;
    };

    bool areaDescendingCompare(Shape *a, Shape *b) {
        return false;
    };

    bool perimeterAscendingCompare(Shape *a, Shape *b) {
        return false;
    };

    bool perimeterDescendingCompare(Shape *a, Shape *b) {
        return false;
    };
};

class AscendingCompare{
private:
    std::string _feature;
public:
    AscendingCompare(std::string feature): _feature(feature) {}
};

class DescendingCompare{
private:
    std::string _feature;
public:
    DescendingCompare(std::string feature): _feature(feature) {}
};

#endif // SORT