#pragma once

#include "Graph.hpp"

struct HeuristicStats {
    float g;
    float h;
    float F;

    bool operator<(const HeuristicStats &rhs) const;
};

class Node {
public:
    Node() = default;

    Node(Vertex v, const HeuristicStats &hsDist, const HeuristicStats &hsTime, const Node *parent = nullptr);

    bool operator==(const Node &other) const;
    bool operator<(const Node &other) const;

    Vertex getVertex() const;
    Position getPos() const;
    HeuristicStats getHeuristicStatsDist() const;
    HeuristicStats getHeuristicStatsTime() const;
    const Node *getParent() const;

    Node extend(const Edge& edge, const Graph& graph, float hDist, float hTime) const;

private:
    Vertex v_;
    HeuristicStats hsDist_{};
    HeuristicStats hsTime_{};

    const Node *parent_ = nullptr;
};