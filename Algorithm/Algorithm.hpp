#pragma once

#include "Service/Measurements.hpp"
#include "Service/Options.hpp"
#include "Service/AlgorithmState.hpp"

class Algorithm {
public:
    Algorithm(const std::string &name) : name_(name) {};
    
    virtual void runAlgorithm(const Options &opts) = 0;

    void writeReport(const Options &opts) {
        if (opts.reportFile.empty()) {
            writeCout(res_, opts);
        } else {
            writeCsv(res_, opts);
        }
        if (!opts.historyFile.empty()) {
            writeHistory(history_, opts);
        }
    }

    std::string getName() {
        return name_;
    }

protected:
    std::string name_;
    Measurements res_;
    AlgorithmStateHistory history_;
};
