#pragma once

#include <cstddef>
#include "Open.hpp"
#include <set>
#include <unordered_map>
#include <Service/Node.hpp>
#include "Service/PairHash.hpp"

class MapSetOpen : public Open<Node> {
public:
    size_t size() const override;
    void add(Node n) override;
    bool isEmpty() const override;
    Node getBest() override;
private:
    std::set<Node> heap_;
    std::unordered_map<Position, Node, PairHash> nodes_;
};