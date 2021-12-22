#include "MapClosed.hpp"

size_t MapClosed::size() const {
    return nodes_.size();
}

void MapClosed::add(Node n) {
    nodes_[n.getPos()] = n;
}

bool MapClosed::wasExpanded(const Node& n) const {
    return (nodes_.find(n.getPos()) != nodes_.end());
}