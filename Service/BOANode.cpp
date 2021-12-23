#include "BOANode.hpp"

int BOANode::getId() const {
    return id_;
}

const NodePtr &BOANode::getNode() const {
    return node_;
}

BOANode BOANode::extend(const Edge &edge, const Graph& graph, float hDist, float hTime) {
    return BOANode(
        edge.to_id,
        std::make_shared<Node>(Node::extend(edge, graph, hDist, hTime, node_))
    );
}

bool BOANode::operator<(const BOANode& other) const {
    return std::make_tuple(node_->getHeuristicStatsDist().F, node_->getHeuristicStatsTime().F, id_) <
           std::make_tuple(other.node_->getHeuristicStatsDist().F, other.node_->getHeuristicStatsTime().F, other.id_);
}