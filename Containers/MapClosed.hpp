#pragma once

#include <cstddef>
#include <unordered_map>
#include <Service/Node.hpp>
#include "Closed.hpp"
#include "Service/PairHash.hpp"

class MapClosed : public Closed<NodePtr> {
public:
    size_t size() const override;
    void add(NodePtr n) override;
    bool wasExpanded(const NodePtr& n) const override;
private:
    std::unordered_map<int, NodePtr> nodes_;
};