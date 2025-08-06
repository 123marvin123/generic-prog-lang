#pragma once

struct OpenBinding
{
    const unsigned int N;

    bool operator==(const OpenBinding& other) const {
        return N == other.N;
    }
};