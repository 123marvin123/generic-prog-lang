//
// Created by Marvin Haschker on 09.03.25.
//

#ifndef DECLS_H
#define DECLS_H

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
struct Expression;

enum class Operator
{
    ADD,
    MUL,
    DIV,
    SUB,
    MOD
};

#endif //DECLS_H
