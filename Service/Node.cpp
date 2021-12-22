#include "Node.hpp"

Node::Node(Vertex v, float g, float h, float F, Node *parent) : v_(v), parent_(parent), hs_({g, h, F}) {}

bool Node::operator==(const Node &other) const {
    return v_.x == other.v_.x && v_.y == other.v_.y;
}


bool Node::operator<(const Node &other) const {
    return hs_.F < other.hs_.F || ((hs_.F == other.hs_.F) && (hs_.h < other.hs_.h));
}

Vertex Node::getVertex() const {
    return v_;
}

std::pair<long, long> Node::getPos() const {
    return {v_.x, v_.y};
}

HeuristicStats Node::getHeuristicStats() const {
    return hs_;
}