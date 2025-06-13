//
// Created by Marvin Haschker on 17.03.25.
//
#include "Preprocessor.h"
#include <fstream>
#include <sstream>
#include <format>

std::string Preprocessor::process(const std::filesystem::path& input_file)
{
    std::unordered_set<std::string> files{};
    return process_recursive(input_file, files);
}

std::string Preprocessor::process_recursive(const std::filesystem::path& input_file, std::unordered_set<std::string>& visitedFiles)
{
    if (visitedFiles.contains(input_file)) {
        return "";
    }
    visitedFiles.insert(input_file);

    std::ifstream file(input_file);
    if (!file.is_open()) {
        throw std::runtime_error(std::format("Failed to open file: {}", input_file.string()));
    }

    std::stringstream result;
    std::string line;
    const std::regex importPattern(R"raw(#import\s*"([^"]+)")raw");

    while (std::getline(file, line)) {
        if (std::smatch match;
            std::regex_search(line, match, importPattern)) {
            std::string importPath = match[1].str();

            std::filesystem::path basePath = std::filesystem::path(input_file).parent_path();
            std::filesystem::path resolvedPath = basePath / importPath;

            result << process_recursive(resolvedPath.string(), visitedFiles);
            } else {
                result << line << '\n';
            }
    }

    return result.str();
}
