#include "DummyAlgorithm.hpp"

void DummyAlgorithm::runAlgorithm(const Options &opts) {
    for (int i = 0; i < opts.iterations; i++) {
        res_.push_back({{"Algorithm name", this->getName()}, 
                        {"Iteration num", std::to_string(i)}});
    }
}