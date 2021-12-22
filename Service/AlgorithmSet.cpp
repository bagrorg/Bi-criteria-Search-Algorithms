#include <Containers/SimplePPFOpen.hpp>
#include "AlgorithmSet.hpp"

void build(AlgorithmSet &as) {
    as["DummyAlgorithm"] = std::make_shared<DummyAlgorithm>();
    as["PP-A*"] = std::make_shared<PPA>(
        std::make_unique<SimplePPFOpen>(),
        std::make_unique<SimplePPFOpen>(),
        [](int) { return 0.f; },
        [](int) { return 0.f; }
    );
    as["BOA*"] = std::make_shared<BOA>(
        std::make_unique<MapSetOpen>(),
        std::make_unique<MapSetOpen>(),
        [](int) { return 0.f; },
        [](int) { return 0.f; }
    );
}