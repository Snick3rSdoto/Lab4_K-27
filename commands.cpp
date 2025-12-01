#include "commands.h"

#include <fstream>
#include <iostream>

std::vector<Command> load_commands(const std::string &filename) {
    std::ifstream in(filename);
    std::vector<Command> cmds;

    if (!in) {
        std::cerr << "Cannot open file " << filename << " for reading\n";
        return cmds;
    }

    std::string op;
    while (in >> op) {
        if (op == "write") {
            int field, value;
            in >> field >> value;
            cmds.push_back(Command{OpType::Write, field, value});
        } else if (op == "read") {
            int field;
            in >> field;
            cmds.push_back(Command{OpType::Read, field, 0});
        } else if (op == "string") {
            cmds.push_back(Command{OpType::ToString, -1, 0});
        }
    }

    return cmds;
}

