//
// Created by Marvin Haschker on 15.03.25.
//
//
// Created by Marvin Haschker on 11.03.25.
//

#include "../Common.h"

TEST_GROUP(ConceptGroup)
{
    DEFAULT_SEMA()
};

TEST(ConceptGroup, TestConceptDeclaration)
{
    constexpr auto id = "C";

    const auto data = construct_parse_tree(std::format("concept {};", id));

    const auto size = sema->concepts().size();

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    CHECK(sema->concepts().size() == size + 1);

    const auto& c = sema->find_concept(id);

    CHECK(c.has_value());
    CHECK(c.value()->get_identifier() == id);
}

TEST(ConceptGroup, TestConceptDefinition)
{
    constexpr auto id = "C";

    const auto data = construct_parse_tree(std::format("concept {};", id));

    const auto size = sema->concepts().size();

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());

    CHECK(sema->concepts().size() == size + 1);
    const auto& c = sema->find_concept(id);
}

TEST(ConceptGroup, TestConceptDefinitionBases)
{
    constexpr auto id = "A";
    constexpr auto id2 = "B";

    const auto data = construct_parse_tree(std::format("concept {}; concept {} : {};", id, id2, id));

    const auto size = sema->concepts().size();

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());

    CHECK(sema->concepts().size() == size + 2);

    const auto& id2_c = sema->find_concept(id2);
    const auto& id_c = sema->find_concept(id);
    CHECK((*id_c)->is_base_of(*id2_c));
}

TEST(ConceptGroup, TestConceptBases)
{
    constexpr auto id = "C";

    const auto& data = construct_parse_tree(std::format("concept {} : {};", id, id));

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    CHECK_THROWS(invalid_concept_base, v2.visit(data.parse_tree()));
}

TEST(ConceptGroup, TestConceptSelfBase)
{
    constexpr auto id = "C";

    const auto& data = construct_parse_tree(std::format("concept {} : {};", id, id));

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    CHECK_THROWS(invalid_concept_base, v2.visit(data.parse_tree()));
}

TEST(ConceptGroup, TestConceptUnknownBase)
{
    constexpr auto id = "C";

    const auto& data = construct_parse_tree(std::format("concept {} : Unknown;", id, id));

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());

    DefinitionVisitor v2{sema.get()};
    CHECK_THROWS(concept_not_found, v2.visit(data.parse_tree()));
}

TEST(ConceptGroup, TestIsLegalBase)
{
    constexpr auto id_1 = "A";
    constexpr auto id_2 = "B";

    const auto& data = construct_parse_tree(std::format("concept {}; concept {};", id_1, id_2));

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());

    const auto c_1 = sema->find_concept(id_1).value();
    const auto c_2 = sema->find_concept(id_2).value();

    // Legal case: B can be a base of A
    CHECK(c_2->is_legal_base(c_1));

    // Make B inherit from A
    c_2->extend_bases({c_1});

    // Illegal case: A cannot inherit from B now (would create a cycle)
    CHECK_FALSE(c_2->is_legal_base(c_1));
}

TEST(ConceptGroup, TestIsBaseOfWithCyclicDependency)
{
    constexpr auto id_1 = "A";
    constexpr auto id_2 = "B";
    constexpr auto id_3 = "C";

    const auto& data = construct_parse_tree(std::format("concept {}; concept {} : {}; concept {} : {};", id_3, id_2, id_3, id_1, id_2));

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());

    auto c_a = sema->find_concept(id_1).value();
    auto c_c = sema->find_concept(id_3).value();

    // Now create a cycle by making C inherit from X: A -> B -> C -> A

    c_c->extend_bases({c_a});
    CHECK_FALSE(c_a->is_base_of(c_a));
}

TEST(ConceptGroup, TestEmptyDescription)
{
    constexpr auto id_1 = "A";
    const auto& data = construct_parse_tree(std::format("concept {};", id_1));

    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());

    const auto c_a = sema->find_concept(id_1).value();
    CHECK_FALSE_TEXT(c_a->get_description().has_value(), "Concept should not have a description");
}

TEST(ConceptGroup, TestDescription)
{
    constexpr auto id_1 = "A";
    constexpr auto id_desc = "This is a description";

    const auto& data = construct_parse_tree(std::format("concept {}(description: \"{}\");", id_1, id_desc));
    DeclarationVisitor v{sema.get()};
    v.visit(data.parse_tree());
    DefinitionVisitor v2{sema.get()};
    v2.visit(data.parse_tree());

    const auto c_a = sema->find_concept(id_1).value();
    CHECK_TRUE_TEXT(c_a->get_description().has_value(), "Concept should have a description");
    CHECK_EQUAL_TEXT(std::string(*c_a->get_description()), id_desc, "Description should be equal");
}

TEST(ConceptGroup, TestEmptyName)
{
    CHECK_THROWS(std::runtime_error, Sema::create_concept(sema.get(), "").value());
}