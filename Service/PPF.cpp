#include <tuple>
#include "PPF.hpp"

int PPF::getId() const {
    return id_;
}

const Node &PPF::getTlNode() const {
    return tlNode_;
}

const Node &PPF::getBrNode() const {
    return brNode_;
}

PPF PPF::extend(const Edge &edge, const Graph &graph, float hDist, float hTime) {
    return PPF(
        edge.to_id,
        tlNode_.extend(edge, graph, hDist, hTime),
        brNode_.extend(edge, graph, hDist, hTime)
    );
}

PPF PPF::merge(const PPF &a, const PPF &b) {
    Node newTlNode = a.tlNode_.getHeuristicStatsDist().g < b.tlNode_.getHeuristicStatsDist().g ? a.tlNode_ : b.tlNode_;
    Node newBrNode = a.brNode_.getHeuristicStatsTime().g < b.brNode_.getHeuristicStatsTime().g ? a.brNode_ : b.brNode_;
    return PPF(a.id_, newTlNode, newBrNode);
}

bool PPF::isBounded(float epsDist, float epsTime) const {
    bool distBounded = epsDist * tlNode_.getHeuristicStatsDist().g >=
                       brNode_.getHeuristicStatsDist().g - tlNode_.getHeuristicStatsDist().g;
    bool timeBounded = epsTime * brNode_.getHeuristicStatsTime().g >=
                       tlNode_.getHeuristicStatsTime().g - brNode_.getHeuristicStatsTime().g;
    return distBounded && timeBounded;
}

bool PPF::operator<(const PPF &other) const {
    return std::make_tuple(tlNode_.getHeuristicStatsDist().F, brNode_.getHeuristicStatsTime().F, id_) <
           std::make_tuple(other.tlNode_.getHeuristicStatsDist().F, other.brNode_.getHeuristicStatsTime().F, other.id_);
}

bool PPF::operator==(const PPF &other) const {
    return std::make_tuple(tlNode_.getHeuristicStatsDist().F, brNode_.getHeuristicStatsTime().F, id_) ==
           std::make_tuple(other.tlNode_.getHeuristicStatsDist().F, other.brNode_.getHeuristicStatsTime().F, other.id_);
}
