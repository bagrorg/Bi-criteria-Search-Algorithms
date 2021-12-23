#include "MapSetOpen.hpp"

size_t MapSetOpen::size() const {
    return nodes_.size();
}

void MapSetOpen::add(NodePtr n) {
    auto id = n->getVertex().id;

    if (nodes_.find(id) != nodes_.end()) {
       if (nodes_[id]->getHeuristicStatsDist().g <= n->getHeuristicStatsDist().g &&
            nodes_[id]->getHeuristicStatsTime().g <= n->getHeuristicStatsTime().g) {
           return;
       }
        // TODO: fix with two heuristicStats
    }

    nodes_[id] = n;
    heap_.insert(std::move(n));
}

bool MapSetOpen::isEmpty() const {
    return size() == 0;
}

NodePtr MapSetOpen::getBest() {
    auto it = heap_.begin();
    heap_.erase(it);

    nodes_.erase((*it)->getVertex().id);
    return *it;
}

void MapSetOpen::clear() {
    heap_.clear();
    nodes_.clear();
}