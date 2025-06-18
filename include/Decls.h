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

struct Object;
struct Map;

struct Expression;

struct GenericImplementation;

enum class Operator
{
    ADD,
    MUL,
    DIV,
    SUB,
    MOD,
    POW
};
