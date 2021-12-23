#pragma once

#include <unordered_map>
#include <set>
#include <list>

#include "Service/PPF.hpp"
#include "PPFOpen.hpp"


class SimplePPFOpen : public PPFOpen {
public:
    size_t size() const override;

    void add(PPF n) override;

    bool isEmpty() const override;

    PPF getBest() override;

    void clear() override;

    bool isDominated(const PPF &pair, int goalId, bool newPair) override;

    std::vector<Node> getAddedNodes() override;

    std::vector<Node> getAllNodes() override;

private:
    std::set<PPF> set_;
    std::unordered_map<int, std::list<PPF>> pairs_;
    std::unordered_map<int, float> gTimeMin_;
    std::vector<Node> added_;

    float gMin(int id);
};


