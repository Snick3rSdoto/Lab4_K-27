#pragma once

#include <string>
#include <vector>

// запускає сценарій, повертає середній час виконання (мс)
double run_scenario(
    const std::string &scenario_name,
    int num_threads,
    const std::vector<std::string> &files,
    int repeats
);

