#include "MapSetOpen.hpp"

size_t MapSetOpen::size() const {
    return nodes_.size();
}

void MapSetOpen::addNode(Node n) {
    auto pos = n.getPos();

    if (nodes_.find(pos) != nodes_.end()) {
        if (nodes_[pos].getHeuristicStats().g <= n.getHeuristicStats().g) {
            return;
        }
    }

    nodes_[pos] = n;
    heap_.insert(n);
}

bool MapSetOpen::empty() const {
    return size() == 0;
}

Node MapSetOpen::getBestNode() {
    auto it = heap_.begin();
    heap_.erase(it);

    nodes_.erase(it->getPos());
    return *it;
}