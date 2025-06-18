#pragma once

#include "Number/core/NaturalStatic.hh"
#include "Boolean/core/BooleanStatic.hh"

#include "Type.hh"
#include "Undefined.hh"
#include "Decls.hh"

#include <climits> // *_MIN *_MAX
#include <cwchar> // WCHAR_MIN WCHAR_MAX
#include <utility> // for stdlib meta functions
#include <type_traits>

namespace cong::lang::core
{
    using namespace ::cong::lang::core;
    namespace intern
    {
        // @todo rename?
        typedef char No;

        struct Yes
        {
            char x[2];
        };


        // @todo provide here corresponding Fun that use these functions
        template <typename Type_>
        Type_ provide();

        template <typename Type_>
        False accept(...);
        template <typename Type_>
        True accept(Type_);
    }

    // C++ type traits

    // mapping type -> properties
    template <typename Type_>
    struct Traits;

    // @todo replace N<...>/True/False/Invalid with local types

    // hierarchical assignment of properties to types
    struct TypeTraits
    {
        using IsVoid = False;
        using IsBool = False;
        using IsChar = False;
        using IsWchar = False;
        using IsSignedChar = False;
        using IsUnsignedChar = False;
        using IsCharacter = False;
        using IsSignedShort = False;
        using IsUnsignedShort = False;
        using IsShort = False;
        using IsSignedInt = False;
        using IsUnsignedInt = False;
        using IsInt = False;
        using IsSignedLong = False;
        using IsUnsignedLong = False;
        using IsLong = False;
        using IsSigned = False;
        using IsUnsigned = False;
        using IsIntegral = False;
        using IsFloat = False;
        using IsDouble = False;
        using IsLongDouble = False;
        using IsReal = False;
        using IsArithmetic = False;
        using IsEnum = False;
        using IsVoidPointer = False;
        using IsObjectPointer = False;
        using IsFunctionPointer = False;
        using IsPointer = False;
        using IsMemberObjectPointer = False;
        using IsMemberFunctionPointer = False;
        using IsMemberPointer = False;
        using IsScalar = False;
        using IsBoundArray = False;
        using IsUnboundArray = False;
        using IsArray = False;
        using IsClass = False;
        using IsObjectType = False;
        using IsQualifiable = False;
        using IsFunction = False;
        using IsReferenceable = False;
        using IsPointable = False;
        using IsObjectReference = False;
        using IsFunctionReference = False;
        using IsReference = False;

        using IsQualified = False;
        using IsConst = False;
        using IsVolatile = False;
        using IsConstVolatile = False;

        using ToConst = Invalid;
        using ToVolatile = Invalid;
        using ToConstVolatile = Invalid;
        using ToNonConst = Invalid;
        using ToNonVolatile = Invalid;
        using ToNonQualified = Invalid;
        using ToReference = Invalid;
        using ToNonReference = Invalid;
        using ToPointer = Invalid;
        using ToNonPointer = Invalid;
        using ToPromoted = Invalid;
        using ToReturn = Invalid;
        using ToParamTupleOfType = Invalid;
        using ToClass = Invalid;
        using ToMember = Invalid;
        using ToElement = Invalid;
        using ToLength = Invalid;
    };

    template <typename NonReference_>
    struct ReferenceTraits
        : Traits<NonReference_>
    {
        using IsReference = True;

        using ToReference = NonReference_&;
        using ToNonReference = NonReference_;
    };

    template <typename Type_>
    struct PointableTraits
        : TypeTraits
    {
        using IsPointable = True;

        using ToNonReference = Type_;
        using ToPointer = Type_*;
    };

    template <typename Type_>
    struct VoidTraits
        : PointableTraits<Type_>
    {
        using IsQualifiable = True;
        using ToConst = void const;
        using ToVolatile = void volatile;
        using ToConstVolatile = void const volatile;

        using IsVoid = True;
    };

    template <typename Type_>
    struct ReferenceableTraits
        : PointableTraits<Type_>
    {
        using IsReferenceable = True;
        using ToReference = Type_&;
    };

