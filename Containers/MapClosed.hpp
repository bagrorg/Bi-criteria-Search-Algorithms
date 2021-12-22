#pragma once

#include <cstddef>
#include <unordered_map>
#include <Service/Node.hpp>
#include "Closed.hpp"
#include "Service/PairHash.hpp"

class MapClosed : public Closed<Node> {
public:
    size_t size() const override;
    void add(Node n) override;
    bool wasExpanded(const Node& n) const override;
private:
    std::unordered_map<Position, Node, PairHash> nodes_;
};