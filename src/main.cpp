#include <iostream>
#include <CLI/CLI.hpp>

#include "export/JinjaEngine.h"
#include "Processor.h"

const std::map<std::string, LanguageMode> langmode_map = {{"cpp", LanguageMode::Cpp}, {"python", LanguageMode::Python}};

void process(const std::filesystem::path& input_file, const std::filesystem::path& output_folder,
             const std::filesystem::path& template_folder, const bool purge_output, const LanguageMode language_mode)
{
    const Processor p{input_file};
    const u_ptr<Sema> sema = p.run_sema();

    for (const JinjaEngine engine{sema.get(), output_folder, template_folder, purge_output};
         const auto& f : engine.process(language_mode))
        std::cout << f << std::endl;
}

void print_exception(const std::exception& e, const unsigned int level = 0)
{
    if (level > 0)
        std::cerr << "[" << level << "] ";
    std::cerr << e.what() << '\n';
    try
    {
        std::rethrow_if_nested(e);
    }
    catch (const std::exception& nestedException)
    {
        print_exception(nestedException, level + 1);
    }
    catch (...) {}
}

int main(const int argc, char** argv)
{
    CLI::App app{"Generic Programming Language Transpiler"};
    argv = app.ensure_utf8(argv);

    std::filesystem::path input_file,
        output_folder = std::filesystem::current_path() / "output",
        template_folder = std::filesystem::current_path() / "templates";
    bool purge_output = false;
    auto language_mode{LanguageMode::Cpp};

    app.add_option("--input", input_file, "Input file")
       ->required()
       ->check(CLI::ExistingFile);

    app.add_option("--output-folder", output_folder, "Output folder")
        ->default_str(output_folder.string());

    app.add_option("--template-folder", template_folder, "Template folder")
        ->check(CLI::ExistingDirectory)
        ->default_val(template_folder.string());

    app.add_flag("--purge", purge_output,
                 "Removes all files in the output directory before writing new files");

    app.add_option("--lang-mode", language_mode, "Language modes to generate")
        ->required()
        ->transform(CLI::CheckedTransformer(langmode_map, CLI::ignore_case));

    CLI11_PARSE(app, argc, argv);

    DirValidator validator(purge_output);
    if (const std::string err_msg = validator(output_folder.string()); !err_msg.empty())
        return app.exit(CLI::ValidationError(err_msg));

    /*try
    {*/
        process(input_file, output_folder, template_folder, purge_output, language_mode);
    /*}
    catch (const std::exception& e)
    {
        print_exception(e);
        return EXIT_FAILURE;
    }*/


    return EXIT_SUCCESS;
}
