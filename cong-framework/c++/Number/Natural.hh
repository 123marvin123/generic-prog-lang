#pragma once

#include <limits>

namespace cong::lang::core
{
    using Natural = unsigned long long int;
    constexpr Natural natInf = std::numeric_limits<Natural>::max();
}