#include "generator.h"

#include <fstream>
#include <iostream>

void generate_file(
    const std::string &filename,
    std::size_t operations_count,
    const Distribution &dist,
    std::mt19937 &gen
) {
    std::uniform_real_distribution<double> unif(0.0, 1.0);

    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Cannot open file " << filename << " for writing\n";
        return;
    }

    for (std::size_t i = 0; i < operations_count; ++i) {
        double r = unif(gen);

        if (r < dist.p_write0) {
            out << "write 0 1\n";
        } else if (r < dist.p_write0 + dist.p_write1) {
            out << "write 1 1\n";
        } else if (r < dist.p_write0 + dist.p_write1 + dist.p_read0) {
            out << "read 0\n";
        } else if (r < dist.p_write0 + dist.p_write1 + dist.p_read0 + dist.p_read1) {
            out << "read 1\n";
        } else {
            out << "string\n";
        }
    }
}

