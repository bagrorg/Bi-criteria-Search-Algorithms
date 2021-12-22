#pragma once

#include <stddef.h>
#include "Service/Node.hpp"

class Open {
public:
    virtual size_t size() const = 0;
    virtual void addNode(Node n) = 0;
    virtual bool empty() const = 0;
    virtual Node getBestNode() = 0;
};