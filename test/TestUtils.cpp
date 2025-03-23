//
// Created by Marvin Haschker on 15.03.25.
//

#include "Common.h"
#include "Utils.h"

TEST_GROUP(UtilsGroup)
{
    DEFAULT_SEMA()
};

TEST(UtilsGroup, TestSplitFQILocal)
{
    constexpr auto id = "A::B::C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    CHECK(!topLevel);
    CHECK(identifier == "C");
    CHECK(namespaces.size() == 2);
    CHECK(namespaces[0] == "A");
    CHECK(namespaces[1] == "B");
}

TEST(UtilsGroup, TestSplitFQITopLevel)
{
    constexpr auto id = "::A::B::C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    CHECK(topLevel);
    CHECK(identifier == "C");
    CHECK(namespaces.size() == 2);
    CHECK(namespaces[0] == "A");
    CHECK(namespaces[1] == "B");
}

TEST(UtilsGroup, TestSplitFQISimpleIdentifier)
{
    constexpr auto id = "C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    CHECK(!topLevel);
    CHECK(identifier == "C");
    CHECK(namespaces.empty());
}

TEST(UtilsGroup, TestSplitFQISimpleIdentifierTopLevel)
{
    constexpr auto id = "::C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    CHECK(topLevel);
    CHECK(identifier == "C");
    CHECK(namespaces.empty());
}

TEST(UtilsGroup, TestCleanupStringLiteral)
{
    constexpr auto id = "\"Hello World!\"";
    constexpr auto id2 = "Anything else";

    CHECK(utils::cleanup_string_literal("").empty());
    STRCMP_EQUAL("a", utils::cleanup_string_literal("a").c_str());
    STRCMP_EQUAL("Hello World!", utils::cleanup_string_literal(id).c_str());
    STRCMP_EQUAL(id2, utils::cleanup_string_literal(id2).c_str());
}

TEST(UtilsGroup, TestReturnsTrueForValidDynamicCast)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Derived();
    CHECK(utils::is<Derived>(base));
    delete base;
}

TEST(UtilsGroup, TestReturnsFalseForInvalidDynamicCast)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Base();
    CHECK(!utils::is<Derived>(base));
    delete base;
}

TEST(UtilsGroup, TestReturnsTrueForValidSharedPtrDynamicCast)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const s_ptr<Base> base = std::make_shared<Derived>();
    CHECK(utils::is<Derived>(base));
}

TEST(UtilsGroup, TestReturnsFalseForInvalidSharedPtrDynamicCast)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const auto base = std::make_shared<Base>();
    CHECK(!utils::is<Derived>(base));
}

TEST(UtilsGroup, TestDynCastReturnsValidPointerForCorrectType)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    Base* base = new Derived();
    CHECK(utils::dyn_cast<Derived>(base) != nullptr);
    delete base;
}

TEST(UtilsGroup, TestDynCastReturnsNullptrForIncorrectType)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const auto base = new Base();
    CHECK(utils::dyn_cast<Derived>(base) == nullptr);
    delete base;
}

TEST(UtilsGroup, TestDynCastConstReturnsValidPointerForCorrectType)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Derived();
    CHECK(utils::dyn_cast<Derived>(base) != nullptr);
    delete base;
}

TEST(UtilsGroup, TestDynCastConstReturnsNullptrForIncorrectType)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Base();
    CHECK(utils::dyn_cast<Derived>(base) == nullptr);
    delete base;
}

TEST(UtilsGroup, TestDynPtrCastReturnsValidSharedPtrForCorrectType)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const s_ptr<Base> base = std::make_shared<Derived>();
    CHECK(utils::dyn_ptr_cast<Derived>(base) != nullptr);
}

TEST(UtilsGroup, TestDynPtrCastReturnsNullptrForIncorrectType)
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const auto base = std::make_shared<Base>();
    CHECK(utils::dyn_ptr_cast<Derived>(base) == nullptr);
}

TEST(UtilsGroup, TestResolveFQIWithValidConceptIdentifier)
{
    constexpr auto c_id = "Object";
    const utils::FQIInfo fqiInfo{{}, c_id, true};

    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    CHECK(result.has_value());
    CHECK_EQUAL(std::string((*sema->find_concept(c_id))->get_identifier()), std::string((*result)->get_identifier()));
}

TEST(UtilsGroup, TestResolveFQIWithInvalidConceptIdentifier)
{
    const utils::FQIInfo fqiInfo{{}, "invalid_identifier", true};

    auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    CHECK(!result.has_value());
}

TEST(UtilsGroup, TestResolveFQIWithValidConceptIdentifierInNamespace)
{
    constexpr auto ns_id = "A";
    constexpr auto c_id = "C";
    const utils::FQIInfo fqiInfo{{ns_id}, c_id, true};

    const auto ns = Sema::create_namespace(ns_id, sema.get(), sema.get()).value();
    Sema::create_concept(ns, c_id).value();

    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    CHECK(result.has_value());
    CHECK_EQUAL(c_id, std::string((*result)->get_identifier()));
}

