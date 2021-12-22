#pragma once

#include <cstddef>

template<typename T>
class Closed {
public:
    virtual size_t size() const = 0;
    virtual void add(T n) = 0;
    virtual bool wasExpanded(const T& n) const = 0;
};