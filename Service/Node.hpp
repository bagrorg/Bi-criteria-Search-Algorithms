#pragma once

#include "Graph.hpp"

struct HeuristicStats {
    float g;
    float h;
    float F;
};

using Position = std::pair<long, long>;

class Node {
public:
    Node() = default;
    Node (Vertex v, float g, float h, float F, Node *parent = nullptr);
    bool operator==(const Node &other) const;
    bool operator<(const Node &other) const;

    Vertex getVertex() const;
    Position getPos() const;
    HeuristicStats getHeuristicStats() const;
    Node *getParent() const;
private:
    Vertex v_;
    HeuristicStats hs_{};

    Node *parent_ = nullptr;
};