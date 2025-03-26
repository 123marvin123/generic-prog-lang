#include <iostream>
#include <CLI/CLI.hpp>

#include "export/JinjaEngine.h"
#include "Processor.h"

int main(const int argc, char** argv)
{
    CLI::App app{"Generic Programming Language Transpiler"};
    argv = app.ensure_utf8(argv);

    std::filesystem::path input_file,
        output_folder = std::filesystem::current_path() / "output",
        template_folder = std::filesystem::current_path() / "templates";
    bool purge_output = false;

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

    CLI11_PARSE(app, argc, argv);

    DirValidator validator(purge_output);
    if (const std::string err_msg = validator(output_folder.string()); !err_msg.empty())
        return app.exit(CLI::ValidationError(err_msg));

    const Processor p{input_file};
    const u_ptr<Sema> sema = p.run_sema();

    for (const JinjaEngine engine{sema.get(), output_folder, template_folder, purge_output};
        const auto& a : engine.process(LanguageMode::Cpp))
        std::cout << a << std::endl;

    return 0;
}
