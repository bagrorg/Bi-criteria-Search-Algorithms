#pragma once

#include <cstddef>
#include "Open.hpp"
#include <set>
#include <unordered_map>
#include <Service/Node.hpp>
#include "Service/PairHash.hpp"

class MapSetOpen : public Open<NodePtr> {
public:
    size_t size() const override;
    void add(NodePtr n) override;
    bool isEmpty() const override;
    NodePtr getBest() override;
    void clear() override;
private:
    std::set<NodePtr> heap_;
    std::unordered_map<int, NodePtr> nodes_;
};