#pragma once

#include <Service/Node.hpp>
#include <utility>

class BOANode {
public:
    BOANode() = default;
    BOANode(int id, NodePtr node)
        : id_(id), node_(node) {}

    int getId() const;

    const NodePtr &getNode() const;

    BOANode extend(const Edge &edge, const Graph& graph, float hDist, float hTime);

    bool operator==(const BOANode& other) const;

    bool operator<(const BOANode& other) const;

private:
    int id_;
    NodePtr node_;
};
