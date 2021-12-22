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

PPF PPF::extend(const Edge &edge, const Graph& graph, float hDist, float hTime) {
    return PPF(
        edge.to_id,
        tlNode_.extend(edge, graph, hDist, hTime),
        brNode_.extend(edge, graph, hDist, hTime)
    );
}
