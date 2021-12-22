#pragma once

#include <stddef.h>
#include <unordered_map>
#include "Closed.hpp"
#include "Service/PairHash.hpp"

class MapClosed : public Closed {
public:
    virtual size_t size() const;
    virtual void addNode(Node n);
    virtual bool wasExpanded(Node n) const;
private:
    std::unordered_map<std::pair<long, long>, Node, PairHash> nodes_;
};