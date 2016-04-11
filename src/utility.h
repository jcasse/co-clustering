#ifndef COCL_UTILITY_H
#define COCL_UTILITY_H

#include <iostream>
#include <limits>

namespace cocl {

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

void lineacross(std::ostream& os, const std::string& title, const char c);
bool is_numeric(const std::string& s);
inline void stop(const std::string& msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

} // namespace cocl

#endif // COCL_UTILITY_H
