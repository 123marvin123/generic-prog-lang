#pragma once

#include <limits>

namespace cong::lang::core
{
    using Integer = long long int;
    constexpr Integer intInf = std::numeric_limits<Integer>::max();
}
