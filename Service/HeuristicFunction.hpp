#pragma once

#include <functional>
#include <string>

std::function<float(int)> buildHeuristicFunction(const std::string& file);
