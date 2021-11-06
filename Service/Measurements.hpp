#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "Options.hpp"

using Measurements = std::vector<std::map<std::string, std::string>>;

void writeCsv(const Measurements &results, const Options &opts);
void writeCout(const Measurements &results, const Options &opts);
