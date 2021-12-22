#pragma once

#include <Service/Node.hpp>
#include <utility>

class PPF {
public:
    PPF(int id, Node tlNode, Node brNode) : id_(id), tlNode_(std::move(tlNode)), brNode_(std::move(brNode)) {}

    int getId() const;

    const Node &getTlNode() const;

    const Node &getBrNode() const;

    PPF extend(const Edge &edge, const Graph& graph, float hDist, float hTime);

    static PPF merge(const PPF& a, const PPF& b);

    bool isBounded(float epsDist, float epsTime) const;

    bool operator==(const PPF& other) const;

    bool operator<(const PPF& other) const;

private:
    int id_;
    Node tlNode_;
    Node brNode_;
};
