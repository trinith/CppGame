#pragma once

#include <string>

class Path
{
public:
    static std::string Combine(std::string_view lhs, std::string_view rhs);
};