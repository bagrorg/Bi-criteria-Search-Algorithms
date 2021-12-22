#include "AlgorithmSet.hpp"

void build(AlgorithmSet &as) {
    as["DummyAlgorithm"] = std::make_shared<DummyAlgorithm>();
    as["PP-A*"] = std::make_shared<PPA>(
        nullptr, nullptr,
        [](int) { return 0.f; },
        [](int) { return 0.f; }
    );
}