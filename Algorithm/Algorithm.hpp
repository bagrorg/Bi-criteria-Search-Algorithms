#pragma once

#include "Service/Measurements.hpp"
#include "Service/Options.hpp"

class Algorithm {
public:
    Algorithm(const std::string &name) : name_(name) {};
    
    virtual void runAlgorithm(const Options &opts) = 0;

    void writeReport(const Options &opts) {
        if (opts.report_file.compare("") == 0) {
            writeCout(res_, opts);
        } else {
            writeCsv(res_, opts);
        }
    }

    std::string getName() {
        return name_;
    }

protected:
    std::string name_;
    Measurements res_;
};
