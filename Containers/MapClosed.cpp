#include "MapClosed.hpp"

size_t MapClosed::size() const {
    return nodes_.size();
}

void MapClosed::add(NodePtr n) {
    nodes_[n->getVertex().id] = n;
}

bool MapClosed::wasExpanded(const NodePtr& n) const {
    return (nodes_.find(n->getVertex().id) != nodes_.end());
}