#include <boost/program_options.hpp>
#include "Service/Options.hpp"
#include "Service/Measurements.hpp"
#include "Service/AlgorithmSet.hpp"
#include <iostream>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char** argv) {
    AlgorithmSet as;
    build(as);

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("algo", po::value<std::string>(), "algorithm name")
        ("report_path", po::value<std::string>(), "report file path")
        ("source_path", po::value<std::string>(), "path to benchmark file")
        ("iterations", po::value<size_t>(), "count of iterations")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("algo")) {
        auto a = as[vm["algo"].as<std::string>()];
        Options opts = optionsFromInput(vm);

        a->runAlgorithm(opts);
        a->writeReport(opts);
    }
}