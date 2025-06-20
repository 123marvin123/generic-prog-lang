#pragma once

#include "Preprocessor.h"
#include "CongLexer.h"
#include "CongParser.h"

#include "visitor/DeclarationVisitor.h"
#include "visitor/DefinitionVisitor.h"
#include "visitor/FinalizingFunctionVisitor.h"

#include "CustomErrorListener.h"

class Processor final
{
    u_ptr<antlr4::ANTLRInputStream> input_stream;
    u_ptr<CongLexer> lexer;
    u_ptr<CongParser> parser;
    u_ptr<antlr4::CommonTokenStream> token_stream;
    u_ptr<CustomErrorListener> customErrorListener;
public:

    explicit Processor(const std::filesystem::path& f)
    {
        Preprocessor preprocessor{};
        auto code = preprocessor.process(f);

        this->input_stream = std::make_unique<antlr4::ANTLRInputStream>(code);
        this->lexer = std::make_unique<CongLexer>(this->input_stream.get());
        this->token_stream = std::make_unique<antlr4::CommonTokenStream>(this->lexer.get());
        this->parser = std::make_unique<CongParser>(this->token_stream.get());

        this->customErrorListener = std::make_unique<CustomErrorListener>();
        this->parser->removeErrorListeners();
        this->parser->addErrorListener(customErrorListener.get());
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

        try
        {
            DeclarationVisitor v1{sema.get(), DeclarationVisitor::Mode::Concepts};
            v1.visit(tree);

            DeclarationVisitor v2{sema.get(), DeclarationVisitor::Mode::Functions, false};
            v2.visit(tree);

            DefinitionVisitor v3{sema.get()};
            v3.visit(tree);

            FinalizingFunctionVisitor v4{sema.get()};
            v4.visit(tree);
        }
        catch (...)
        {
            std::throw_with_nested(std::runtime_error("Semantic actions failed"));
        }

        return std::move(sema);
    }
};
