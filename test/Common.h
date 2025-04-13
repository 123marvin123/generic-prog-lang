//
// Created by Marvin Haschker on 15.03.25.
//

#ifndef COMMON_H
#define COMMON_H

#include <iostream>

#include "Exception.h"
#include "sema/Sema.h"

#include "visitor/DeclarationVisitor.h"
#include "visitor/DefinitionVisitor.h"

#include "CongLexer.h"
#include "CongParser.h"

template <class T>
using u_ptr = std::unique_ptr<T>;

#define UNWRAP(x) x

#define CUSTOM_SEMA(SETUP, TEARDOWN) \
    u_ptr<Sema> sema; \
    Sema* sema_ptr; \
    void setup() override { UNWRAP SETUP } \
    void teardown() override { UNWRAP TEARDOWN }

#define DEFAULT_SEMA() \
    CUSTOM_SEMA((sema = std::make_unique<Sema>(); sema_ptr = sema.get();), (std::cout << "\n" << sema->to_string(4) << std::endl; sema.reset();))

struct ANTLRData
{
    explicit ANTLRData(u_ptr<antlr4::ANTLRInputStream> input) : input_stream(std::move(input)),
        lexer(std::make_unique<CongLexer>(input_stream.get())),
        token_stream(std::make_unique<antlr4::CommonTokenStream>(lexer.get())),
        parser(std::make_unique<CongParser>(token_stream.get())),
        translation_unit(parser->translationUnit()) {}

    u_ptr<antlr4::ANTLRInputStream> input_stream;
    u_ptr<CongLexer> lexer;
    u_ptr<antlr4::CommonTokenStream> token_stream;
    u_ptr<CongParser> parser;

    [[nodiscard]] antlr4::tree::ParseTree* parse_tree() const { return translation_unit; };
private:
    antlr4::tree::ParseTree* translation_unit;
};

inline ANTLRData construct_parse_tree(const std::string& input)
{
    using namespace antlr4;
    return ANTLRData(std::make_unique<ANTLRInputStream>(input));
}
#endif //COMMON_H
