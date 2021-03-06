#include "SimplePPFOpen.hpp"

#include <limits>
#include <algorithm>

void SimplePPFOpen::clear() {
    pairs_.clear();
    set_.clear();
    gTimeMin_.clear();
}

bool SimplePPFOpen::isDominated(const PPF &pair, int goalId, bool newPair) {
    bool dominatedBySolution = pair.getId() != goalId && (1.f + epsTime_) * pair.getBrNode()->getHeuristicStatsTime().F >= gMin(goalId);
    bool dominatedByPPF = newPair && pair.getBrNode()->getHeuristicStatsTime().g >= gMin(pair.getId());
    return dominatedBySolution || dominatedByPPF;
}

size_t SimplePPFOpen::size() const {
    return set_.size();
}

void SimplePPFOpen::add(PPF n) {
    auto& pairs = pairs_[n.getId()];
    for (auto iter = pairs.begin(); iter != pairs.end(); ++iter) {
        PPF newPair = PPF::merge(*iter, n);
        if (newPair.isBounded(epsDist_, epsTime_)) {
            set_.erase(*iter);
            pairs.erase(iter);
            set_.insert(newPair);
            pairs.push_back(newPair);
            added_.push_back(*newPair.getTlNode());
            return;
        }
    }
    set_.insert(n);
    pairs.push_back(n);
    added_.push_back(*n.getTlNode());
}

bool SimplePPFOpen::isEmpty() const {
    return set_.empty();
}

PPF SimplePPFOpen::getBest() {
    PPF best = set_.extract(set_.begin()).value();
    auto& pairs = pairs_[best.getId()];
    pairs.erase(std::find(pairs.begin(), pairs.end(), best));
    gTimeMin_[best.getId()] = std::min(gMin(best.getId()), best.getBrNode()->getHeuristicStatsTime().g);
    return best;
}

float SimplePPFOpen::gMin(int id) {
    return gTimeMin_.find(id) == gTimeMin_.end() ? std::numeric_limits<float>::infinity() : gTimeMin_[id];
}

std::vector<Node> SimplePPFOpen::getAddedNodes() {
    auto res = added_;
    added_.clear();
    return res;
}

std::vector<Node> SimplePPFOpen::getAllNodes() {
    std::vector<Node> res;
    res.reserve(set_.size());
    for (const auto& pair : set_) {
        res.push_back(*pair.getTlNode());
    }
    return res;
}
