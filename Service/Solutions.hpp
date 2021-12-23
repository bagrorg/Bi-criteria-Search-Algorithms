#pragma once

#include "Node.hpp"
#include "Options.hpp"

using Solutions = std::vector<Node>;

void writeSolutions(const Solutions& solutions, const Options& opts);
