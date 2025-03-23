//
// Created by Marvin Haschker on 15.03.25.
//

#include "../Common.h"

TEST_GROUP(NamespaceGroup)
{
    DEFAULT_SEMA()
};

TEST(NamespaceGroup, TestInvalidConceptSearch)
{
    constexpr auto id = "X";
    const auto c = sema->find_concept(id);

    CHECK(!c.has_value());
}

TEST(NamespaceGroup, TestInvalidNamespaceSearch)
{
    constexpr auto id = "X";
    const auto c = sema->find_namespace(id);

    CHECK(!c.has_value());
}

TEST(NamespaceGroup, TestInvalidFunctionSearch)
{
    constexpr auto id = "X";
    const auto c = sema->find_function(id);

    CHECK(!c.has_value());
}

TEST(NamespaceGroup, TestConceptSearch)
{
    constexpr auto id = "X";
    const auto data = construct_parse_tree(std::format("concept {};", id));

    DeclarationVisitor v{sema_ptr};
    v.visit(data.parse_tree());
    const auto c = sema->find_concept(id);
    CHECK(c.has_value());
}

TEST(NamespaceGroup, TestNamespaceSearch)
{
    constexpr auto id = "X";
    const auto data = construct_parse_tree(std::format("namespace {} {{}}", id));

    DeclarationVisitor v{sema_ptr};
    v.visit(data.parse_tree());

    CHECK(sema->find_namespace(id).has_value());
}

TEST(NamespaceGroup, TestFunctionSearch)
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "f";
    const auto data = construct_parse_tree(std::format("concept {}; fun {}() -> {} {{}}", id_c, id_f, id_c));

    DeclarationVisitor v{sema_ptr};
    v.visit(data.parse_tree());

    CHECK(sema->find_function(id_f).has_value());
}

TEST(NamespaceGroup, TestChildNamespace)
{
    constexpr auto id1 = "X";
    constexpr auto id2 = "Y";
    const auto data = construct_parse_tree(std::format("namespace {} {{ namespace {} {{}} }}", id1, id2));

    DeclarationVisitor v{sema_ptr};
    v.visit(data.parse_tree());

    const auto ns1 = sema->find_namespace(id1);
    CHECK(ns1.has_value());

    const auto ns2 = ns1.value()->find_namespace(id2);
    CHECK(ns2.has_value());
    CHECK(ns2.value()->get_parent() == ns1);
    CHECK(!ns2.value()->is_global());
}

TEST(NamespaceGroup, TestTopLevelNamespace)
{
    CHECK(sema->is_global());
}

TEST(NamespaceGroup, TestFullNameWithParent)
{
    constexpr auto id1 = "X";
    constexpr auto id2 = "Y";
    const auto data = construct_parse_tree(std::format("namespace {} {{ namespace {} {{}} }}", id1, id2));

    DeclarationVisitor v{sema_ptr};
    v.visit(data.parse_tree());

    const auto ns1 = sema->find_namespace(id1).value();
    const auto ns2 = ns1->find_namespace(id2).value();

    CHECK(id1 == ns1->get_identifier());
    CHECK(id2 == ns2->get_identifier());
    CHECK(std::format("::{}", std::string{id1}) == ns1->get_full_name());
    CHECK(std::format("::{}::{}", std::string{id1}, std::string{id2}) == ns2->get_full_name());
}

TEST(NamespaceGroup, TestRemoveFunctions)
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "f";
    constexpr auto id_ns = "NS";

    const auto data = construct_parse_tree(std::format(
        "concept {}; fun {}() -> {} {{}} namespace {} {{}}", id_c, id_f, id_c, id_ns));

    DeclarationVisitor v{sema_ptr};
    v.visit(data.parse_tree());

    const auto c = sema->find_concept(id_c);
    const auto f = sema->find_function(id_f);
    const auto ns = sema->find_namespace(id_ns);
    CHECK(c.has_value());
    CHECK(f.has_value());
    CHECK(ns.has_value());

    CHECK(sema->remove_concept(c.value()));
    CHECK(sema->remove_function(f.value()));
    CHECK(sema->remove_namespace(ns.value()));

    CHECK(!sema->find_concept(id_c).has_value());
    CHECK(!sema->find_function(id_f).has_value());
    CHECK(!sema->find_namespace(id_ns).has_value());
}

TEST(NamespaceGroup, TestRegister)
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "F";
    constexpr auto id_ns = "NS";

    const auto new_concept = Sema::create_concept(sema_ptr, id_c);
    const auto new_ns = Sema::create_namespace(id_ns, sema_ptr, sema_ptr);
    const auto new_func = Sema::create_function<ConcreteFunction>(sema_ptr, id_f, sema_ptr, new_concept.value());

    CHECK(new_concept.has_value());
    CHECK(new_ns.has_value());
    CHECK(new_func.has_value());

    const auto c = sema->find_concept(id_c);
    const auto f = sema->find_function(id_f);
    const auto ns = sema->find_namespace(id_ns);
    CHECK(c.has_value());
    CHECK(f.has_value());
    CHECK(ns.has_value());

    CHECK(c.value() == new_concept.value());
    CHECK(f.value() == new_func.value());
    CHECK(ns.value() == new_ns.value());
}

TEST(NamespaceGroup, TestRegisterTwice)
{
    constexpr auto id_c = "C";
    constexpr auto id_f = "F";
    constexpr auto id_ns = "NS";

    const auto& new_concept = Sema::create_concept(sema_ptr, id_c);
    CHECK(new_concept.has_value());
    CHECK(Sema::create_namespace(id_ns, sema_ptr, sema_ptr).has_value());
    CHECK(Sema::create_function<ConcreteFunction>(sema_ptr, id_f, sema_ptr, new_concept.value()).has_value());

    CHECK(!Sema::create_concept(sema_ptr, id_c).has_value());
    CHECK(!Sema::create_namespace(id_ns, sema_ptr, sema_ptr));
    CHECK(!Sema::create_function<ConcreteFunction>(sema_ptr, id_f, sema_ptr, new_concept.value()));
}

TEST(NamespaceGroup, TestEmptyName)
{
    CHECK_THROWS(std::runtime_error, Sema::create_namespace("", sema_ptr, sema_ptr).value());
}