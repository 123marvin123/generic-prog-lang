#pragma once

#include "../Boolean/BooleanStatic.hh"
#include "../Number/NaturalStatic.hh"
#include "../Decls.hh"
#include "../Type.hh"

#include <utility>
#include <functional>

namespace cong::lang::core {

struct IsTuple
{
private:
  template<typename Tuple_>
  struct Dispatch
  {
    using Type = False;
  };
  template<typename... Elems>
  struct Dispatch<Tuple<Elems...>>
  {
    using Type = True;
  };
public:
  template<typename Tuple_>
  struct Call
  {
    using Type = typename Dispatch<Tuple_>::Type;
    /**
     * @brief Returns a default-constructed instance of the result type.
     *
     * This static constexpr function uses the provided tuple to deduce the associated type
     * and returns a default-initialized value of that type. The tuple is used solely for type deduction.
     *
     * @param t A tuple used for type deduction.
     * @return A default-constructed instance of Type.
     */
    static constexpr Type call(Tuple_&& t)
    {
      return {};
    }
  };
};

struct Length
{
  template <typename Tuple_>
  struct Call
  {
    using Type = NaturalStatic<
      	std::tuple_size<typename Plain::Call<Tuple_>::Type>::value
      >;

    /**
     * @brief Returns a default-constructed instance of the associated Type.
     *
     * This static method ignores its input parameter and returns an empty instance of Type.
     * The parameter is used solely for template type deduction.
     *
     * @param Tuple_ A tuple instance used for type deduction.
     * @return A default-constructed instance of Type.
     */
    static Type call(Tuple_)
    {
      return {};
    }
  };
};

struct ItemAt
{
  template <typename Tuple_, typename Offset_>
  struct Call
  {
    using Type = typename std::tuple_element<Offset_::native(),
                                             typename Plain::Call<Tuple_>::Type
                                             >::type&;

    /**
     * @brief Retrieves the tuple element at a compile-time specified offset.
     *
     * This function extracts and returns the element from the given tuple at the position
     * determined by the compile-time index provided through the Offset_ type. The index is
     * obtained via Offset_::native() and used with std::get to access the corresponding element.
     *
     * @param tuple The tuple from which the element is retrieved.
     * @param Offset_ A type that supplies a compile-time index via its native() method.
     * @return The element of the tuple at the specified offset.
     */
    static Type call(Tuple_& tuple,
                     Offset_)
    {
      return std::get<Offset_::native()>(tuple);
    }
  };
};

struct Item
{
  template <typename Tuple_>
  struct Call
  {
  private:
    using ItemAt_ = ItemAt::Call<Tuple_, Zero>;
  public:
    using Type = typename ItemAt_::Type;

    /**
     * @brief Retrieves the first element of the given tuple.
     *
     * Extracts and returns the element at index zero from the provided tuple by forwarding it to 
     * the underlying tuple item accessor.
     *
     * @param tuple The tuple from which to retrieve the first element.
     * @return Type The first element of the tuple.
     */
    static Type call(Tuple_& tuple)
    {
      return ItemAt_::call(std::forward<Tuple_>(tuple), Zero{});
    }
  };
};

namespace local
{
  template <typename Fun_,
            typename Init_,
            typename Tuple_,
            typename Length_,
            typename Offset_>
  struct FoldDispatch
  {
  private:
    using FunCall_ = typename Fun_::template Call<Init_,
                                                  typename Plain::Call<typename ItemAt::Call<Tuple_,
                                                                        Offset_>::Type>::Type>::Type;
    using Dispatch_ = FoldDispatch<Fun_,
                                   FunCall_,
                                   Tuple_,
                                   Length_,
                                   typename Succ::Call<Offset_>::Type>;
  public:
    using Type = typename Dispatch_::Type;

    /**
     * @brief Executes a fold step on a tuple.
     *
     * Retrieves the tuple element at a predetermined offset and applies a binary function to combine
     * it with the initial accumulator value. The updated accumulator and the original tuple are then
     * passed to a dispatch mechanism to continue the fold operation.
     *
     * @param fun The binary function used to combine the accumulator with a tuple element.
     * @param init The initial accumulator value.
     * @param tuple The tuple to be folded.
     * @return Type The accumulator updated with the result of the fold step.
     */
    static Type call(Fun_ fun,
                     Init_ init,
                     Tuple_ tuple)
    {
      return Dispatch_::call(fun,
                             FunCall_::call(init,
                                            ItemAt
                                            ::Call<Tuple_, Offset_>
                                            ::call(tuple,
                                                   Offset_{})),
                             tuple);
    }
  };
  template <typename Fun_,
            typename Init_,
            typename Tuple_,
            typename Length_>
  struct FoldDispatch<Fun_, Init_, Tuple_, Length_, Length_>
  {

