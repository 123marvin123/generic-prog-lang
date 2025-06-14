#include "sema/SemaIdentifier.h"
#include "sema/Namespace.h"

std::string SemaIdentifier::get_full_name() const
{
    return std::format("{}::{}", get_namespace()->get_full_name(), get_identifier());
}