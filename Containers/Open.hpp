#pragma once

#include <cstddef>

template<typename T>
class Open {
public:
    virtual size_t size() const = 0;
    virtual void add(T n) = 0;
    virtual bool isEmpty() const = 0;
    virtual T getBest() = 0;
};