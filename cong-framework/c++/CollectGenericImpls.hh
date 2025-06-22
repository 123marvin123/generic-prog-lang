#pragma once

#include <limits>
#include <stdexcept>
#include <tuple>
#include <variant>
#include "Boolean/core/Boolean.hh"
#include "Seq/core/Tuple.hh"
#include "Undefined.hh"

#include <boost/core/demangle.hpp>

namespace cong::lang::intern
{
    template <typename... Ts>
    struct make_variant_from_tuple_elements
    {
        using type = std::variant<Ts...>;
    };

    template <>
    struct make_variant_from_tuple_elements<>
    {
        using type = std::variant<std::monostate>;
    };

    template <typename TTuple>
    struct tuple_to_variant_impl;

    template <typename... TArgs>
    struct tuple_to_variant_impl<std::tuple<TArgs...>>
    {
        using type = typename make_variant_from_tuple_elements<TArgs...>::type;
    };

    template <class TupleType>
    using tuple_to_variant = typename tuple_to_variant_impl<TupleType>::type;

    template <class Arg_, class Tuple_>
    struct PrependElement;

    template <class Arg_, class... Elements_>
    struct PrependElement<Arg_, core::Tuple<Elements_...>>
    {
        using Type = core::Tuple<Arg_, Elements_...>;
    };

    template <class Impl_, class Exp_, class TupleOfExp_, typename ActualExpArg, typename ActualTupleOfExpArg>
    auto get_impl_value_forwarded(ActualExpArg&& e, ActualTupleOfExpArg&& t)
    {
        using ApplyTime_ = typename Impl_::template Call<Exp_, TupleOfExp_>::ApplyTime::template Call<Exp_, TupleOfExp_>;
        const auto& result = intern::eval(ApplyTime_::call(
            std::forward<ActualExpArg>(e),
            std::forward<ActualTupleOfExpArg>(t)
        ));

        // Evaluting time resulted in a undefined result

        if constexpr (std::is_same_v<typename IsDefined::Call<decltype(result)>::Type, core::False>)
        {
            std::cerr << "Could not evaluate " << boost::core::demangle(typeid(ApplyTime_).name()) << " because result is undefined\n";
            return std::make_tuple(false, 0);
        }
        else if constexpr (std::is_same_v<typename IsValid::Call<decltype(result)>::Type, core::False>)
        {
            throw std::logic_error("Evaluating time resulted in an invalid result.");
        }
        else
        {
            return std::make_tuple(true, result.native());
        }
    }

    template <class Exp_, class TupleOfExp_, class TupleOfImpl_, typename FwdExpArg, typename FwdTupleOfExpArg, size_t
              ... Is>
    auto find_best_impl_runtime(FwdExpArg&& exp_arg, FwdTupleOfExpArg&& tuple_exp_arg, std::index_sequence<Is...>)
    {
        using VariantType = tuple_to_variant<TupleOfImpl_>;

        double best_value = std::numeric_limits<double>::max();
        size_t best_idx = static_cast<size_t>(-1);

        auto evaluate_and_update = [&](auto idx_constant)
        {
            constexpr size_t current_idx = idx_constant.value;
            using CurrentImpl = std::tuple_element_t<current_idx, TupleOfImpl_>;

            const auto& current_val = get_impl_value_forwarded<CurrentImpl, Exp_, TupleOfExp_>(
                std::forward<FwdExpArg>(exp_arg),
                std::forward<FwdTupleOfExpArg>(tuple_exp_arg)
            );

            if (std::get<0>(current_val) && std::get<1>(current_val) < best_value)
            {
                best_value = std::get<1>(current_val);
                best_idx = current_idx;
            }
        };

        (evaluate_and_update(std::integral_constant<size_t, Is>{}), ...);

        if (best_idx == static_cast<size_t>(-1) && std::tuple_size_v<TupleOfImpl_> > 0)
        {
            std::cerr << "Could not determine best dynamic algorithm" << std::endl;
            best_idx = 0;
        }

        VariantType result_variant;

        if (std::tuple_size_v<TupleOfImpl_> > 0)
        {
            if (best_idx == static_cast<size_t>(-1))
            {
                throw std::runtime_error("Ungültiger Index für die beste Implementierung nach der Suche.");
            }

            auto emplace_best = [&]<size_t ConcreteIdx>(std::integral_constant<size_t, ConcreteIdx>)
            {
                result_variant.template emplace<ConcreteIdx>();
            };

            bool dispatched = false;
            ([&]<size_t CurrentCompileIdx>(std::integral_constant<size_t, CurrentCompileIdx>)
            {
                if (dispatched) return;
                if (best_idx == CurrentCompileIdx)
                {
                    emplace_best(std::integral_constant<size_t, CurrentCompileIdx>{});
                    dispatched = true;
                }
            }(std::integral_constant<size_t, Is>{}), ...);

            if (!dispatched)
            {
                throw std::logic_error("Interner Fehler: best_idx führte zu keiner Variant-Zuweisung.");
            }
        }
        return result_variant;
    }

