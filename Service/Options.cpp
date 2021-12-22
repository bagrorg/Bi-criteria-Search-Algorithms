#include "Options.hpp"

Options optionsFromInput(const po::variables_map &vm) {
    Options opts;
    
    if (vm.count("report_path")) {
        opts.reportFile = vm["report_path"].as<std::string>();
    }

    if (vm.count("iterations")) {
        opts.iterations = vm["iterations"].as<size_t>();
    }

    if (vm.count("eps_dist")) {
        opts.epsDist = vm["eps_dist"].as<float>();
    }

    if (vm.count("eps_time")) {
        opts.epsTime = vm["eps_time"].as<float>();
    }

    if (vm.count("start_id")) {
        opts.startId = vm["start_id"].as<int>();
    }

    if (vm.count("goal_id")) {
        opts.goalId = vm["goal_id"].as<int>();
    }

    if (vm.count("graph_path")) {
        opts.graphFile = vm["graph_path"].as<std::string>();
    }

    if (vm.count("history_path")) {
        opts.historyFile = vm["history_path"].as<std::string>();
    }

    return opts;
}