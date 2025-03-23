#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

struct already_finalized_exception final : std::exception
{
    [[nodiscard]] const char* what() const noexcept override
    {
        return "Concept is already finalized";
    }
};

struct invalid_concept_base final : std::exception
{
    [[nodiscard]] const char* what() const noexcept override
    {
        return "Invalid concept base";
    }
};

struct concept_not_found final : std::exception
{
    [[nodiscard]] const char* what() const noexcept override
    {
        return "Concept not found";
    }
};

struct namespace_not_found final : std::exception
{
    [[nodiscard]] const char* what() const noexcept override
    {
        return "Namespace not found";
    }
};

struct function_not_found final : std::exception
{
    [[nodiscard]] const char* what() const noexcept override
    {
        return "Function not found";
    }
};

#endif //EXCEPTION_H
