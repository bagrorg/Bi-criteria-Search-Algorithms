#pragma once

#include <Service/Node.hpp>
#include <utility>

class PPF {
public:
    PPF(int id, std::shared_ptr<Node> tlNode, std::shared_ptr<Node> brNode)
        : id_(id), tlNode_(std::move(tlNode)), brNode_(std::move(brNode)) {}

    int getId() const;

    const std::shared_ptr<Node> &getTlNode() const;

    const std::shared_ptr<Node> &getBrNode() const;

    PPF extend(const Edge &edge, const Graph& graph, float hDist, float hTime);

    static PPF merge(const PPF& a, const PPF& b);

    bool isBounded(float epsDist, float epsTime) const;

    bool operator==(const PPF& other) const;

    bool operator<(const PPF& other) const;

private:
    int id_;
    std::shared_ptr<Node> tlNode_;
    std::shared_ptr<Node> brNode_;
};
