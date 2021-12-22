#include "AlgorithmState.hpp"
#include <fstream>

void writeHistory(const AlgorithmStateHistory& history, const Options& opts) {
    std::ofstream of(opts.historyFile, std::ios::out);

    int epoch = 0;
    for (const auto& state: history) {
        of << "e " << epoch << "\n";
        for (const auto& node: state.openNodes) {
            of << "p";
            const Node* curNode = &node;
            while (curNode) {
                auto pos = curNode->getPos();
                of << " " << pos.first << " " << pos.second;
                curNode = curNode->getParent();
            }
        }
        of << "\n";
        for (const auto& node : state.solutions) {
            of << "s";
            const Node* curNode = &node;
            while (curNode) {
                auto pos = curNode->getPos();
                of << " " << pos.first << " " << pos.second;
                curNode = curNode->getParent();
            }
        }
        of << "\n";
    }
}
