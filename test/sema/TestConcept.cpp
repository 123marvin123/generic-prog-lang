//
// Created by Marvin Haschker on 15.03.25.
//
#include <catch2/catch_test_macros.hpp>
#include "../Common.h"

struct ConceptFixture
{
    std::unique_ptr<Sema> sema;
    Sema* sema_ptr;

    ConceptFixture()
    {
        sema = std::make_unique<Sema>();
        sema_ptr = sema.get();
    }

    ~ConceptFixture()
    {
        sema.reset();
    }
};

TEST_CASE_METHOD(ConceptFixture, "Concept declaration", "[concept]")
{
    constexpr auto id = "C";
    const auto data = construct_parse_tree(std::format("concept {};", id));
    const auto size = sema->concepts().size();

    INFO(sema->to_string());
    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    INFO("After declaration visitor: " << sema->to_string());

    REQUIRE(sema->concepts().size() == size + 1);
    const auto& c = sema->find_concept(id);
    REQUIRE(c.has_value());
    REQUIRE(c.value()->get_identifier() == id);
}

TEST_CASE_METHOD(ConceptFixture, "Concept definition", "[concept]")
{
    constexpr auto id = "C";
    const auto data = construct_parse_tree(std::format("concept {};", id));
    const auto size = sema->concepts().size();
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    INFO("After declaration visitor");

    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());
    INFO("After definition visitor: " << sema->to_string());

    REQUIRE(sema->concepts().size() == size + 1);
    const auto& c = sema->find_concept(id);
    REQUIRE(c.has_value());
}

TEST_CASE_METHOD(ConceptFixture, "Concept definition with bases", "[concept]")
{
    constexpr auto id = "A";
    constexpr auto id2 = "B";
    const auto data = construct_parse_tree(std::format("concept {}; concept {} : {};", id, id2, id));
    const auto size = sema->concepts().size();
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    INFO("After declaration visitor");

    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());
    INFO("After definition visitor: " << sema->to_string());

    REQUIRE(sema->concepts().size() == size + 2);
    const auto& id2_c = sema->find_concept(id2);
    const auto& id_c = sema->find_concept(id);
    REQUIRE((*id_c)->is_base_of(*id2_c));
}

TEST_CASE_METHOD(ConceptFixture, "Concept with circular base reference", "[concept]")
{
    constexpr auto id = "C";
    const auto& data = construct_parse_tree(std::format("concept {} : {};", id, id));
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    INFO("After declaration visitor");

    DefinitionVisitor v2{sema.get()};
    REQUIRE_THROWS_AS(v2.visit(data.parse_tree()), invalid_concept_base);
}

TEST_CASE_METHOD(ConceptFixture, "Concept with self as base", "[concept]")
{
    constexpr auto id = "C";
    const auto& data = construct_parse_tree(std::format("concept {} : {};", id, id));
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    INFO("After declaration visitor");

    DefinitionVisitor v2{sema.get()};
    REQUIRE_THROWS_AS(v2.visit(data.parse_tree()), invalid_concept_base);
}

TEST_CASE_METHOD(ConceptFixture, "Concept with unknown base", "[concept]")
{
    constexpr auto id = "C";
    const auto& data = construct_parse_tree(std::format("concept {} : Unknown;", id));
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    INFO("After declaration visitor");

    DefinitionVisitor v2{sema.get()};
    REQUIRE_THROWS_AS(v2.visit(data.parse_tree()), concept_not_found);
}

TEST_CASE_METHOD(ConceptFixture, "Is legal base validation", "[concept]")
{
    constexpr auto id_1 = "A";
    constexpr auto id_2 = "B";
    const auto& data = construct_parse_tree(std::format("concept {}; concept {};", id_1, id_2));
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());
    INFO("After definition visitor: " << sema->to_string());

    const auto c_1 = sema->find_concept(id_1).value();
    const auto c_2 = sema->find_concept(id_2).value();

    // Legal case: B can be a base of A
    REQUIRE(c_2->is_legal_base(c_1));

    // Make B inherit from A
    c_2->extend_bases({c_1});
    INFO("After extending bases");

    // Illegal case: A cannot inherit from B now (would create a cycle)
    REQUIRE_FALSE(c_2->is_legal_base(c_1));
}

TEST_CASE_METHOD(ConceptFixture, "Is base of with cyclic dependency", "[concept]")
{
    constexpr auto id_1 = "A";
    constexpr auto id_2 = "B";
    constexpr auto id_3 = "C";
    const auto& data = construct_parse_tree(
        std::format("concept {}; concept {} : {}; concept {} : {};", id_3, id_2, id_3, id_1, id_2));
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());
    INFO("After definition visitor: " << sema->to_string());

    auto c_a = sema->find_concept(id_1).value();
    auto c_c = sema->find_concept(id_3).value();

    // Now create a cycle by making C inherit from A: A -> B -> C -> A
    c_c->extend_bases({c_a});
    INFO("After creating cyclic dependency");

    REQUIRE_FALSE(c_a->is_base_of(c_a));
}

TEST_CASE_METHOD(ConceptFixture, "Empty description", "[concept]")
{
    constexpr auto id_1 = "A";
    const auto& data = construct_parse_tree(std::format("concept {};", id_1));
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());
    INFO("After definition visitor: " << sema->to_string());

    const auto c_a = sema->find_concept(id_1).value();
    INFO("Concept should not have a description");
    REQUIRE_FALSE(c_a->get_description().has_value());
}

TEST_CASE_METHOD(ConceptFixture, "Concept with description", "[concept]")
{
    constexpr auto id_1 = "A";
    constexpr auto id_desc = "This is a description";
    const auto& data = construct_parse_tree(std::format("concept {}(description: \"{}\");", id_1, id_desc));
    INFO(sema->to_string());

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());
    INFO("After definition visitor: " << sema->to_string());

    const auto c_a = sema->find_concept(id_1).value();
    INFO("Concept should have a description");
    REQUIRE(c_a->get_description().has_value());
    REQUIRE(std::string(*c_a->get_description()) == id_desc);
}

TEST_CASE_METHOD(ConceptFixture, "Empty name not allowed", "[concept]")
{
    INFO(sema->to_string());
    REQUIRE_THROWS_AS(Sema::create_concept(sema.get(), "").value(), std::runtime_error);
}
