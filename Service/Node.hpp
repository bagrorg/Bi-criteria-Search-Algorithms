#pragma once

#include "Graph.hpp"

struct HeuristicStats {
    float g;
    float h;
    float F;
};


class Node {
public:
    Node() = default;
    Node (Vertex v, float g, float h, float F, Node *parent);
    bool operator==(const Node &other) const;
    bool operator<(const Node &other) const;

    Vertex getVertex() const;
    std::pair<long, long> getPos() const;
    HeuristicStats getHeuristicStats() const;
private:
    Vertex v_;
    HeuristicStats hs_;

    Node *parent_;
};