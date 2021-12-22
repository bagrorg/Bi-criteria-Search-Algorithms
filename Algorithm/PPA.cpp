#include "PPA.hpp"

void PPA::runAlgorithm(const Options &opts) {
    const Graph graph = [&opts] () -> Graph {
        std::vector<Vertex> vs;
        parseGraph(opts.graph_file, vs);
        return vs;
    }();

    for (int i = 0; i < opts.iterations; i++) {
        runAlgorithmImpl(graph, 0, 0);
    }
}

void PPA::runAlgorithmImpl(const Graph &graph, int idStart, int idGoal) {

}