    template <class TupleOfImpl_, class Spec_, class Stacktrace_>
    struct SelectDynamicGenericImpl
    {
        template <class Exp_, class TupleOfExp_>
        struct Call
        {
            static auto call(Exp_ e, TupleOfExp_ t)
            {
                if (core::Length::Call<TupleOfImpl_>::Type::native() == 0)
                {
                    throw std::runtime_error(std::format("No dynamic generic implementation available; {}", Stacktrace_::str().data));
                }

                const auto res = find_best_impl_runtime<Exp_, TupleOfExp_, TupleOfImpl_>(
                    std::forward<Exp_>(e),
                    std::forward<TupleOfExp_>(t),
                    std::make_index_sequence<std::tuple_size_v<TupleOfImpl_>>{}
                );

                return std::visit([&e, &t](const auto& actual_impl_value)
                {
                    using ActualImpl = std::decay_t<decltype(actual_impl_value)>;
                    if constexpr (std::is_same_v<typename IsDefined::Call<ActualImpl>::Type, core::False>)
                    {
                        throw std::runtime_error(std::format("No dynamic generic implementation available; {}", Stacktrace_::str().data));
                    }
                    else
                    {
                        return ActualImpl::template Call<Exp_, TupleOfExp_>::call(
                            std::forward<Exp_>(e),
                            std::forward<TupleOfExp_>(t)
                        );
                    }
                }, res);
            }

            using Type = std::invoke_result_t<decltype(call), Exp_, TupleOfExp_>;
        };
    };

    // Neither static nor dynamic implementations are available for
    // given arguments; we return Undefined to state that result is
    // not defined.
    template <class Spec_, class Stacktrace_>
    struct SelectDynamicGenericImpl<core::Tuple<>, Spec_, Stacktrace_>
    {
        template <class Exp_, class TupleOfExp_>
        struct Call
        {
            static constexpr auto call(...)
            {
                return typename WrapUndefined::Call<
                    core::concat<"No static or dynamic algorithms are available for ", Spec_::name>(), Stacktrace_>::Type{};
            }

            using Type = std::invoke_result_t<decltype(call), TupleOfExp_>;
        };
    };

    template <class TupleOfImpl_, class Exp_, class TupleOfExp_>
    struct SelectBestStaticGenericImpl
    {
    private:
        template <class ImplA_, class ImplB_>
        struct CompareImpls
        {
        private:
            using ATime_ = typename ImplA_::template Call<Exp_, TupleOfExp_>::ApplyTime::template Call<
                Exp_, TupleOfExp_>::Type;
            using BTime_ = typename ImplB_::template Call<Exp_, TupleOfExp_>::ApplyTime::template Call<
                Exp_, TupleOfExp_>::Type;

            static_assert(
                core::Truthy::Call<typename core::IsStatic<typename ImplA_::template Call<
                    Exp_, TupleOfExp_>::Type>::Type>::call(), "Impl_ must return a static result");
            static_assert(core::Truthy::Call<typename core::IsStatic<ATime_>::Type>::call(),
                          "Impl_ must return a static time complexity");

