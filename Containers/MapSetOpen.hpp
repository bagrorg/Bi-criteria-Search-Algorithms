#pragma once

#include <stddef.h>
#include "Open.hpp"
#include <set>
#include <unordered_map>
#include "Service/PairHash.hpp"

class MapSetOpen : public Open {
public:
    virtual size_t size() const;
    virtual void addNode(Node n);
    virtual bool empty() const;
    virtual Node getBestNode();
private:
    std::set<Node> heap_;
    std::unordered_map<std::pair<long, long>, Node, PairHash> nodes_;
};