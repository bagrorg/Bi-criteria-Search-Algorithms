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

bool BOANode::operator==(const BOANode& other) const {
    return *node_ == *other.node_;
}

bool BOANode::operator<(const BOANode& other) const {
    return *node_ < *other.node_;
}