    template <typename Type_, typename Return_, class ParamTupleOfType_>
    struct FunctionTraits
        : ReferenceableTraits<Type_>
    {
    private:
        using Base_ = ReferenceableTraits<Type_>;

    public:
        using IsFunction = True;
        using IsQualified = False;
        using IsConst = False;
        using IsVolatile = False;
        using IsConstVolatile = False;

        using ToConst = Type_;
        using ToVolatile = Type_;
        using ToConstVolatile = Type_;
        using ToNonConst = Type_;
        using ToNonVolatile = Type_;
        using ToNonQualified = Type_;

        using ToReturn = Return_;
        using ToParamTupleOfType = typename ParamTupleOfType_::Type;
    };

    template <typename Type_>
    struct ObjectTraits
        : ReferenceableTraits<Type_>
    {
        using IsObjectType = True;

        using IsQualifiable = True;
        using ToConst = Type_ const;
        using ToVolatile = Type_ volatile;
        using ToConstVolatile = Type_ const volatile;
    };

    template <typename Type_>
    struct ScalarTraits
        : ObjectTraits<Type_>
    {
        using IsScalar = True;
    };

    template <typename Type_>
    struct ArithmeticTraits
        : ScalarTraits<Type_>
    {
        using IsArithmetic = True;
    };

    template <typename Type_>
    struct IntegralTraits
        : ArithmeticTraits<Type_>
    {
        using IsIntegral = True;
    };

    template <typename Type_>
    struct BoolTraits
        : IntegralTraits<Type_>
    {
        using IsBool = True;

        using ToPromoted = signed int;
    };

    template <typename Type_>
    struct CharacterTraits
        : IntegralTraits<Type_>
    {
        using IsCharacter = True;
    };

    template <typename Type_>
    struct CharTraits
        : CharacterTraits<Type_>
    {
        using IsChar = True;

        typedef Cond::Call<core::BooleanStatic<(CHAR_MAX < INT_MAX)>, signed int, unsigned int>
        ::Type
        ToPromoted;
    };

    template <typename Type_>
    struct WCharTraits
        : CharacterTraits<Type_>
    {
        using IsWChar = True;

        typedef Cond::Call<core::BooleanStatic<(INT_MIN <= WCHAR_MIN && WCHAR_MAX <= INT_MAX)>,
                           signed int,
                           Cond::Call<core::BooleanStatic<(0 <= WCHAR_MIN && WCHAR_MAX <= UINT_MAX)>,
                                      unsigned int,
                                      Cond::Call<core::BooleanStatic<(LONG_MIN <= WCHAR_MIN && WCHAR_MAX <= LONG_MAX)>,
                                                 signed long,
                                                 Cond::Call<core::BooleanStatic<(0 <= WCHAR_MIN && WCHAR_MAX <=
                                                 ULONG_MAX)>,
                                                            unsigned long,
                                                            Invalid>::Type>::Type>::Type>::Type
        ToPromoted;
    };

    template <typename Type_>
    struct SignedCharTraits
        : CharacterTraits<Type_>
    {
        using IsSigned = True;
        using IsSignedChar = True;

        using ToPromoted = signed int;
    };

    template <typename Type_>
    struct UnsignedCharTraits
        : CharacterTraits<Type_>
    {
        using IsUnsigned = True;
        using IsUnsignedChar = True;

        typedef Cond::Call<core::BooleanStatic<(UCHAR_MAX <= INT_MAX)>, signed int, unsigned int>::Type
        ToPromoted;
    };

    template <typename Type_>
    struct ShortTraits
        : IntegralTraits<Type_>
    {
        using IsShort = True;
    };

    template <typename Type_>
    struct SignedShortTraits
        : ShortTraits<Type_>
    {
        using IsSigned = True;
        using IsSignedShort = True;

        using ToPromoted = signed int;
    };

    template <typename Type_>
    struct UnsignedShortTraits
        : ShortTraits<Type_>
    {
        using IsUnsigned = True;
        using IsUnsignedShort = True;

        typedef Cond::Call<core::BooleanStatic<(USHRT_MAX <= INT_MAX)>, signed int, unsigned int>::Type
        ToPromoted;
    };

    template <typename Type_>
    struct IntTraits
        : IntegralTraits<Type_>
    {
        using IsInt = True;
    };

    template <typename Type_>
    struct SignedIntTraits
        : IntTraits<Type_>
    {
        using IsSigned = True;
        using IsSignedInt = True;
        using ToPriority = NaturalStatic<0>;

        using ToPromoted = signed int;
    };

