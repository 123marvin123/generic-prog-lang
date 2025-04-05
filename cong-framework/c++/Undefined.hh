#pragma once

namespace cong::lang::core
{
    /**
     * type used to indicate that a type - namely the return type of a function, i.e. the type of the
     * corresponding function call expression - is not valid, i.e. that the type-producing expression
     * is illegal
     */
    // only declared, not to be defined/instantiated
    struct Invalid;

    /**
     * type used to indicate that a type - namely the return type of a function, i.e. the type of the
     * corresponding function call expression - is not defined, i.e. that the type-producing expression
     * is undefined
     */
    // only declared, not to be defined/instantiated
    struct Undefined;
};
