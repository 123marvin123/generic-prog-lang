//
// Created by Marvin Haschker on 24.03.25.
//

#ifndef JINJAPYTHONEXPORT_H
#define JINJAPYTHONEXPORT_H

#include "../LangExport.h"

struct JinjaPythonExport final : LangExport
{
    explicit JinjaPythonExport(Sema* sema, const vec<const Concept*>& c, const vec<const Function*>& f) : LangExport(sema, c, f) {};

    std::string process(const std::filesystem::path&) override { throw std::runtime_error("Not implemented"); }
};

#endif //JINJAPYTHONEXPORT_H
