//
// Created by Marvin Haschker on 05.05.25.
//

#pragma once

#include "sema/Expression.h"
#include "Decls.h"

struct GenericImplementation
{
    GenericImplementation(s_ptr<Expression> expression,
                        s_ptr<Expression> time_complexity = nullptr,
                        s_ptr<Expression> space_complexity = nullptr)
        : expression(std::move(expression)),
          time_complexity(std::move(time_complexity)),
          space_complexity(std::move(space_complexity))
    {
    }

    [[nodiscard]]
    s_ptr<Expression> get_expression() const
    {
        return expression;
    }

    [[nodiscard]]
    s_ptr<Expression> get_time_complexity() const
    {
        return time_complexity;
    }

    [[nodiscard]]
    s_ptr<Expression> get_space_complexity() const
    {
        return space_complexity;
    }

    void set_time_complexity(s_ptr<Expression> time_complexity)
    {
        this->time_complexity = std::move(time_complexity);
    }

    void set_space_complexity(s_ptr<Expression> space_complexity)
    {
        this->space_complexity = std::move(space_complexity);
    }

private:
        s_ptr<Expression> expression;
        s_ptr<Expression> time_complexity;
        s_ptr<Expression> space_complexity;
};