#pragma once

#include <string>
#include <vector>

enum class OpType {
    Read,
    Write,
    ToString
};

struct Command {
    OpType op;
    int field;
    int value;
};

// зчитуємо текстовий файл з операціями у вектор команд
std::vector<Command> load_commands(const std::string &filename);

