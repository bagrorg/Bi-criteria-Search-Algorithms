#include "MapSetOpen.hpp"

size_t MapSetOpen::size() const {
    return nodes_.size();
}

void MapSetOpen::add(Node n) {
    auto pos = n.getPos();

    if (nodes_.find(pos) != nodes_.end()) {
//        if (nodes_[pos].getHeuristicStats().g <= n.getHeuristicStats().g) {
//            return;
//        }
        // TODO: fix with two heuristicStats
    }

    nodes_[pos] = n;
    heap_.insert(std::move(n));
}

bool MapSetOpen::isEmpty() const {
    return size() == 0;
}

Node MapSetOpen::getBest() {
    auto it = heap_.begin();
    heap_.erase(it);

    nodes_.erase(it->getPos());
    return *it;
}