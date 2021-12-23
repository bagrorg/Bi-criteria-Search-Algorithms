#include "Solutions.hpp"

#include <fstream>

void writeSolutions(const Solutions& solutions, const Options& opts) {
    std::ofstream of(opts.solutionFile, std::ios_base::out);

    for (const auto& node: solutions) {
        of << "s " << node.getHeuristicStatsDist().g << " " << node.getHeuristicStatsTime().g << "\n";
        of << "p";
        const Node* curNode = &node;
        while (curNode) {
            of << " " << curNode->getVertex().id;
            curNode = curNode->getParent().get();
        }
        of << "\n";
    }
}
