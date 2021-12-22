#pragma once

#include <memory>
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

    Node(Vertex v, const HeuristicStats &hsDist, const HeuristicStats &hsTime, std::shared_ptr<Node> parent = nullptr);

    bool operator==(const Node &other) const;
    bool operator<(const Node &other) const;

    Vertex getVertex() const;
    Position getPos() const;
    HeuristicStats getHeuristicStatsDist() const;
    HeuristicStats getHeuristicStatsTime() const;
    std::shared_ptr<Node> getParent() const;

    static Node extend(const Edge& edge, const Graph& graph, float hDist, float hTime, const std::shared_ptr<Node>& parent);

private:
    Vertex v_;
    HeuristicStats hsDist_{};
    HeuristicStats hsTime_{};

    std::shared_ptr<Node> parent_ = nullptr;
};

using NodePtr = std::shared_ptr<Node>;