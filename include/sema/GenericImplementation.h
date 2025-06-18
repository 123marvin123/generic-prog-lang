#pragma once

#include "sema/Expression.h"
#include "Decls.h"

struct GenericImplementation
{
    explicit GenericImplementation(s_ptr<Expression> expression,
                        s_ptr<Expression> time_complexity = nullptr,
                        s_ptr<Expression> space_complexity = nullptr,
                        std::string language = "")
        : expression(std::move(expression)),
          time_complexity(std::move(time_complexity)),
          space_complexity(std::move(space_complexity)),
            language(std::move(language))
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

    void set_expression(s_ptr<Expression> expression)
    {
        this->expression = std::move(expression);
    }

    void set_time_complexity(s_ptr<Expression> time_complexity)
    {
        this->time_complexity = std::move(time_complexity);
    }

    void set_space_complexity(s_ptr<Expression> space_complexity)
    {
        this->space_complexity = std::move(space_complexity);
    }

    [[nodiscard]]
    std::string_view get_language() const
    {
        return language;
    }

    void set_language(std::string lang)
    {
        this->language = std::move(lang);
    }

    [[nodiscard]]
    std::string get_native_implementation() const
    {
        return native_implementation;
    }

    void set_native_implementation(std::string native_implementation)
    {
        this->native_implementation = std::move(native_implementation);
    }

private:
        s_ptr<Expression> expression;
        s_ptr<Expression> time_complexity;
        s_ptr<Expression> space_complexity;
    std::string language;
    std::string native_implementation;
};