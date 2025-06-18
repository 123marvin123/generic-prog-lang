#include "CustomErrorListener.h"

void CustomErrorListener::syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line,
                                      size_t charPositionInLine, const std::string& msg, std::exception_ptr e)
{
    std::cerr << "Error on line " << line << ":" << charPositionInLine << " at ";
    if (offendingSymbol) {
        std::cerr << offendingSymbol->getText();
    } else {
        std::cerr << "<unknown>";
    }
    std::cerr << ": " << msg << std::endl;

    auto parser = dynamic_cast<antlr4::Parser*>(recognizer);
    if (!parser) return;

    antlr4::TokenStream* tokens = parser->getTokenStream();
    if (!tokens) return;

    std::string input = tokens->getTokenSource()->getInputStream()->toString();
    std::istringstream iss(input);
    std::vector<std::string> allLines;
    std::string lineText;
    
    while (std::getline(iss, lineText)) {
        allLines.push_back(lineText);
    }
    
    if (line > 1 && line - 2 < allLines.size()) {
        std::cerr << ">> " << allLines[line - 2] << std::endl;
    }
    
    if (line - 1 < allLines.size()) {
        std::cerr << ">> " << allLines[line - 1] << std::endl;

        std::cerr << ">> ";
        for (size_t i = 0; i < charPositionInLine; ++i) {
            std::cerr << " ";
        }
        if (offendingSymbol) {
            std::string offendingText = offendingSymbol->getText();
            for (size_t i = 0; i < offendingText.length(); ++i) {
                std::cerr << "^";
            }
        }
        std::cerr << std::endl;
    } else {
        std::cerr << ">> <End of input reached before error line>" << std::endl;
    }

    if (line < allLines.size()) {
        std::cerr << ">> " << allLines[line] << std::endl;
    }
}