//
// Created by Marvin Haschker on 24.03.25.
//

#ifndef JINJACPPEXPORT_H
#define JINJACPPEXPORT_H

#include "../LangExport.h"

struct JinjaCppExport final : LangExport
{
    explicit JinjaCppExport(Sema* sema, const vec<const Concept*>& c, const vec<const Function*>& f) :
        LangExport(sema, c, f)
    {
        register_concept_functions();
        register_function_functions();
    };

    std::string process(const std::filesystem::path&) override;
private:
    void register_concept_functions() override;
    void register_function_functions() override;
};

#endif //JINJACPPEXPORT_H
