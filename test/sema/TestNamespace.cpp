//
// Created by Marvin Haschker on 15.03.25.
//

#include <catch2/catch_test_macros.hpp>
#include "../Common.h"

struct NamespaceFixture {
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;

    NamespaceFixture() {
        sema = std::make_unique<Sema>();
        sema_ptr = sema.get();
    }

    ~NamespaceFixture() {
        sema.reset();
    }
};

TEST_CASE_METHOD(NamespaceFixture, "Invalid concept search", "[namespace]")
{
    INFO(sema->to_string());
    constexpr auto id = "X";
    const auto c = sema->find_concept(id);

    REQUIRE_FALSE(c.has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Invalid namespace search", "[namespace]")
{
    INFO(sema->to_string());
    constexpr auto id = "X";
    const auto c = sema->find_namespace(id);

    REQUIRE_FALSE(c.has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Invalid function search", "[namespace]")
{
    INFO(sema->to_string());
    constexpr auto id = "X";
    const auto c = sema->find_function(id);

    REQUIRE_FALSE(c.has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Concept search", "[namespace]")
{
    constexpr auto id = "X";
    const auto data = construct_parse_tree(std::format("concept {};", id));

    DeclarationVisitor v{sema_ptr, DeclarationVisitor::Mode::Concepts};
    v.visit(data.parse_tree());

    INFO(sema->to_string());

    const auto c = sema->find_concept(id);
    REQUIRE(c.has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Namespace search", "[namespace]")
{
    constexpr auto id = "X";
    const auto data = construct_parse_tree(std::format("namespace {} {{}}", id));

    DeclarationVisitor v{sema_ptr, DeclarationVisitor::Mode::Concepts};
    v.visit(data.parse_tree());

    INFO(sema->to_string());

    REQUIRE(sema->find_namespace(id).has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Function search", "[namespace]")
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "f";
    const auto data = construct_parse_tree(std::format("concept {}; fun {}() -> {} {{}}", id_c, id_f, id_c));

    DeclarationVisitor v{sema_ptr, DeclarationVisitor::Mode::Concepts};
    v.visit(data.parse_tree());

    DeclarationVisitor v2{sema_ptr, DeclarationVisitor::Mode::Functions, false};
    v2.visit(data.parse_tree());

    INFO(sema->to_string());

    REQUIRE(sema->find_function(id_f).has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Child namespace", "[namespace]")
{
    constexpr auto id1 = "X";
    constexpr auto id2 = "Y";
    const auto data = construct_parse_tree(std::format("namespace {} {{ namespace {} {{}} }}", id1, id2));

    DeclarationVisitor v{sema_ptr, DeclarationVisitor::Mode::Concepts};
    v.visit(data.parse_tree());

    INFO(sema->to_string());

    const auto ns1 = sema->find_namespace(id1);
    REQUIRE(ns1.has_value());

    const auto ns2 = ns1.value()->find_namespace(id2);
    REQUIRE(ns2.has_value());
    REQUIRE(ns2.value()->get_parent() == ns1);
    REQUIRE_FALSE(ns2.value()->is_global());
}

TEST_CASE_METHOD(NamespaceFixture, "Top level namespace", "[namespace]")
{
    INFO(sema->to_string());
    REQUIRE(sema->is_global());
}

TEST_CASE_METHOD(NamespaceFixture, "Full name with parent", "[namespace]")
{
    constexpr auto id1 = "X";
    constexpr auto id2 = "Y";
    const auto data = construct_parse_tree(std::format("namespace {} {{ namespace {} {{}} }}", id1, id2));

    DeclarationVisitor v{sema_ptr, DeclarationVisitor::Mode::Concepts};
    v.visit(data.parse_tree());

    INFO(sema->to_string());

    const auto ns1 = sema->find_namespace(id1).value();
    const auto ns2 = ns1->find_namespace(id2).value();

    REQUIRE(id1 == ns1->get_identifier());
    REQUIRE(id2 == ns2->get_identifier());
    REQUIRE(std::format("::{}", std::string{id1}) == ns1->get_full_name());
    REQUIRE(std::format("::{}::{}", std::string{id1}, std::string{id2}) == ns2->get_full_name());
}

TEST_CASE_METHOD(NamespaceFixture, "Remove functions", "[namespace]")
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "f";
    constexpr auto id_ns = "NS";

    const auto data = construct_parse_tree(std::format(
        "concept {}; fun {}() -> {} {{}} namespace {} {{}}", id_c, id_f, id_c, id_ns));

    DeclarationVisitor v{sema_ptr, DeclarationVisitor::Mode::Concepts};
    v.visit(data.parse_tree());

    DeclarationVisitor v2{sema_ptr, DeclarationVisitor::Mode::Functions, false};
    v2.visit(data.parse_tree());

    INFO(sema->to_string());

    const auto c = sema->find_concept(id_c);
    const auto f = sema->find_function(id_f);
    const auto ns = sema->find_namespace(id_ns);
    REQUIRE(c.has_value());
    REQUIRE(f.has_value());
    REQUIRE(ns.has_value());

    REQUIRE(sema->remove_concept(c.value()));
    REQUIRE(sema->remove_function(f.value()));
    REQUIRE(sema->remove_namespace(ns.value()));

    REQUIRE_FALSE(sema->find_concept(id_c).has_value());
    REQUIRE_FALSE(sema->find_function(id_f).has_value());
    REQUIRE_FALSE(sema->find_namespace(id_ns).has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Register", "[namespace]")
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "F";
    constexpr auto id_ns = "NS";

    const auto new_concept = Sema::create_concept(sema_ptr, id_c);
    const auto new_ns = Sema::create_namespace(id_ns, sema_ptr, sema_ptr);
    const auto new_func = Sema::create_function<ConcreteFunction>(sema_ptr, id_f, sema_ptr, new_concept.value());

    INFO(sema->to_string());

    REQUIRE(new_concept.has_value());
    REQUIRE(new_ns.has_value());
    REQUIRE(new_func.has_value());

    const auto c = sema->find_concept(id_c);
    const auto f = sema->find_function(id_f);
    const auto ns = sema->find_namespace(id_ns);
    REQUIRE(c.has_value());
    REQUIRE(f.has_value());
    REQUIRE(ns.has_value());

    REQUIRE(c.value() == new_concept.value());
    REQUIRE(f.value() == new_func.value());
    REQUIRE(ns.value() == new_ns.value());
}

TEST_CASE_METHOD(NamespaceFixture, "Register twice", "[namespace]")
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "F";
    constexpr auto id_ns = "NS";

    const auto& new_concept = Sema::create_concept(sema_ptr, id_c);

    INFO(sema->to_string());

    REQUIRE(new_concept.has_value());
    REQUIRE(Sema::create_namespace(id_ns, sema_ptr, sema_ptr).has_value());
    REQUIRE(Sema::create_function<ConcreteFunction>(sema_ptr, id_f, sema_ptr, new_concept.value()).has_value());

    REQUIRE_FALSE(Sema::create_concept(sema_ptr, id_c).has_value());
    REQUIRE_FALSE(Sema::create_namespace(id_ns, sema_ptr, sema_ptr).has_value());
    REQUIRE_FALSE(Sema::create_function<ConcreteFunction>(sema_ptr, id_f, sema_ptr, new_concept.value()).has_value());
}

TEST_CASE_METHOD(NamespaceFixture, "Empty name", "[namespace]")
{
    REQUIRE_THROWS_AS(Sema::create_namespace("", sema_ptr, sema_ptr).value(), std::runtime_error);
}