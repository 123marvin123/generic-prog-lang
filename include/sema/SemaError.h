#pragma once

#include <stdexcept>
#include <string>
#include <sstream>
#include "antlr4-runtime.h"

struct SemaError final : std::runtime_error {
    explicit SemaError(const std::string& message, antlr4::ParserRuleContext* context = nullptr)
        : std::runtime_error(message), context(context)
    {
        construct_error_message();
    }

    explicit SemaError(const char* message, antlr4::ParserRuleContext* context = nullptr)
        : std::runtime_error(message), context(context)
    {
        construct_error_message();
    }

    [[nodiscard]]
    antlr4::ParserRuleContext* getContext() const {
        return context;
    }

    [[nodiscard]]
    const char *what() const noexcept override
    {
        return error_message.c_str();
    }

    [[nodiscard]]
    std::string printErrorContext() const {
        std::stringstream contextInfo;

        if (context) {
            const auto token = context->getStart();
            const auto inputStream = token->getInputStream();

            const auto line = token->getLine();
            const auto charPositionInLine = token->getCharPositionInLine();

            contextInfo << "Error at line " << line << ":" << charPositionInLine << "\n";

            if (inputStream) {
                std::string inputText = inputStream->toString();

                std::vector<std::string> lines;
                std::string currentLine;
                std::istringstream iss(inputText);

                while (std::getline(iss, currentLine)) {
                    lines.push_back(currentLine);
                }

                // Show previous line if available
                if (line > 1 && (line - 2) < lines.size()) {
                    contextInfo << line - 1 << ": " << lines[line - 2] << "\n";
                }

                // Show current line if available
                if (line > 0 && (line - 1) < lines.size()) {
                    contextInfo << line << ": " << lines[line - 1] << "\n";

                    std::string pointer(std::to_string(line).length() + 2 + charPositionInLine, ' ');
                    pointer += "^";
                    contextInfo << pointer << "\n";
                }

                // Show next line if available
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
    void construct_error_message()
    {
        std::string supplemental_info;
        if (context)
        {
            supplemental_info = std::format(" - {}", printErrorContext());
        }

        error_message = std::format("{}{}", std::runtime_error::what(), supplemental_info);
    }

    antlr4::ParserRuleContext* context;
    std::string error_message;
};