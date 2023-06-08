#include "Path.h"

#include <filesystem>

/* static */
std::string Path::Combine(std::string_view lhs, std::string_view rhs)
{
    std::filesystem::path path = std::filesystem::path{ lhs } / std::filesystem::path{ rhs };
    return path.string();
}