    template <typename Type_>
    struct UnsignedIntTraits
        : IntTraits<Type_>
    {
        using IsUnsigned = True;
        using IsUnsignedInt = True;
        using ToPriority = NaturalStatic<1>;

        using ToPromoted = unsigned int;
    };

    template <typename Type_>
    struct LongTraits
        : IntegralTraits<Type_>
    {
        using IsLong = True;
    };

    template <typename Type_>
    struct SignedLongTraits
        : LongTraits<Type_>
    {
        using IsSigned = True;
        using IsSignedLong = True;
        using ToPriority = NaturalStatic<((UINT_MAX <= LONG_MAX) ? 3 : 2)>;

        using ToPromoted = signed long;
    };

    template <typename Type_>
    struct UnsignedLongTraits
        : LongTraits<Type_>
    {
        using IsUnsigned = True;
        using IsUnsignedLong = True;
        using ToPriority = NaturalStatic<4>;

        using ToPromoted = unsigned long;
    };

    template <typename Type_>
    struct RealTraits
        : ArithmeticTraits<Type_>
    {
        using IsReal = True;
    };

    template <typename Type_>
    struct FloatTraits
        : RealTraits<Type_>
    {
        using IsFloat = True;

        using ToPromoted = double;
    };

    template <typename Type_>
    struct DoubleTraits
        : RealTraits<Type_>
    {
        using IsDouble = True;
        using ToPriority = NaturalStatic<5>;

        using ToPromoted = double;
    };

    template <typename Type_>
    struct LongDoubleTraits
        : RealTraits<Type_>
    {
        using IsLongDouble = True;
        using ToPriority = NaturalStatic<6>;

        using ToPromoted = long double;
    };

    template <typename Type_>
    struct EnumTraits
        : ScalarTraits<Type_>
    {
        using IsEnum = True;

    private:
        typedef typename Cond::Call
        <
            core::BooleanStatic<(sizeof(Type_) <= sizeof(signed int))>,
            typename Cond::Call<core::BooleanStatic<((Type_)-1 < (Type_)0)>,
                                signed int,
                                unsigned int>::Type,
            typename Cond::Call<core::BooleanStatic<(sizeof(Type_) <= sizeof(signed long))>,
                                typename Cond::Call<
                                    core::BooleanStatic<((Type_)-1 < (Type_)0)>, signed long, unsigned long>::Type,
                                Invalid>::Type
        >::Type ToUnderlying_;

    public:
        using ToPromoted = typename Traits<ToUnderlying_>::ToPromoted;
    };

    template <typename Type_, typename NonPointer_>
    struct PointerTraits
        : ScalarTraits<Type_>
    {
        using IsPointer = True;

        using ToNonPointer = NonPointer_;
    };

    template <typename Type_, typename NonPointer_>
    struct VoidPointerTraits
        : PointerTraits<Type_, NonPointer_>
    {
        using IsVoidPointer = True;
    };

    template <typename Type_, typename NonPointer_>
    struct ObjectPointerTraits
        : PointerTraits<Type_, NonPointer_>
    {
        using IsObjectPointer = True;
    };

    template
    <typename Type_, typename NonPointer_, typename Return_, class ParamTupleOfType_
    >
    struct FunctionPointerTraits
        : PointerTraits<Type_, NonPointer_>
    {
        using IsFunctionPointer = True;

        using ToReturn = Return_;
        using ToParamTupleOfType = typename ParamTupleOfType_::Type;
    };

    template <typename Type_, class Class_>
    struct MemberPointerTraits
        : ScalarTraits<Type_>
    {
        using IsMemberPointer = True;

        using ToClass = Class_;
    };

    template <typename Type_, typename Member_, class Class_>
    struct MemberObjectPointerTraits
        : MemberPointerTraits<Type_, Class_>
    {
        using IsMemberObjectPointer = True;

        using ToMember = Member_;
    };

    template <typename Type_, typename Return_, class Class_, class ParamTupleOfType_>
    struct MemberFunctionPointerTraits
        : MemberPointerTraits<Type_, Class_>
    {
        using IsMemberFunctionPointer = True;

        using ToReturn = Return_;
        using ToParamTupleOfType = typename ParamTupleOfType_::Type;
    };

    template <typename Type_, typename Element_>
    struct ArrayTraits
        : ObjectTraits<Type_>
    {
        using IsArray = True;

        using ToPointer = typename Traits<Element_>::ToPointer;
        using ToElement = Element_;
    };

