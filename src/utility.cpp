#include <boost/lexical_cast.hpp>

#include "utility.h"

namespace cocl {

void lineacross(std::ostream& os, const std::string& title, const char c) {
    char prev = os.fill(c);
    os.width(80);
    if (title.empty()) os << c << std::endl;
    else os << std::string(2, c) + " " + title + " " << std::endl;
    os.fill(prev);
}

bool is_numeric(const std::string& s) {
    try {boost::lexical_cast<double>(s);}
    catch (boost::bad_lexical_cast &) {return false;}
    return true;
}

} // namespace cocl
