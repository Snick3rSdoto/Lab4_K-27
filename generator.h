#pragma once

#include <string>
#include <random>
#include <cstddef>

struct Distribution {
    double p_write0;
    double p_write1;
    double p_read0;
    double p_read1;
    double p_string;
};

// генерує один файл з послідовністю операцій
void generate_file(
    const std::string &filename,
    std::size_t operations_count,
    const Distribution &dist,
    std::mt19937 &gen
);

