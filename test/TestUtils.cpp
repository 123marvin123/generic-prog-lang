//
// Created by Marvin Haschker on 15.03.25.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "Common.h"
#include "Utils.h"

struct UtilsFixture {
    u_ptr<Sema> sema;
    Sema* sema_ptr;

    UtilsFixture() : sema(std::make_unique<Sema>()), sema_ptr(sema.get()) {}
};

TEST_CASE_METHOD(UtilsFixture, "Split fully qualified identifier - local", "[utils]")
{
    constexpr auto id = "A::B::C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    REQUIRE_FALSE(topLevel);
    REQUIRE(identifier == "C");
    REQUIRE(namespaces.size() == 2);
    REQUIRE(namespaces[0] == "A");
    REQUIRE(namespaces[1] == "B");
}

TEST_CASE_METHOD(UtilsFixture, "Split fully qualified identifier - top level", "[utils]")
{
    constexpr auto id = "::A::B::C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    REQUIRE(topLevel);
    REQUIRE(identifier == "C");
    REQUIRE(namespaces.size() == 2);
    REQUIRE(namespaces[0] == "A");
    REQUIRE(namespaces[1] == "B");
}

TEST_CASE_METHOD(UtilsFixture, "Split fully qualified identifier - simple identifier", "[utils]")
{
    constexpr auto id = "C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    REQUIRE_FALSE(topLevel);
    REQUIRE(identifier == "C");
    REQUIRE(namespaces.empty());
}

TEST_CASE_METHOD(UtilsFixture, "Split fully qualified identifier - simple identifier top level", "[utils]")
{
    constexpr auto id = "::C";
    const auto [namespaces, identifier, topLevel] =
        utils::split_fully_qualified_identifier(id);

    REQUIRE(topLevel);
    REQUIRE(identifier == "C");
    REQUIRE(namespaces.empty());
}

TEST_CASE_METHOD(UtilsFixture, "Cleanup string literal", "[utils]")
{
    constexpr auto id = "\"Hello World!\"";
    constexpr auto id2 = "Anything else";

    REQUIRE(utils::cleanup_string_literal("").empty());
    REQUIRE(utils::cleanup_string_literal("a") == "a");
    REQUIRE(utils::cleanup_string_literal(id) == "Hello World!");
    REQUIRE(utils::cleanup_string_literal(id2) == id2);
}

TEST_CASE_METHOD(UtilsFixture, "is() returns true for valid dynamic cast", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Derived();
    REQUIRE(utils::is<Derived>(base));
    delete base;
}

TEST_CASE_METHOD(UtilsFixture, "is() returns false for invalid dynamic cast", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Base();
    REQUIRE_FALSE(utils::is<Derived>(base));
    delete base;
}

TEST_CASE_METHOD(UtilsFixture, "is() returns true for valid shared_ptr dynamic cast", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const s_ptr<Base> base = std::make_shared<Derived>();
    REQUIRE(utils::is<Derived>(base));
}

TEST_CASE_METHOD(UtilsFixture, "is() returns false for invalid shared_ptr dynamic cast", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const auto base = std::make_shared<Base>();
    REQUIRE_FALSE(utils::is<Derived>(base));
}

TEST_CASE_METHOD(UtilsFixture, "dyn_cast returns valid pointer for correct type", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    Base* base = new Derived();
    REQUIRE(utils::dyn_cast<Derived>(base) != nullptr);
    delete base;
}

TEST_CASE_METHOD(UtilsFixture, "dyn_cast returns nullptr for incorrect type", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const auto base = new Base();
    REQUIRE(utils::dyn_cast<Derived>(base) == nullptr);
    delete base;
}

TEST_CASE_METHOD(UtilsFixture, "dyn_cast const returns valid pointer for correct type", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Derived();
    REQUIRE(utils::dyn_cast<Derived>(base) != nullptr);
    delete base;
}

TEST_CASE_METHOD(UtilsFixture, "dyn_cast const returns nullptr for incorrect type", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const Base* base = new Base();
    REQUIRE(utils::dyn_cast<Derived>(base) == nullptr);
    delete base;
}

TEST_CASE_METHOD(UtilsFixture, "dyn_ptr_cast returns valid shared_ptr for correct type", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const s_ptr<Base> base = std::make_shared<Derived>();
    REQUIRE(utils::dyn_ptr_cast<Derived>(base) != nullptr);
}

