#pragma once

#include <mutex>
#include <string>

class Data2Fields {
private:
    int f0{0};
    int f1{0};

    mutable std::mutex m0;
    mutable std::mutex m1;

public:
    void set(int index, int value);
    int get(int index) const;
    operator std::string() const;
};

