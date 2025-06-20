#pragma once

#include <string>
#include "Decls.h"
#include "SemaError.h"

struct RequiresStatement
{
    explicit RequiresStatement(s_ptr<Expression> expression,
        opt<std::string> name = std::nullopt,
          opt<std::string> desc = std::nullopt)
        : expression(std::move(expression)), name(std::move(name)), desc(std::move(desc))
    {
        if (!this->expression) throw SemaError("Expression must not be null");
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
    const opt<std::string>& get_desc() const
    {
        return desc;
    }

    [[nodiscard]]
    bool is_named() const
    {
        return name.has_value();
    }

    [[nodiscard]]
    bool has_desc() const
    {
        return desc.has_value();
    }

private:
    s_ptr<Expression> expression;
    opt<std::string> name;
    opt<std::string> desc;
};