            static_assert(
                core::Truthy::Call<typename core::IsStatic<typename ImplB_::template Call<
                    Exp_, TupleOfExp_>::Type>::Type>::call(), "Other_ must return a static result");
            static_assert(core::Truthy::Call<typename core::IsStatic<BTime_>::Type>::call(),
                          "Other_ must return a static time complexity");

        public:
            using Type = std::conditional_t<
                ATime_::native() <= BTime_::native(),
                ImplA_,
                ImplB_>;
        };

        template <class TupleOfImpl__>
        struct Dispatch;

        template <class ImplA_, class ImplB_, class... Remaining>
        struct Dispatch<core::Tuple<ImplA_, ImplB_, Remaining...>>
        {
            using Type = typename CompareImpls<ImplA_, typename Dispatch<core::Tuple<ImplB_, Remaining...>>::Type>::Type
            ;
        };

        template <class ImplA_>
        struct Dispatch<core::Tuple<ImplA_>>
        {
            using Type = ImplA_;
        };

        template <>
        struct Dispatch<core::Tuple<>>
        {
            using Type = core::Undefined<"No static generic implementation available">;
        };

    public:
        using Type = typename Dispatch<TupleOfImpl_>::Type;
    };

    template <class Spec_, class Exp_, class TupleOfExp_>
    struct FindStaticGenericImpl
    {
    private:
        template <class CurrentTuple_, class RemainingTuple_>
        struct Dispatch;

        template <class CurrentTuple_, class Impl_, class... Impls_>
        struct Dispatch<CurrentTuple_, core::Tuple<Impl_, Impls_...>>
        {
        private:
            using NextTuple_ = std::conditional_t<
                core::Truthy::Call<typename core::IsStatic<typename Impl_::template Call<
                    Exp_, TupleOfExp_>::Type>::Type>::call(),
                typename PrependElement<Impl_, CurrentTuple_>::Type,
                CurrentTuple_
            >;

        public:
            using Type = typename Dispatch<NextTuple_, core::Tuple<Impls_...>>::Type;
        };

        template <class CurrentTuple_>
        struct Dispatch<CurrentTuple_, core::Tuple<>>
        {
            using Type = CurrentTuple_;
        };

        using ResultingTuple_ = typename Dispatch<core::Tuple<>, typename Spec_::GenericImpls>::Type;

    public:
        using Type = std::conditional_t<
            0 < std::tuple_size_v<ResultingTuple_>,
            typename SelectBestStaticGenericImpl<ResultingTuple_, Exp_, TupleOfExp_>::Type,
            core::Undefined<"No static generic implementation available">
        >;
    };

    template <class Spec_, class Exp_, class TupleOfExp_>
    struct CollectDynamicGenericImpls
    {
    private:
        template <class Tuple_>
        struct PopElement;

        template <class Item_, class... Other_>
        struct PopElement<core::Tuple<Item_, Other_...>>
        {
            using Type = core::Tuple<Other_...>;
        };

        template <class TupleRemainingImpls_, class TupleDynamicImpls_ = core::Tuple<>>
        struct Dispatch
        {
        private:
            using Impl_ = typename std::tuple_element<0, TupleRemainingImpls_>::type;
            using Remaining_ = std::conditional_t<
                core::Falsy::Call<typename core::IsStatic<typename Impl_::template Call<
                    Exp_, TupleOfExp_>::Type>::Type>::call(),
                typename PrependElement<Impl_, TupleDynamicImpls_>::Type,
                TupleDynamicImpls_
            >;

        public:
            using Type = typename Dispatch<typename PopElement<TupleRemainingImpls_>::Type, Remaining_>::Type;
        };

        template <class TupleDynamicImpls_>
        struct Dispatch<core::Tuple<>, TupleDynamicImpls_>
        {
            using Type = TupleDynamicImpls_;
        };

    public:
        using Type = typename Dispatch<typename Spec_::GenericImpls>::Type;
    };
}
