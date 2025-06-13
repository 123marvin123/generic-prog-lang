#pragma once

#include <stdexcept>
#include <string>
#include <sstream>
#include "antlr4-runtime.h"

struct SemaError final : std::runtime_error {
    explicit SemaError(const std::string& message, antlr4::ParserRuleContext* context = nullptr)
        : std::runtime_error(message), context(context) {}

    explicit SemaError(const char* message, antlr4::ParserRuleContext* context = nullptr)
        : std::runtime_error(message), context(context) {}

    [[nodiscard]] antlr4::ParserRuleContext* getContext() const {
        return context;
    }

    [[nodiscard]] std::string printErrorContext() const {
        std::stringstream contextInfo;

        if (context) {
            const auto token = context->getStart();
            const auto inputStream = token->getInputStream();

            const int line = token->getLine();
            const int charPositionInLine = token->getCharPositionInLine();

            contextInfo << "Error at line " << line << ":" << charPositionInLine << "\n";

            if (inputStream) {
                std::string inputText = inputStream->toString();

                std::vector<std::string> lines;
                std::string currentLine;
                std::istringstream iss(inputText);

                while (std::getline(iss, currentLine)) {
                    lines.push_back(currentLine);
                }

                if (line > 1) {
                    contextInfo << line - 1 << ": " << lines[line - 2] << "\n";
                }

                contextInfo << line << ": " << lines[line - 1] << "\n";

                std::string pointer(std::to_string(line).length() + 2 + charPositionInLine, ' ');
                pointer += "^";
                contextInfo << pointer << "\n";

                if (line < lines.size()) {
                    contextInfo << line + 1 << ": " << lines[line] << "\n";
                }
            }
        } else {
            contextInfo << "No context information available.";
        }

        return contextInfo.str();
    }

private:
    antlr4::ParserRuleContext* context;
};
