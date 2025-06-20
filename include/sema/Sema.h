#pragma once

#include "Function.h"
#include "Concept.h"
#include "Namespace.h"
#include "SemaError.h"

struct Sema final : DefaultNamespace
{
    explicit Sema(const bool create_builtin = true) : DefaultNamespace(this)
    {
        if (!create_builtin) return;

        register_builtin_concepts();
#ifndef __CATCH2_TEST__
        register_builtin_functions();
#endif
        register_builtin_operators();
        register_builtin_requirements();
    }

    [[nodiscard]]
    static
    opt<Concept*> create_concept(
        Namespace* ns,
        const std::string& name,
        opt<std::set<const Concept*>> bases = std::nullopt,
        bool export_ = true);

    [[nodiscard]]
    static
    opt<Namespace*> create_namespace(const std::string& name,
                                    Sema* sema,
                                    Namespace* parent);

    template <class T, class... Args> requires std::is_base_of_v<Function, T>
    [[nodiscard]] static
    opt<T*> create_function(Namespace* ns, Args&&... args)
    {
        auto fn = std::make_unique<T>(std::forward<Args>(args)...);
        auto* ptr = fn.get();
        if (!ns->register_function(std::move(fn)))
            return std::nullopt;
        return ptr;
    }

    template <class T>
    [[nodiscard]]
    const Concept* builtin_concept() const;

    template <Operator T>
    [[nodiscard]]
    const Function* builtin_function() const;

private:
    void register_builtin_concepts();
    void register_builtin_functions();
    void register_builtin_requirements();
    void register_builtin_operators();

    Concept* object_concept;
    Concept* string_concept;
    Concept* boolean_concept;
    Concept* map_concept;

    Concept* ordered_concept;

    Concept* number_concept;
    Concept* natural_concept;
    Concept* cardinal_concept;
    Concept* integer_concept;
    Concept* rational_concept;
    Concept* real_concept;
    Concept* complex_concept;

    Function* isModelOf_function;

    Function* add_function;
    Function* sub_function;
    Function* mod_function;
    Function* mul_function;
    Function* div_function;
    Function* succ_function;
    Function* pred_function;
    Function* pow_function;

    Function* not_function;
    Function* or_function;
    Function* xor_function;
    Function* and_function;

    Function* isLess_function;
    Function* isLessEqual_function;
    Function* isGreater_function;
    Function* isGreaterEqual_function;

    Function* isEqual_function;
    Function* isNotEqual_function;
    Function* id_function;
};
