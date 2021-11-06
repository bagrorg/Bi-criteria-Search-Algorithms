#include "Options.hpp"

Options optionsFromInput(const po::variables_map &vm) {
    Options opts;
    
    if (vm.count("report_path")) {
        opts.report_file = vm["report_path"].as<std::string>();
    }

    if (vm.count("iterations")) {
        opts.iterations = vm["iterations"].as<size_t>();
    }

    return opts;
}