    template <typename Type_, typename Element_, class Length_>
    struct BoundArrayTraits
        : ArrayTraits<Type_, Element_>
    {
        using IsBoundArray = True;
        using ToLength = Length_;
    };

    template <typename Type_, typename Element_>
    struct UnboundArrayTraits
        : ArrayTraits<Type_, Element_>
    {
    private:
        using Base_ = ArrayTraits<Type_, Element_>;

    public:
        using IsUnboundArray = True;
    };

    template <typename Type_>
    struct ClassTraits
        : ObjectTraits<Type_>
    {
        using IsClass = True;
    };

    template <Boolean IS_CLASS_, typename Type_>
    struct ClassOrEnumDispatch_ //<False,...>
        : EnumTraits<Type_>
    {
    };

    template <typename Type_>
    struct ClassOrEnumDispatch_<true, Type_>
        : ClassTraits<Type_>
    {
    };

    template <typename Type_, typename Plain_, typename Pointer_>
    struct UnqualifiedDispatch_
        : ClassOrEnumDispatch_
        <(sizeof(intern::accept<void (Type_::*)(void)>(0)) == sizeof(intern::Yes)),
         Type_
        >
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, void, void*>
        : VoidTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, bool, bool*>
        : BoolTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, char, char*>
        : CharTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, wchar_t, wchar_t*>
        : WCharTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, signed char, signed char*>
        : SignedCharTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, unsigned char, unsigned char*>
        : UnsignedCharTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, signed short, signed short*>
        : SignedShortTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, unsigned short, unsigned short*>
        : UnsignedShortTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, signed int, signed int*>
        : SignedIntTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, unsigned int, unsigned int*>
        : UnsignedIntTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, signed long, signed long*>
        : SignedLongTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, unsigned long, unsigned long*>
        : UnsignedLongTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, float, float*>
        : FloatTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, double, double*>
        : DoubleTraits<Type_>
    {
    };

    template <typename Type_>
    struct UnqualifiedDispatch_<Type_, long double, long double*>
        : LongDoubleTraits<Type_>
    {
    };

    template <class IsVoid_, typename Type_, typename NonPointer_>
    struct VoidOrObjectPointerDispatch_ //<True,...>
        : VoidPointerTraits<Type_, NonPointer_>
    {
    };

    template <typename Type_, typename NonPointer_>
    struct VoidOrObjectPointerDispatch_<False, Type_, NonPointer_>
        : ObjectPointerTraits<Type_, NonPointer_>
    {
        using IsObjectPointer = True;
    };

    template <typename Type_, typename NonPointer_>
    struct UnqualifiedDispatch_<Type_, NonPointer_*, NonPointer_**>
        : VoidOrObjectPointerDispatch_<typename Traits<NonPointer_>::IsVoid,
                                       Type_,
                                       NonPointer_>
    {
    };

    template
    <typename Type_, typename Return_,
     typename NonPointer_
    >
    struct UnqualifiedDispatch_<Type_, Return_ (*)(), NonPointer_**>
        : FunctionPointerTraits
        <Type_, NonPointer_, Return_,
         Tuple<>
        >
    {
    };

    template
    <typename Type_, typename Return_,
     typename Arg1_,
     typename NonPointer_
    >
    struct UnqualifiedDispatch_<Type_, Return_ (*)(Arg1_), NonPointer_**>
        : FunctionPointerTraits
        <Type_, NonPointer_, Return_, Tuple<Arg1_>
        >
    {
    };

    template
    <typename Type_, typename Return_,
     typename Arg1_, typename Arg2_,
     typename NonPointer_
    >
    struct UnqualifiedDispatch_<Type_, Return_ (*)(Arg1_, Arg2_), NonPointer_**>
        : FunctionPointerTraits
        <Type_, NonPointer_, Return_, Tuple<Arg1_, Arg2_>
        >
    {
    };

    template
    <typename Type_, typename Return_,
     typename Arg1_, typename Arg2_, typename Arg3_,
     typename NonPointer_
    >
    struct UnqualifiedDispatch_<Type_, Return_ (*)(Arg1_, Arg2_, Arg3_), NonPointer_**>
        : FunctionPointerTraits
        <Type_, NonPointer_, Return_, Tuple<Arg1_, Arg2_, Arg3_>
        >
    {
    };

