#pragma once

#include <string>
#include <regex>
#include <unordered_set>
#include <filesystem>

struct Preprocessor
{

    std::string process(const std::filesystem::path& input_file);

private:
    std::string process_recursive(const std::filesystem::path& input_file, std::unordered_set<std::string>& visitedFiles); // NOLINT(*-no-recursion)

};
