#include "MapSetOpen.hpp"
#include <iostream>

size_t MapSetOpen::size() const {
    return nodes_.size();
}

size_t MapSetOpen::size2() const {
    return heap_.size();
}


void MapSetOpen::add(BOANode n) {
    auto id = n.getId();

    if (nodes_.find(id) != nodes_.end()) {
       if (nodes_[id].getNode()->getHeuristicStatsDist().g <= n.getNode()->getHeuristicStatsDist().g &&
            nodes_[id].getNode()->getHeuristicStatsTime().g <= n.getNode()->getHeuristicStatsTime().g) {
           return;
       }
    }

    nodes_[id] = n;
    heap_.insert(n).second;
}

bool MapSetOpen::isEmpty() const {
    return size() == 0;
}

BOANode MapSetOpen::getBest() {
    auto it = heap_.extract(heap_.begin()).value();
    nodes_.erase(it.getId());
    return it;
}

void MapSetOpen::clear() {
    heap_.clear();
    nodes_.clear();
}

std::vector<Node> MapSetOpen::getAllNodes() {
    std::vector<Node> result;
    result.reserve(heap_.size());
    for (const auto& node: heap_) {
        result.push_back(*node.getNode());
    }
    return result;
}