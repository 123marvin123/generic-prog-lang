#pragma once

#include <vector>
#include <set>
#include <memory>
#include <optional>

template <class T>
using s_ptr = std::shared_ptr<T>;

template <class T>
using u_ptr = std::unique_ptr<T>;

template <class T>
using vec = std::vector<T>;

template<class T>
using opt = std::optional<T>;

struct Concept;
struct Namespace;
struct FunctionParameter;
struct PlaceholderFunctionParameter;
struct ConcreteFunctionParameter;
struct Function;
struct Sema;
struct RequiresStatement;

struct Object;
struct Map;

struct Expression;

struct GenericImplementation;

// Structure to represent a let binding for scope checking
struct LetBinding {
    std::string identifier;
    s_ptr<Expression> value;

    LetBinding(std::string id, s_ptr<Expression> val)
        : identifier(std::move(id)), value(std::move(val)) {}
};

enum class Operator
{
    ADD,
    MUL,
    DIV,
    SUB,
    MOD,
    POW
};