    template
    <typename Type_, typename Return_,
     typename Arg1_, typename Arg2_, typename Arg3_, typename Arg4_,
     typename NonPointer_
    >
    struct UnqualifiedDispatch_<Type_, Return_ (*)(Arg1_, Arg2_, Arg3_, Arg4_), NonPointer_**>
        : FunctionPointerTraits
        <Type_, NonPointer_, Return_, Tuple<Arg1_, Arg2_, Arg3_, Arg4_>
        >
    {
    };

    template <typename Type_, typename Member_, class Class_, typename Pointer_>
    struct UnqualifiedDispatch_<Type_, Member_ Class_::*, Pointer_>
        : MemberObjectPointerTraits<Type_, Member_, Class_>
    {
    };

    template
    <typename Type_, typename Return_, class Class_,
     typename Pointer_
    >
    struct UnqualifiedDispatch_
        <Type_, Return_ (Class_::*)(), Pointer_
        >
        : MemberFunctionPointerTraits<Type_, Return_, Class_, Tuple<>>
    {
    };

    template
    <typename Type_, typename Return_, class Class_,
     typename Arg1_,
     typename Pointer_
    >
    struct UnqualifiedDispatch_
        <Type_, Return_ (Class_::*)(Arg1_), Pointer_
        >
        : MemberFunctionPointerTraits
        <Type_, Return_, Class_, Tuple<Arg1_>
        >
    {
    };

    template
    <typename Type_, typename Return_, class Class_,
     typename Arg1_, typename Arg2_,
     typename Pointer_
    >
    struct UnqualifiedDispatch_<Type_, Return_ (Class_::*)(Arg1_, Arg2_), Pointer_>
        : MemberFunctionPointerTraits
        <Type_, Return_, Class_, Tuple<Arg1_, Arg2_>
        >
    {
    };

    template
    <typename Type_, typename Return_, class Class_,
     typename Arg1_, typename Arg2_, typename Arg3_,
     typename Pointer_
    >
    struct UnqualifiedDispatch_
        <Type_, Return_ (Class_::*)(Arg1_, Arg2_, Arg3_), Pointer_
        >
        : MemberFunctionPointerTraits
        <Type_, Return_, Class_, Tuple<Arg1_, Arg2_, Arg3_>
        >
    {
    };

    template
    <typename Type_, typename Return_, class Class_,
     typename Arg1_, typename Arg2_, typename Arg3_, typename Arg4_,
     typename Pointer_
    >
    struct UnqualifiedDispatch_
        <Type_, Return_ (Class_::*)(Arg1_, Arg2_, Arg3_, Arg4_), Pointer_
        >
        : MemberFunctionPointerTraits
        <Type_, Return_, Class_, Tuple<Arg1_, Arg2_, Arg3_, Arg4_>
        >
    {
    };

    template <typename Element_, Natural LENGTH_, typename Plain_>
    struct UnqualifiedDispatch_<Element_[LENGTH_], Plain_, Plain_*>
        : BoundArrayTraits<Element_[LENGTH_], Element_, NaturalStatic<LENGTH_>>
    {
    };

    template <typename Element_, typename Plain_>
    struct UnqualifiedDispatch_<Element_[], Plain_, Plain_*>
        : UnboundArrayTraits<Element_[], Element_>
    {
    };

    template
    <typename Type_, typename Plain_,
     typename Return_
    >
    struct UnqualifiedDispatch_<Type_, Plain_, Return_ (*)()>
        : FunctionTraits<Type_, Return_, Tuple<>>
    {
    };

    template
    <typename Type_, typename Plain_,
     typename Return_, typename Arg1_
    >
    struct UnqualifiedDispatch_<Type_, Plain_, Return_ (*)(Arg1_)>
        : FunctionTraits<Type_, Return_, Tuple<Arg1_>>
    {
    };

    template
    <typename Type_, typename Plain_,
     typename Return_, typename Arg1_, typename Arg2_
    >
    struct UnqualifiedDispatch_<Type_, Plain_, Return_ (*)(Arg1_, Arg2_)>
        : FunctionTraits<Type_, Return_, Tuple<Arg1_, Arg2_>>
    {
    };

