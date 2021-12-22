#pragma once

#include <stddef.h>
#include "Service/Node.hpp"

class Closed {
public:
    virtual size_t size() const = 0;
    virtual void addNode(Node n) = 0;
    virtual bool wasExpanded(Node n) const = 0;
};