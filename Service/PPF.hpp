#pragma once

#include <Service/Node.hpp>
#include <utility>
#include "Containers/Open.hpp"
#include "Containers/Closed.hpp"

class PPF {
public:
    PPF(int id, Node tlNode, Node brNode) : id_(id), tlNode_(std::move(tlNode)), brNode_(std::move(brNode)) {}

    int getId() const;

    const Node &getTlNode() const;

    const Node &getBrNode() const;

    PPF extend(const Edge &edge, const Graph& graph, float hDist, float hTime);

private:
    int id_;
    Node tlNode_;
    Node brNode_;
};
