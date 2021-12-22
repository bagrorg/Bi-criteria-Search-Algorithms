#include "HeuristicFunction.hpp"

#include <fstream>
#include <unordered_map>

std::function<float(int)> buildHeuristicFunction(const std::string& file) {
    if (file.empty()) {
        return [](int) {
            return 0.f;
        };
    }
    std::ifstream in(file, std::ios_base::in);

    std::unordered_map<int, float> h;

    int cur_id;
    while (in >> cur_id) {
        in >> h[cur_id];
    }

    return [h](int id) {
        return h.at(id);
    };
}