    using Type = Init_;

    /**
     * @brief Base case for the fold operation, returning the accumulated result.
     *
     * This overload is invoked when there are no more tuple elements to process. It ignores the provided
     * function and tuple parameters and directly returns the current accumulator.
     *
     * @param init The current accumulated value.
     * @return The accumulated value.
     */
    static Type call(Fun_,
                     Init_ init,
                     Tuple_)
    {
      return init;
    }
  };

}

struct Fold
{
  template <typename Fun_, typename Init_, typename Tuple_>
  struct Call
    : local::FoldDispatch<Fun_,
                         Init_,
                         Tuple_,
                         typename Length::Call<Tuple_>::Type,
                         Zero>
  {
  };
};

struct Fold1
{
  template <typename Fun_, typename Tuple_>
  struct Call
  {
  private:
    using Dispatch_ = typename local::FoldDispatch<Fun_,
                                                  typename Plain::Call<typename ItemAt::Call<Tuple_, Zero>::Type>::Type,
                                                  Tuple_,
                                                  typename Length::Call<Tuple_>::Type,
                                                  One>;
  public:
    using Type = typename Dispatch_::Type;
    /**
     * @brief Performs a fold over a tuple using its first element as the initial accumulator.
     *
     * This function initializes a fold operation by extracting the first element of the tuple to serve as
     * the initial accumulator and then delegates to an internal dispatch mechanism to combine this accumulator
     * with the remaining elements using the supplied binary function.
     *
     * @tparam Fun_ Type of the binary function used for folding.
     * @tparam Tuple_ Type of the tuple to be folded.
     * @param fun The binary function that combines the accumulator with an element.
     * @param tuple The tuple to fold; it must contain at least one element.
     * @return The result of the fold operation.
     *
     * @pre The tuple should not be empty.
     */
    static Type call(Fun_ fun,
                     Tuple_ tuple)
    {
      return Dispatch_::call(fun,
                             ItemAt::Call<Tuple_, NaturalStatic<0>>::call(tuple, NaturalStatic<0>{}),
                             tuple);
    }
  };
};

struct Transform
{
private:
  template <typename Fun_,
            typename Tuple_>
  struct Dispatch;

  template <typename Fun_,
           typename... ItemS_>
  struct Dispatch<Fun_, Tuple<ItemS_...>>
  {
  private:
    using PlainFun_ = typename ::cong::lang::core::Plain::Call<Fun_>::Type;
  public:
    using Type = Tuple<typename PlainFun_::template Call<ItemS_>::Type...>;

  private:
    /**
     * @brief Applies a callable to each provided argument and aggregates the results into a tuple.
     *
     * This function forwards the given callable to each item in the parameter pack and constructs a new tuple
     * containing the outcome of each function call. The use of perfect forwarding preserves the original value categories
     * of both the function and the arguments.
     *
     * @param fun The callable to be applied to each item.
     * @param itemS The items to which the callable is applied.
     * @return Type A tuple constructed from the results of applying the callable to each item.
     */
    static constexpr Type call_(Fun_&& fun,
                                ItemS_... itemS)
    {
      return tuple(std::forward<Fun_>(fun)(itemS)...);
    }
  public:
    /**
     * @brief Applies a transformation function to the unpacked elements of a tuple.
     *
     * Unpacks the elements of the provided tuple using std::apply and forwards them,
     * along with the given transformation function, to an internal call operator. This
     * results in a transformed value (typically a new tuple) of type Type.
     *
     * @param fun The transformation function to apply to each tuple element.
     * @param tuple The tuple containing the elements to transform.
     * @return Type The transformed result produced by applying the function to the tuple elements.
     */
    static constexpr Type call(Fun_&& fun,
                               Tuple<ItemS_...> tuple)
    {
      return std::apply([&fun](ItemS_&... itemS)
                        {
                          return call_(std::forward<Fun_>(fun),
                                       itemS...);
                        },
                        tuple);
    }
  };
public:
  template <typename Fun_,
            typename Tuple_>
  struct Call
    : Dispatch<Fun_,
               Tuple_>
    {
    };
};

};