TEST_CASE_METHOD(UtilsFixture, "dyn_ptr_cast returns nullptr for incorrect type", "[utils]")
{
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};

    const auto base = std::make_shared<Base>();
    REQUIRE(utils::dyn_ptr_cast<Derived>(base) == nullptr);
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with valid concept identifier", "[utils]")
{
    constexpr auto c_id = "Object";
    const utils::FQIInfo fqiInfo{{}, c_id, true};

    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    REQUIRE(result.has_value());
    REQUIRE(std::string((*sema->find_concept(c_id))->get_identifier()) ==
            std::string((*result)->get_identifier()));
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with invalid concept identifier", "[utils]")
{
    const utils::FQIInfo fqiInfo{{}, "invalid_identifier", true};

    auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with valid concept identifier in namespace", "[utils]")
{
    constexpr auto ns_id = "A";
    constexpr auto c_id = "C";
    const utils::FQIInfo fqiInfo{{ns_id}, c_id, true};

    const auto ns = Sema::create_namespace(ns_id, sema.get(), sema.get()).value();
    Sema::create_concept(ns, c_id).value();

    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    REQUIRE(result.has_value());
    REQUIRE(std::string((*result)->get_identifier()) == c_id);
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with empty concept identifier", "[utils]")
{
    const utils::FQIInfo fqiInfo{{}, "", true};

    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, sema.get());
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with null namespace", "[utils]")
{
    const utils::FQIInfo fqiInfo{{"namespace1", "namespace2"}, "identifier", true};
    const auto result = utils::resolve_fully_qualified_identifier<Concept>(fqiInfo, nullptr);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with valid function identifier", "[utils]")
{
    constexpr auto f_id = "id";
    const auto object = *sema->find_concept("Object");
    const auto sema_ptr = sema.get();
    const Function* f = *Sema::create_function<ConcreteFunction>(sema.get(), f_id, sema_ptr, object);
    const utils::FQIInfo fqiInfo{{}, f_id, true};

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    REQUIRE(result.has_value());
    REQUIRE(std::string((*result)->get_identifier()) == f_id);
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with invalid function identifier", "[utils]")
{
    const utils::FQIInfo fqiInfo{{}, "non_existent_function", true};

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with valid function identifier in namespace", "[utils]")
{
    constexpr auto ns_id = "Math";
    constexpr auto f_id = "add";
    const utils::FQIInfo fqiInfo{{ns_id}, f_id, false};
    const auto number = *sema->find_concept("Number");

    const auto ns = *Sema::create_namespace(ns_id, sema.get(), sema.get());
    *Sema::create_function<ConcreteFunction>(ns, f_id, ns, number);

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    REQUIRE(result.has_value());
    REQUIRE(std::string((*result)->get_identifier()) == f_id);
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with empty function identifier", "[utils]")
{
    const utils::FQIInfo fqiInfo{{}, "", true};

    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, sema.get());
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with null namespace for function", "[utils]")
{
    const utils::FQIInfo fqiInfo{{"namespace1", "namespace2"}, "function_id", true};
    const auto result = utils::resolve_fully_qualified_identifier<Function>(fqiInfo, nullptr);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with invalid namespace identifier", "[utils]")
{
    const utils::FQIInfo fqiInfo{{}, "invalid_namespace", true};

    const auto result = utils::resolve_fully_qualified_identifier<Namespace>(fqiInfo, sema.get());
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with valid namespace identifier", "[utils]")
{
    constexpr auto ns_id = "Math";
    const utils::FQIInfo fqiInfo{{}, ns_id, true};

    *Sema::create_namespace(ns_id, sema.get(), sema.get());

    const auto result = utils::resolve_fully_qualified_identifier<Namespace>(fqiInfo, sema.get());
    REQUIRE(result.has_value());
    REQUIRE(std::string((*result)->get_identifier()) == ns_id);
}

TEST_CASE_METHOD(UtilsFixture, "resolve_fully_qualified_identifier with nested namespaces", "[utils]")
{
    constexpr auto ns_id1 = "Math";
    constexpr auto ns_id2 = "Test";

    const auto a = *Sema::create_namespace(ns_id1, sema.get(), sema.get());
    const auto b = *Sema::create_namespace(ns_id2, sema.get(), a);

    const utils::FQIInfo fqiInfo{{ns_id1}, ns_id2, true};
    const auto result = utils::resolve_fully_qualified_identifier<Namespace>(fqiInfo, sema.get());
    REQUIRE(result.has_value());
    REQUIRE(std::string(b->get_identifier()) == std::string((*result)->get_identifier()));
}

TEST_CASE_METHOD(UtilsFixture, "Cross namespace concept dependency with simple name", "[utils]")
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

    REQUIRE(true);
}

TEST_CASE_METHOD(UtilsFixture, "Top level namespace", "[utils]")
{
    const auto [namespaces, identifier, topLevel] = utils::split_fully_qualified_identifier("::");
    REQUIRE(namespaces.empty());
    REQUIRE(identifier.empty());
    REQUIRE(topLevel);
}