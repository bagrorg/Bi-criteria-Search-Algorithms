#pragma once

#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct Options {
    std::string report_file = "";
    size_t iterations = 1;
     /* something from command line query */
};

Options optionsFromInput(const po::variables_map &vm);