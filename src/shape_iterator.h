#ifndef SHAPE_ITERATOR_H
#define SHAPE_ITERATOR_H

#include "iterator.h"
#include <string>

template<class ForwardIterator>
class ShapeIterator : public Iterator {
private:
    ForwardIterator const _begin;
    ForwardIterator const _end;
    ForwardIterator _currentItem;

public:
    ShapeIterator(ForwardIterator begin, ForwardIterator end):_begin(begin), _end(end) {
        // initialize iterator
        first();
    }

    void first() {
        // initialize iterator.
        _currentItem = _begin;
    }

    void next() {
        if (_currentItem != _end) {
            ++_currentItem;
            return;
        }
        throw std::string("Moving past the end!");
        // move iterator to next position,
        // throw std::string "Moving past the end!" when iterator move over the range of the structure.
    }

    bool isDone() const {
        return _currentItem == _end;
        // return true when iterator reach the end of the structure.
    }

    Shape* currentItem() const {
        return *_currentItem;
        // return the shape that iterator currently point at.
    }
};
#endif