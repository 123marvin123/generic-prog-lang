
#ifndef SEMA_H
#define SEMA_H

#include "Function.h"
#include "sema/Concept.h"
#include "sema/Namespace.h"

struct Sema final : DefaultNamespace
{
    explicit Sema(const bool create_builtin = true) : DefaultNamespace(this)
    {
        if (!create_builtin) return;

        register_builtin_concepts();
        register_builtin_functions();
        register_builtin_operators();
    }

    [[nodiscard]]
    static
    opt<Concept*> create_concept(
        Namespace* ns,
        const std::string& name,
        opt<std::set<const Concept*>> bases = std::nullopt);

    [[nodiscard]]
    static
    opt<Namespace*> create_namespace(const std::string& name,
                                    Sema* sema,
                                    Namespace* parent);

    template <class T, class... Args> requires std::is_base_of_v<Function, T>
    [[nodiscard]] static
    opt<T*> create_function(Namespace* ns, Args&... args)
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

private:
    void register_builtin_concepts();
    void register_builtin_functions();
    void register_builtin_operators();

    const Concept* object_concept;
    const Concept* string_concept;
    const Concept* boolean_concept;
    const Concept* real_concept;
    const Concept* number_concept;
};

#endif // SEMA_H
