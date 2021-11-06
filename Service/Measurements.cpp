#include "Measurements.hpp"
#include <fstream>
#include <sstream>

void writeCsv(const Measurements &results, const Options &opts) {
    bool exists = std::ifstream(opts.report_file).good();
    std::ofstream of(opts.report_file, std::ios::app);

    std::stringstream line;
    if (!exists) {
        for (auto kv: results[0]) {
            line << kv.first << ",";
        }
        of << line.str().substr(0, line.str().size() - 1) << "\n";
    }

    for (int i = 0; i < results.size(); i++) {
        auto reses = results[i];
        line.str("");
        for (auto kv: reses) {
            line << kv.second << ",";
        }
        of << line.str().substr(0, line.str().size() - 1) << "\n";
    }
}

void writeCout(const Measurements &results, const Options &opts) {
    for (int i = 0; i < results.size(); i++) {
        auto reses = results[i];
        std::cout << "Result number " << i << ":" << std::endl;
 
        for (auto kv: reses) {
            std::cout << "\t" << kv.first << " -- " << kv.second << std::endl;
        }
        std::cout << std::endl;
    }
}

