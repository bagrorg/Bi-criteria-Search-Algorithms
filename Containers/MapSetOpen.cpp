#include "MapSetOpen.hpp"
#include <iostream>

size_t MapSetOpen::size() const {
    return heap_.size();
}

void MapSetOpen::add(BOANode n) {
    heap_.insert(n);
    added_.push_back(*n.getNode());
}

bool MapSetOpen::isEmpty() const {
    return size() == 0;
}

BOANode MapSetOpen::getBest() {
    auto it = heap_.extract(heap_.begin()).value();
    return it;
}

void MapSetOpen::clear() {
    heap_.clear();
}

std::vector<Node> MapSetOpen::getAddedNodes() {
    auto res = added_;
    added_.clear();
    return res;
}