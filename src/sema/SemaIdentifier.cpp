#include "sema/SemaIdentifier.h"
#include "sema/Namespace.h"

std::string SemaIdentifier::get_full_name() const
{
    const auto name = std::string(get_identifier());
    return get_namespace()->get_full_name() + "::" + name;
}