#pragma once
#ifndef CONG_NUMBER_LANG_CORE_NATURAL_HH
#define CONG_NUMBER_LANG_CORE_NATURAL_HH

#include <limits>

namespace cong::lang::core
{
    using Natural = unsigned long long int;
    constexpr Natural natInf = std::numeric_limits<Natural>::max();
}

#endif
