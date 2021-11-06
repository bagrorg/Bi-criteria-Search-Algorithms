#pragma once

#include "Algorithm/Algorithm.hpp"
#include "Algorithm/DummyAlgorithm.hpp"
#include <string>
#include <memory>

using AlgorithmSet = std::map<std::string, std::shared_ptr<Algorithm>>;

void build(AlgorithmSet &as);