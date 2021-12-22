#include "Node.hpp"

bool Node::operator==(const Node &other) const {
    return v_.position == other.v_.position;
}

bool Node::operator<(const Node &other) const {
    return std::make_pair(hsDist_, hsTime_) < std::make_pair(other.hsDist_, other.hsTime_);
}

Vertex Node::getVertex() const {
    return v_;
}

Position Node::getPos() const {
    return v_.position;
}

HeuristicStats Node::getHeuristicStatsDist() const {
    return hsDist_;
}

HeuristicStats Node::getHeuristicStatsTime() const {
    return hsTime_;
}

const Node *Node::getParent() const {
    return parent_;
}

Node::Node(Vertex v, const HeuristicStats &hsDist, const HeuristicStats &hsTime, const Node *parent)
    : v_(std::move(v)), hsDist_(hsDist), hsTime_(hsTime), parent_(parent) {}

Node Node::extend(const Edge &edge, const Graph &graph, float hDist, float hTime) const {
    return Node(
        graph.getVertex(edge.to_id),
        HeuristicStats{
            hsDist_.g + edge.dist_cost,
            hDist,
            hsDist_.g + edge.dist_cost + hDist
        },
        HeuristicStats{
            hsTime_.g + edge.time_cost,
            hTime,
            hsTime_.g + edge.time_cost + hTime
        },
        this
    );
}

bool HeuristicStats::operator<(const HeuristicStats &rhs) const {
    return std::make_pair(F, h) < std::make_pair(F, h);
}
