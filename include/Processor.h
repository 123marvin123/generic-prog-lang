//
// Created by Marvin Haschker on 25.03.25.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Preprocessor.h"
#include "CongLexer.h"
#include "CongParser.h"

#include "visitor/DeclarationVisitor.h"
#include "visitor/DefinitionVisitor.h"
#include "visitor/FinalizingFunctionVisitor.h"

class Processor final
{
    u_ptr<antlr4::ANTLRInputStream> input_stream;
    u_ptr<CongLexer> lexer;
    u_ptr<CongParser> parser;
    u_ptr<antlr4::CommonTokenStream> token_stream;
public:

    explicit Processor(const std::filesystem::path& f)
    {
        Preprocessor preprocessor{};
        auto code = preprocessor.process(f);

        this->input_stream = std::make_unique<antlr4::ANTLRInputStream>(code);
        this->lexer = std::make_unique<CongLexer>(this->input_stream.get());
        this->token_stream = std::make_unique<antlr4::CommonTokenStream>(this->lexer.get());
        this->parser = std::make_unique<CongParser>(this->token_stream.get());
    }

    [[nodiscard]]
    antlr4::tree::ParseTree* get_translation_unit() const
    {
        return this->parser->translationUnit();
    }

    [[nodiscard]]
    u_ptr<Sema> run_sema() const
    {
        auto sema = std::make_unique<Sema>();
        const auto tree = get_translation_unit();

        DeclarationVisitor v{sema.get()};
        v.visit(tree);

        DefinitionVisitor v2{sema.get()};
        v2.visit(tree);

        FinalizingFunctionVisitor v3{sema.get()};
        v3.visit(tree);

        return std::move(sema);
    }
};

#endif //PROCESSOR_H
