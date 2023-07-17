#include "StringUtil.h"
#include "iw4/iw_string.h"
#include <cstdarg>
#include <iterator>

std::vector<std::string> StringSplit(const std::string& string, const char delimeter) {
    std::vector<std::string> elems;
    StringSplit(string, delimeter, std::back_inserter(elems));
    return elems;
}