    template
    <typename Type_, typename Plain_,
     typename Return_, typename Arg1_, typename Arg2_, typename Arg3_
    >
    struct UnqualifiedDispatch_<Type_, Plain_, Return_ (*)(Arg1_, Arg2_, Arg3_)>
        : FunctionTraits<Type_, Return_, Tuple<Arg1_, Arg2_, Arg3_>>
    {
    };

    template
    <typename Type_, typename Plain_,
     typename Return_, typename Arg1_, typename Arg2_, typename Arg3_, typename Arg4_
    >
    struct UnqualifiedDispatch_<Type_, Plain_, Return_ (*)(Arg1_, Arg2_, Arg3_, Arg4_)>
        : FunctionTraits<Type_, Return_, Tuple<Arg1_, Arg2_, Arg3_, Arg4_>>
    {
    };

    template <typename Plain_>
    struct Traits
        : UnqualifiedDispatch_<Plain_, Plain_, Plain_*>
    {
        using ToNonConst = Plain_;
        using ToNonVolatile = Plain_;
        using ToNonQualified = Plain_;

        using ToPlain = Plain_;
    };

    template <typename Plain_>
    struct Traits<Plain_ const>
        : UnqualifiedDispatch_<Plain_ const, Plain_, Plain_*>
    {
        using IsQualified = True;
        using IsConst = True;

        using ToNonConst = Plain_;
        using ToNonVolatile = Plain_ const;
        using ToNonQualified = Plain_;

        using ToPlain = Plain_;
    };

    template <typename Plain_>
    struct Traits<Plain_ volatile>
        : UnqualifiedDispatch_<Plain_ volatile, Plain_, Plain_*>
    {
        using IsQualified = True;
        using IsVolatile = True;

        using ToNonConst = Plain_ volatile;
        using ToNonVolatile = Plain_;
        using ToNonQualified = Plain_;

        using ToPlain = Plain_;
    };

    template <typename Plain_>
    struct Traits<Plain_ const volatile>
        : UnqualifiedDispatch_<Plain_ const volatile, Plain_, Plain_*>
    {
        using IsQualified = True;
        using IsConst = True;
        using IsVolatile = True;
        using IsConstVolatile = True;

        using ToNonConst = Plain_ volatile;
        using ToNonVolatile = Plain_ const;
        using ToNonQualified = Plain_;

        using ToPlain = Plain_;
    };

    template <typename NonReference_>
    struct Traits<NonReference_&>
        : ReferenceTraits<NonReference_>
    {
    };

    // @todo provide type properties in Fun format rather than (yet implemented in terms of) members of Traits

    // --------------------------------------------------------
    // separate approach, individually defined traits functions

    // @todo remove overlaps with Traits

    // @todo move (some) to cong/Object/c++/core/ObjectStatic.hh(?)

    struct IsConst
    {
        template <typename T>
        struct Call
        {
            using Type = False;
        };

        template <typename T>
        struct Call<T const>
        {
            using Type = True;
        };

        template <typename T>
        struct Call<T&>
        {
            using Type = typename Call<T>::Type;
        };

        template <typename T>
        struct Call<T&&>
        {
            using Type = typename Call<T>::Type;
        };
    };

    // @todo differentiate further? (non-ref type)
    template <typename IsConst_, typename IsVolatile_, typename IsLValue_>
    struct Qual;

    struct QualOf
    {
        // @todo use Traits
        template <typename T>
        struct Call;

        template <typename T>
        struct Call<T&&>
        {
            using Type = Qual<False, False, False>;
        };

        template <typename T>
        struct Call<T const&&>
        {
            using Type = Qual<True, False, False>;
        };

        template <typename T>
        struct Call<T volatile&&>
        {
            using Type = Qual<False, True, False>;
        };

        template <typename T>
        struct Call<T const volatile&&>
        {
            using Type = Qual<True, True, False>;
        };

        template <typename T>
        struct Call<T&>
        {
            using Type = Qual<False, False, True>;
        };

        template <typename T>
        struct Call<T const&>
        {
            using Type = Qual<True, False, True>;
        };

        template <typename T>
        struct Call<T volatile&>
        {
            using Type = Qual<False, True, True>;
        };

        template <typename T>
        struct Call<T const volatile&>
        {
            using Type = Qual<True, True, True>;
        };
    };

    template <typename T>
    struct IsStatic
    {
        static constexpr bool value = std::is_base_of<StaticTag, std::remove_cv_t<T>>::value;
        using Type = core::BooleanStatic<value>;
    };
};