TEST(UtilsGroup, TestResolveFQIWithEmptyConceptIdentifier)
{
    const utils::FQIInfo fqiInfo{{}, "", true};

    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    CHECK(!result.has_value());
}

TEST(UtilsGroup, TestResolveFQIWithNullNamespace)
{
    const utils::FQIInfo fqiInfo{{"namespace1", "namespace2"}, "identifier", true};
    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, nullptr);
    CHECK(!result.has_value());
}

TEST(UtilsGroup, TestResolveFQIWithValidFunctionIdentifier)
{
    constexpr auto f_id = "id";
    const auto object = *sema->find_concept("Object");
    const auto sema_ptr = sema.get();
    const Function* f = *Sema::create_function<ConcreteFunction>(sema.get(), f_id, sema_ptr, object);
    const utils::FQIInfo fqiInfo{{}, f_id, true};

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    CHECK(result.has_value());
    CHECK_EQUAL(f_id, std::string((*result)->get_identifier()));
}

TEST(UtilsGroup, TestResolveFQIWithInvalidFunctionIdentifier)
{
    const utils::FQIInfo fqiInfo{{}, "non_existent_function", true};

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    CHECK(!result.has_value());
}

TEST(UtilsGroup, TestResolveFQIWithValidFunctionIdentifierInNamespace)
{
    constexpr auto ns_id = "Math";
    constexpr auto f_id = "add";
    const utils::FQIInfo fqiInfo{{ns_id}, f_id, false};
    const auto number = *sema->find_concept("Number");

    const auto ns = *Sema::create_namespace(ns_id, sema.get(), sema.get());
    *Sema::create_function<ConcreteFunction>(ns, f_id, ns, number);

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    CHECK(result.has_value());
    CHECK_EQUAL(f_id, std::string((*result)->get_identifier()));
}

TEST(UtilsGroup, TestResolveFQIWithEmptyFunctionIdentifier)
{
    const utils::FQIInfo fqiInfo{{}, "", true};

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    CHECK(!result.has_value());
}

TEST(UtilsGroup, TestResolveFQIWithNullNamespaceForFunction)
{
    const utils::FQIInfo fqiInfo{{"namespace1", "namespace2"}, "function_id", true};
    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, nullptr);
    CHECK(!result.has_value());
}

TEST(UtilsGroup, TestResolveFQIWithInvalidNamespaceIdentifier)
{
    const utils::FQIInfo fqiInfo{{}, "invalid_namespace", true};

    const auto result = utils::resolve_fully_qualified_identifier<Namespace>(fqiInfo, sema.get());
    CHECK(!result.has_value());
}

TEST(UtilsGroup, TestResolveFQIWithValidNamespaceIdentifier)
{
    constexpr auto ns_id = "Math";
    const utils::FQIInfo fqiInfo{{}, ns_id, true};

    *Sema::create_namespace(ns_id, sema.get(), sema.get());

    const auto result = utils::resolve_fully_qualified_identifier<Namespace>(fqiInfo, sema.get());
    CHECK(result.has_value());
    CHECK_EQUAL(ns_id, std::string((*result)->get_identifier()));
}

TEST(UtilsGroup, TestResolveFQIWithNestedNamespaces)
{
    constexpr auto ns_id1 = "Math";
    constexpr auto ns_id2 = "Test";

    const auto a = *Sema::create_namespace(ns_id1, sema.get(), sema.get());
    const auto b = *Sema::create_namespace(ns_id2, sema.get(), a);

    const utils::FQIInfo fqiInfo{{ns_id1}, ns_id2, true};
    const auto result = utils::resolve_fully_qualified_identifier<Namespace>(fqiInfo, sema.get());
    CHECK(result.has_value());
    CHECK_EQUAL(std::string(b->get_identifier()), std::string((*result)->get_identifier()));
}

TEST(UtilsGroup, TestCrossNamespaceConceptDependencyWithSimpleName)
{
    constexpr auto ns_id1 = "NSA";
    constexpr auto ns_id2 = "NSB";

    constexpr auto c_a = "A";
    constexpr auto c_b = "B";

    const auto program = std::format(R"V(
        namespace {} {{
            concept {};
            namespace {} {{
                concept {} : {};
            }}
        }})V", ns_id1, c_a, ns_id2, c_b, c_a);

    const auto& data = construct_parse_tree(program);

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());
}

TEST(UtilsGroup, TestToplevelNS)
{
    const auto [namespaces, identifier, topLevel]= utils::split_fully_qualified_identifier("::");
    CHECK_TRUE(namespaces.empty());
    CHECK_TRUE(identifier.empty());
    CHECK_TRUE(topLevel);
}