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
    bool overwrite_output = false;

    app.add_option("--input", input_file, "Input file")
       ->required()
       ->check(CLI::ExistingFile);

    app.add_option("--output-folder", output_folder, "Output folder")
        ->default_str(output_folder.string());

    app.add_option("--template-folder", template_folder, "Template folder")
        ->check(CLI::ExistingDirectory)
        ->default_val(template_folder.string());

    app.add_flag("--overwrite-output", overwrite_output,
                 "Overwrite the output directory if it exists and is not empty");

    CLI11_PARSE(app, argc, argv);

    DirValidator validator(overwrite_output);
    if (const std::string err_msg = validator(output_folder.string()); !err_msg.empty())
        return app.exit(CLI::ValidationError(err_msg));

    const Processor p{input_file};
    const u_ptr<Sema> sema = p.run_sema();

    const JinjaEngine engine{sema.get()};
    std::cout << engine.process(LanguageMode::Cpp, "example/example_1.txt") << std::endl;

    return 0;
}
