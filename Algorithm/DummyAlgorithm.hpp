#pragma once

#include "Algorithm.hpp"

class DummyAlgorithm : public Algorithm {
public:
    DummyAlgorithm() : Algorithm("DummyAlgorithm") {};

    void runAlgorithm(const Options &opts);
};