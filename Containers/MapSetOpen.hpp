#pragma once

#include <cstddef>
#include "Open.hpp"
#include <set>
#include <unordered_map>
#include <Service/Node.hpp>
#include "Service/PairHash.hpp"
#include <iostream>
#include "Service/BOANode.hpp"

class MapSetOpen : public Open<BOANode> {
public:
    size_t size() const override;
    void add(BOANode n) override;
    bool isEmpty() const override;
    BOANode getBest() override;
    void clear() override;
    std::vector<Node> getAddedNodes();
    std::vector<Node> getAllNodes();
private:
    std::set<BOANode> heap_;
    std::vector<Node> added_;
};