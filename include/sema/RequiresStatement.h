#pragma once

#include <string>
#include "Decls.h"

class RequiresStatement
{
public:
    explicit RequiresStatement(s_ptr<Expression> expression, opt<std::string> name = std::nullopt)
        : expression(std::move(expression)), name(std::move(name))
    {
        if (!this->expression) throw std::runtime_error("Expression must not be null");
    }

    [[nodiscard]]
    const s_ptr<Expression>& get_expression() const
    {
        return expression;
    }

    [[nodiscard]]
    const opt<std::string>& get_name() const
    {
        return name;
    }

    [[nodiscard]]
    bool is_named() const
    {
        return name.has_value();
    }
private:
    s_ptr<Expression> expression;
    opt<std::string> name;
};