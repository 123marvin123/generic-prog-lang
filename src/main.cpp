#include <Preprocessor.h>
#include <iostream>
#include <regex>

#include "CongLexer.h"
#include "CongParser.h"

#include "visitor/DeclarationVisitor.h"
#include "visitor/DefinitionVisitor.h"
#include "visitor/FinalizingFunctionVisitor.h"

#include <termcolor/termcolor.hpp>
#include "export/InjaEngine.h"

using namespace antlr4;

u_ptr<Sema> run_eval(tree::ParseTree* tree)
{
    auto sema = std::make_unique<Sema>();

    DeclarationVisitor v{sema.get()};
    v.visit(tree);

    DefinitionVisitor v2{sema.get()};
    v2.visit(tree);

    FinalizingFunctionVisitor v3{sema.get()};
    v3.visit(tree);

    return std::move(sema);
}

int main()
{

#ifdef NDEBUG
    printf("Release configuration!\n");
#else
    std::cout << termcolor::red << "Debug Configuration!" << termcolor::reset << std::endl;
#endif

    Preprocessor preprocessor{};
    auto code = preprocessor.process("example/example_1.txt");

    // Create an input stream from the input string
    ANTLRInputStream inputStream(code);

    // Create a lexer that feeds off of the input stream
    CongLexer lexer(&inputStream);

    // Create a token stream from the lexer
    CommonTokenStream tokens(&lexer);

    // Create a parser that feeds off the token stream
    CongParser parser(&tokens);

    // Begin parsing at the 'expr' rule
    tree::ParseTree* tree = parser.translationUnit();

#ifndef NDEBUG
    // Print the parse tree (for debugging purposes)
    std::cout << tree->toStringTree(&parser) << std::endl;
#endif

    u_ptr<Sema> sema = run_eval(tree);

    InjaEngine engine{sema.get()};


    return 0;
}
