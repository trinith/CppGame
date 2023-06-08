#pragma once

#include <string>
#include <stdexcept>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define BUILDMSG(condition) "ASSERT(" + std::string{#condition} + ") failed at " + std::string{__FILENAME__} + ":" + std::to_string(__LINE__)

#define ASSERT(condition) if (!(condition)) throw std::runtime_error(BUILDMSG(condition));
#define ASSERT_MSG(condition, msg) if (!(condition)) throw std::runtime_error(BUILDMSG(condition) + "\nMessage: " + std::string{msg});