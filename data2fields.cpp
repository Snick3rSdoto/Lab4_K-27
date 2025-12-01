#include "data2fields.h"

#include <sstream>

void Data2Fields::set(int index, int value) {
    if (index == 0) {
        std::lock_guard<std::mutex> lock(m0);
        f0 = value;
    } else if (index == 1) {
        std::lock_guard<std::mutex> lock(m1);
        f1 = value;
    }
}

int Data2Fields::get(int index) const {
    if (index == 0) {
        std::lock_guard<std::mutex> lock(m0);
        return f0;
    } else if (index == 1) {
        std::lock_guard<std::mutex> lock(m1);
        return f1;
    }
    return 0;
}

Data2Fields::operator std::string() const {
    std::scoped_lock lock(m0, m1);
    std::ostringstream oss;
    oss << f0 << " " << f1;
    return oss.str();
}

