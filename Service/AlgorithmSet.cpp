#include <Containers/SimplePPFOpen.hpp>
#include "AlgorithmSet.hpp"
#include "HeuristicFunction.hpp"

void build(AlgorithmSet &as, const Options& opts) {
    auto hTime = buildHeuristicFunction(opts.hTimeFile);
    auto hDist = buildHeuristicFunction(opts.hDistFile);

    as["DummyAlgorithm"] = std::make_shared<DummyAlgorithm>();
    as["PP-A*"] = std::make_shared<PPA>(
        std::make_unique<SimplePPFOpen>(),
        std::make_unique<SimplePPFOpen>(),
        hDist, hTime
    );
    as["BOA*"] = std::make_shared<BOA>(
        std::make_unique<MapSetOpen>(),
        std::make_unique<MapSetOpen>(),
        hDist, hTime
    );
}