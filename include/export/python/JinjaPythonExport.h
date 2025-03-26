//
// Created by Marvin Haschker on 24.03.25.
//

#ifndef JINJAPYTHONEXPORT_H
#define JINJAPYTHONEXPORT_H

#include "../LangExport.h"

struct JinjaPythonExport final : LangExport
{
    explicit JinjaPythonExport(Sema* sema, const std::filesystem::path& /*template_folder*/,
                                std::filesystem::path out,
                               const vec<const Concept*>& c,
                               const vec<const Function*>& f) :
        LangExport(sema, std::move(out), c, f)
    {
    };

    vec<std::filesystem::path> process() override
    {
        throw std::runtime_error("Not implemented");
    }
};

#endif //JINJAPYTHONEXPORT_H
