#pragma once

#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct Options {
    std::string reportFile;
    size_t iterations = 1;
     /* something from command line query */
    std::string graphFile;
    int startId;
    int goalId;
    float epsDist = 0.f;
    float epsTime = 0.f;
    std::string historyFile;
    std::string hTimeFile;
    std::string hDistFile;
};

Options optionsFromInput(const po::variables_map &vm);